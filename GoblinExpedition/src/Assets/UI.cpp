#include "UI.h"
#include "Enemy.h"
#include "../Task/Task_Game.h"
#include <iostream>
/*コンストラクタ*/
UI::UI()
{
#ifdef _DEBUG
	std::cout << "UI()" << std::endl;
#endif // _DEBUG
}
/*デストラクタ*/
UI::~UI()
{
	this->Finalize();
#ifdef _DEBUG
	std::cout << __super::getTaskname().second <<  "~UI()" << std::endl;
#endif // _DEBUG
}
/*パラメータの初期化をします*/
bool UI::Init_Parameter(const TASKNAME& taskname_, const ObjectType& objecttype_, const Vec2& position_, const Point& scale_, const float& order_)
{
	/*タスク名を設定*/
	__super::setTaskName(taskname_);
	/*描画優先順位を設定*/
	__super::setDrawOrder(this->order = order_);

	this->position = position_;
	this->scale = scale_;
	this->objecttype = objecttype_;
	this->killcheck = false;

	//機能の設定
	void(UI::*function[])() =
	{
		&UI::BackGround_Parameter,
		&UI::Player_Life_Parameter,
		&UI::ScoreUI_Parameter,
		&UI::MusouItem_Parameter,
		&UI::ResultRogo_Parameter
	};
	(this->*function[(int)this->objecttype])();

	return true;
}
/*解放処理*/
bool UI::Finalize()
{
	return true;
}
/*更新処理*/
void UI::Update()
{
	if (this->killcheck)
	{
		this->EnemiesKill();
	}
}
/*描画をします*/
void UI::Render()
{
	switch (this->objecttype)
	{
	case ObjectType::Background:
		this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
		break;
	case ObjectType::PlayerLife:
		this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
		break;
	case ObjectType::ScoreUI:
		this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
		break;
	case ObjectType::MusouItem:
		this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
		break;
	case ObjectType::ResultRogo:
		this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
		break;
	default:
		break;
	}
}
/*オブジェクトを生成します*/
TaskObject::SP UI::Create(const TASKNAME& taskname_, const ObjectType& objecttype_, const Vec2& position_, const Point& scale_,const float& order_ ,bool flag)
{
	UI::SP ui = UI::SP(new UI());
	if (ui)
	{
		ui->me = ui;
		if (!ui->Init_Parameter(taskname_, objecttype_, position_, scale_, order_))
		{
			ui->Kill();
		}
		if (flag)
		{
			taskSystem->Add(ui);
		}
		return ui;
	}
	return nullptr;
}
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★

/*背景の設定を行います*/
void UI::BackGround_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF (this->position, this->scale) , Rect(0, 0, 680, 480));
	this->draw->setTexture(rm->getTexture("インゲーム背景"));
}
/*Playerライフの設定を行います*/
void UI::Player_Life_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 64, 48));
	this->draw->setTexture(rm->getTexture("プレイヤライフ"));
}
/*スコアUIの設定を行います*/
void UI::ScoreUI_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 185, 75));
	this->draw->setTexture(rm->getTexture("スコアUI"));
}
/*無双アイテムの設定を行います*/
void UI::MusouItem_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 64, 64));
	this->draw->setTexture(rm->getTexture("無双アイテム"));
	this->collider = Collider::Addcomponent(Collider::ShapeHitType::Cube,this->position,this->scale);
}
/*リザルトロゴの設定を行います*/
void UI::ResultRogo_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0,0,536,106));
	this->draw->setTexture(rm->getTexture("リザルトロゴ"));
}
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★

/*無双アイテムを使用します*/
void UI::MusouItem_Use()
{
	this->killcheck = true;
}
/*ウィンドウ内にあるかを判定します*/
bool UI::isInWindow(const Vec2& position_, const Point& scale_)
{
	//ウィンドウ矩形を生成する
	RectF window = { 0,0,Window::Size()};
	return window.intersects(RectF(position_, scale_));
}
/*ウィンドウ内にあるかを判定します*/
bool UI::isInWindow(const RectF& drawbase)
{
	RectF window = { 0,0,Window::Size() };
	return window.intersects(RectF(drawbase));
}
/*敵を全滅させます*/
void UI::EnemiesKill()
{
	auto game = taskSystem->GetTask_TaskName<Game>("インゲーム");

	auto enemys = taskSystem->GetTasks_TaskName<Enemy>("ゴブリン");
	if (enemys && game)
	{
		for (auto it = enemys->begin(); it != enemys->end(); ++it)
		{
			if (this->isInWindow((*it)->getHitBace()))
			{
				(*it)->Opaque_Decrement();
				if ((*it)->isOpaque_Zero())
				{
					//スコアを加算
					game->ScoreAddition(ENEMY_SCORE);
					//撃破数を加算
					game->Enemy_DestroyingCount_Add(ENEMY_DESTROYINGSCORE);
					//モンスターの消滅フラグをtrue
					(*it)->setMusouitemkill(true);
					//モンスターの消去
					(*it)->Kill();
					//自身の削除
					this->Kill();
				}
			}
		}
	}
}
/*マウスの判定した後の処理*/
void UI::Receive_Player()
{
	this->MusouItem_Use();
}
/*左クリックが押されたかを判定します*/
bool UI::MouseLclicked()
{
	return this->collider->MouseLeftPressed();
}
/*UIと当たり判定を返します*/
bool UI::Hit(const RectF& drawbace)
{
	if (this->collider)
	{
		return this->collider->Hit(drawbace);
	}
	return false;
}


///*無双アイテムの当たり判定矩形を返します*/
//RectF UI::getDrawBase_MusuoItem()const
//{
//	return this->collider->getHitBace();
//}