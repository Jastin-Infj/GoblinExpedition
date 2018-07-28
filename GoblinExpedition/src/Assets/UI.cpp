#include "UI.h"
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

	//機能の設定
	void(UI::*function[])() =
	{
		&UI::BackGround_Parameter,
		&UI::Player_Life_Parameter
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
void UI::UpDate()
{
	
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
		this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getDrawBace());
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
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
