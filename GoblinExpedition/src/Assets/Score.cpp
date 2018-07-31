#include <iostream>
#include "Score.h"

/*コンストラクタ*/
Score::Score()
{
#ifdef _DEBUG
	std::cout << "Score()" << std::endl;
#endif // _DEBUG
}
/*デストラクタ*/
Score::~Score()
{
	this->Finalize();
#ifdef _DEBUG
	std::cout << __super::getTaskname().second << "~Score()" << std::endl;
#endif // _DEBUG
}
/*スコアの初期化設定を行います*/
bool Score::Score_Parameter(const TASKNAME& taskname_, const Vec2& position_, const Point& scale_, const int& digit_ , const float& order_)
{
	__super::setTaskName(taskname_);
	this->position = position_;
	this->scale = scale_;
	this->setDrawOrder((order = order_));
	this->selectdigit = digit_;

	//各機能ごとの設定
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale));

	return true;
}
/*更新処理*/
void Score::UpDate()
{
	this->Score_UpDate();
}
/*描画をします*/
void Score::Render()
{
	this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
}
/*解放処理を行います*/
bool Score::Finalize()
{
	return true;
}
/*スコアの更新処理を行います*/
void Score::Score_UpDate()
{
	//指定した桁数の数字を取得
	std::string str = this->Digit();

	//画像元矩形の作成
	this->setvalueSrc(str);
}
/*指定の桁数の数字を返します*/
std::string Score::Digit()
{
	std::string str = std::to_string(this->score);
	str = str.substr(this->selectdigit - 1, this->selectdigit);
	return str;
}
/*現在スコアを返します*/
int Score::getScore()const
{
	return this->score;
}
/*画像元矩形の作成*/
void Score::setvalueSrc(const std::string& value)
{
	if (value == "")
	{
		return;
	}
	else if (value == "0")
	{
		
	}
	else if (value == "1")
	{

	}
	else if (value == "2")
	{

	}
	else if (value == "3")
	{

	}
	else if (value == "4")
	{

	}
	else if (value == "5")
	{

	}
	else if (value == "6")
	{

	}
	else if (value == "7")
	{

	}
	else if (value == "8")
	{

	}
	else if (value == "9")
	{

	}
}
/*スコアの生成をします*/
TaskObject::SP Score::Create(const TASKNAME& taskname_, const Vec2& position_, const Point& scale_,const int& digit_  ,const float& order_, bool flag)
{
	Score::SP score = Score::SP(new Score());
	if (score)
	{
		if (!score->Score_Parameter(taskname_ , position_ , scale_ , digit_ , order_))
		{
			score->Kill();
		}
		if (flag)
		{
			taskSystem->Add(score);
		}
		return score;
	}
	return nullptr;
}