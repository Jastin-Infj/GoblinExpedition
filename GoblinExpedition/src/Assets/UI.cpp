#include "UI.h"
#include "../Task/Task_Game.h"
#include "../Task/Task_Title.h"
#include "../Task/Task_Result.h"
#include "../Task/Task_HowPlay.h"
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
bool UI::Init_Parameter(
	const TASKNAME&   taskname_, 
	const ObjectType& objecttype_, 
	const Vec2&       position_, 
	const Point&      scale_,
	const InitFormat& initformat,
	const Rect&       src,
	const float&      order_
	)
{
	/*タスク名を設定*/
	__super::setTaskName(taskname_);
	/*描画優先順位を設定*/
	__super::setDrawOrder(this->order = order_);

	this->position = position_;
	this->scale = scale_;
	this->objecttype = objecttype_;
	this->killcheck = false;
	this->itemuseflag = false;

	//機能の設定
	void(UI::*set_parametar[])(const Rect&) =
	{
		&UI::Normal,
		&UI::AddCollider
	};
	(this->*set_parametar[(int)initformat])(src);

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
TaskObject::SP UI::Create(
	const TASKNAME&   taskname_, 
	const ObjectType& objecttype_, 
	const Vec2&       position_, 
	const Point&      scale_,
	const InitFormat& initformat,
	const Rect&       src,
	const float&      order_ ,
	bool              flag
	)
{
	UI::SP ui = UI::SP(new UI());
	if (ui)
	{
		ui->me = ui;
		if (!ui->Init_Parameter(taskname_, objecttype_, position_, scale_,initformat,src,order_))
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

/*初期設定で設定する雛形　画像サイズ分の描画をする*/
void UI::Normal(const Rect& src_)
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), src_);
	this->draw->setTexture(rm->getTexture(this->getTaskname().second));
}
/*当たり判定の設定もする雛形　画像サイズ分の当たり判定と描画をします*/
void UI::AddCollider(const Rect& src_)
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), src_);
	this->draw->setTexture(rm->getTexture(this->getTaskname().second));
	this->collider = Collider::Addcomponent(Collider::ShapeT::Rect,this->position, this->scale);
}
/*左クリックが押された後の処理をまとめた関数*/
void UI::TitleStartUI_LeftClicked()
{
	auto title = taskSystem->GetTask_TaskName<Title>("タイトル");
	if (title)
	{
		title->Kill();
	}
}
/*マウスで左クリックが押された後の処理を行います*/
void UI::ToGameUI_LeftClicked()
{
	auto howplay = taskSystem->GetTask_TaskName<HowPlay>("遊び方");
	if (howplay)
	{
		howplay->Kill();
	}
}
/*タイトルへ戻るUIが押された後の処理を行います*/
void UI::TotitleUI_LeftClicked()
{
	auto result = taskSystem->GetTask_TaskName<Result>("リザルト");
	if (result)
	{
		result->Kill();
	}
}
/*タイトル用終了ボタンUIの設定を行います*/
void UI::TitleExitUI_LeftClicked()
{
	taskSystem->Application_Exit();
}
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★

/*無双アイテムを使用します*/
void UI::MusouItem_Use()
{
	this->killcheck = true;
	if (this->itemuseflag)
	{
		return;
	}
	else
	{
		this->itemuseflag = true;
	}
}
/*ゲームを終了させます*/
void UI::Escape_Use()
{
	auto game = taskSystem->GetTask_TaskName<Game>("インゲーム");
	if (game)
	{
		game->ChengeGameState(Game::GameState::ESCAPE);
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
					if (!(*it)->getleftrightinversionflag())
					{
						//スコアの生成
						(*it)->KillScoreCreate();
					}
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
		this->itemuseflag = false;
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
	case ObjectType::TitleStart:
		this->TitleStartUI_LeftClicked();	//左クリックで押された後の処理
		break;
	case ObjectType::toGame:
		this->ToGameUI_LeftClicked();		//左クリックで押された後の処理
		break;
	case ObjectType::TitleExit:
		this->TitleExitUI_LeftClicked();	//左クリックが押された後の処理
		break;
	case ObjectType::toTitle:
		this->TotitleUI_LeftClicked();		//左クリックが押された後の処理
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
/*アイテムを使用中かどうか判定します*/
bool UI::isUseItem()const
{
	return this->itemuseflag;
}