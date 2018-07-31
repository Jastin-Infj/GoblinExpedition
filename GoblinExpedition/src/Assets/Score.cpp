#include <iostream>
#include "Score.h"

/*�R���X�g���N�^*/
Score::Score()
{
#ifdef _DEBUG
	std::cout << "Score()" << std::endl;
#endif // _DEBUG
}
/*�f�X�g���N�^*/
Score::~Score()
{
	this->Finalize();
#ifdef _DEBUG
	std::cout << __super::getTaskname().second << "~Score()" << std::endl;
#endif // _DEBUG
}
/*�X�R�A�̏������ݒ���s���܂�*/
bool Score::Score_Parameter(const TASKNAME& taskname_, const Vec2& position_, const Point& scale_, const int& digit_ , const float& order_)
{
	__super::setTaskName(taskname_);
	this->position = position_;
	this->scale = scale_;
	this->setDrawOrder((order = order_));
	this->selectdigit = digit_;

	//�e�@�\���Ƃ̐ݒ�
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale));

	return true;
}
/*�X�V����*/
void Score::UpDate()
{
	this->Score_UpDate();
}
/*�`������܂�*/
void Score::Render()
{
	this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
}
/*����������s���܂�*/
bool Score::Finalize()
{
	return true;
}
/*�X�R�A�̍X�V�������s���܂�*/
void Score::Score_UpDate()
{
	//�w�肵�������̐������擾
	std::string str = this->Digit();

	//�摜����`�̍쐬
	this->setvalueSrc(str);
}
/*�w��̌����̐�����Ԃ��܂�*/
std::string Score::Digit()
{
	std::string str = std::to_string(this->score);
	str = str.substr(this->selectdigit - 1, this->selectdigit);
	return str;
}
/*���݃X�R�A��Ԃ��܂�*/
int Score::getScore()const
{
	return this->score;
}
/*�摜����`�̍쐬*/
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
/*�X�R�A�̐��������܂�*/
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