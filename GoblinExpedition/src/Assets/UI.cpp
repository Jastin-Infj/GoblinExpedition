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
	void(UI::*set_parametar[])() =
	{
		&UI::BackGround_Parameter,		//背景
		&UI::Player_Life_Parameter,		//プレイヤライフ
		&UI::ScoreUI_Parameter,			//スコア表示UI
		&UI::MusouItem_Parameter,		//無双アイテム
		&UI::ResultRogo_Parameter,		//リザルトロゴ
		&UI::TitleRogo_Parameter,		//タイトルUI
		&UI::Escape_Parameter,			//エスケープキー
		&UI::HowplayUI_Parameter,		//遊び方UI
		&UI::TotitleUI_Parameter		//タイトルへ戻るUI
	};
	(this->*set_parametar[(int)this->objecttype])();

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
	this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
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
	this->collider = Collider::Addcomponent(Collider::ShapeT::RectF,this->position,this->scale);
}
/*リザルトロゴの設定を行います*/
void UI::ResultRogo_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0,0,536,106));
	this->draw->setTexture(rm->getTexture("リザルトロゴ"));
}
/*タイトルロゴの設定を行います*/
void UI::TitleRogo_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 418, 64));
	this->draw->setTexture(rm->getTexture("タイトルロゴ"));
}
/*エスケープロゴの設定を行います*/
void UI::Escape_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 285, 88));
	this->draw->setTexture(rm->getTexture("エスケープロゴ"));
	this->collider = Collider::Addcomponent(Collider::ShapeT::RectF, this->position,this->scale);
}
/*遊び方UIの設定を行います*/
void UI::HowplayUI_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 602,133));
	this->draw->setTexture(rm->getTexture("遊び方UI"));
}
/*タイトルへ戻るUIの設定を行います*/
void UI::TotitleUI_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 606, 135));
	this->draw->setTexture(rm->getTexture("タイトルへ戻る"));
	this->collider = Collider::Addcomponent(Collider::ShapeT::RectF, this->position, this->scale);
}
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★

/*無双アイテムを使用します*/
void UI::MusouItem_Use()
{
	this->killcheck = true;
}
/*ゲームを終了させます*/
void UI::Escape_Use()
{
	Game::WP game = taskSystem->GetTask_TaskName<Game>("インゲーム");
	if (!game.expired())
	{
		Game::SP temp = game.lock();
		temp->ChengeGameState(Game::GameState::ESCAPE);
	}
}
/*ウィンドウ内にあるかを判定します*/
bool UI::isInWindow(const Vec2& position_)
{
	//ウィンドウ矩形を生成する
	RectF window = { 0,0, Window::Size()};
	return window.intersects(Vec2(position_));
}
/*ウィンドウ内にあるかを判定します*/
bool UI::isInWindow(const RectF& drawbase)
{
	RectF window = { 0,0,Window::Size() };
	return window.intersects(Vec2(drawbase.x , drawbase.y));
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
				(*it)->SE_Play_frame();
				if (!(*it)->isOpaque_Zero())
				{
					(*it)->Opaque_Decrement();
				}
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
	switch (this->objecttype)
	{
	case ObjectType::MusouItem:		//無双アイテムの使用
		this->MusouItem_Use();
		break;
	case ObjectType::ESCAPERogo:	//エスケープが押された
		this->Escape_Use();
		break;
	}
}
/*左クリックが押されたを判定します*/
bool UI::MouseLclicked()
{
	return this->collider->MouseLeftClicked();
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
/*自身が持つオブジェクトタイプを返します*/
UI::ObjectType UI::getObjecttype()const
{
	return this->objecttype;
}