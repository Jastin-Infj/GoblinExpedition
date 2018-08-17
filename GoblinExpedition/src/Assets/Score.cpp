#include <iostream>
#include <string>
#include "Score.h"
#include "../Task/Task_Game.h"

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
bool Score::Score_Parameter(const TASKNAME& taskname_,const  ObjectType& objecttype_ ,const Vec2& position_, const Point& scale_,const int& digit_ ,const int& score_ , const float& order_)
{
	__super::setTaskName(taskname_);
	this->objecttype = objecttype_;
	this->position = position_;
	this->scale = scale_;
	this->setDrawOrder((order = order_));
	this->selectdigit = digit_;
	this->effectcount = 0;

	//�e�@�\���Ƃ̐ݒ�
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale));
	this->draw->setTexture(rm->getTexture("�X�R�A"));

	this->score = score_;

	return true;
}
/*�X�V����*/
void Score::Update()
{
	this->Score_UpDate();
}
/*�`������܂�*/
void Score::Render()
{
	if (!this->draw->getSrcBace().w == 0 && !this->draw->getSrcBace().h == 0)
	{
		this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
	}
}
/*����������s���܂�*/
bool Score::Finalize()
{
	return true;
}
/*�X�R�A�̌v�Z���s���܂�*/
void Score::Score_UpDate()
{
	if (this->objecttype == ObjectType::InGameUI)
	{
		auto game = taskSystem->GetTask_TaskName<Game>("�C���Q�[��");
		if (game)
		{
			this->score = game->getScore();
		}
	}

	if (this->objecttype == ObjectType::KillEnemy)
	{
		this->KilledEnemy_update();
	}
	

	//�w�肵�������̐������擾
	std::string str = this->Digit(this->score);

	if (str == "")
	{
		return;
	}
	//�摜����`�̍쐬
	this->setvalueSrc(str);
}
/*�w��̌����̐�����Ԃ��܂�*/
std::string Score::Digit(const int& score_)
{
	std::string str = std::to_string(score_);
	if (this->selectdigit <= str.size())
	{
		str = str.substr(this->selectdigit - 1, 1);
		return str;
	}
	return "";
}
/*�G���|�ꂽ��X�R�A�𐶐����܂�*/
void Score::KilledEnemy_update()
{
	this->effectcount++;
	if (this->effectcount >= 60)
	{
		this->Kill();
	}
	//��ŋL�q
}
/*�摜����`�̍쐬*/
void Score::setvalueSrc(const std::string& value)
{
	if (value == "")
	{
		this->draw->setDrawSrc(RectF{});
	}
	else if (value == "0")
	{
		this->draw->setDrawSrc(RectF(0, 0, 40, 50));
	}
	else if (value == "1")
	{
		this->draw->setDrawSrc(RectF(40, 0, 64 - 40, 50));
	}
	else if (value == "2")
	{
		this->draw->setDrawSrc(RectF(64, 0, 100 - 64, 50));
	}
	else if (value == "3")
	{
		this->draw->setDrawSrc(RectF(100, 0, 140 - 100, 50));
	}
	else if (value == "4")
	{
		this->draw->setDrawSrc(RectF(140, 0, 178 - 140, 50));
	}
	else if (value == "5")
	{
		this->draw->setDrawSrc(RectF(178, 0, 215 - 178, 50));
	}
	else if (value == "6")
	{
		this->draw->setDrawSrc(RectF(215, 0, 251 - 215, 50));
	}
	else if (value == "7")
	{
		this->draw->setDrawSrc(RectF(251, 0, 288 - 251, 50));
	}
	else if (value == "8")
	{
		this->draw->setDrawSrc(RectF(288, 0, 325 - 288, 50));
	}
	else if (value == "9")
	{
		this->draw->setDrawSrc(RectF(325, 0, 361 - 325, 50));
	}
}
/*�X�R�A�̐��������܂�*/
TaskObject::SP Score::Create(const TASKNAME& taskname_,const ObjectType& objecttype_ ,const Vec2& position_, const Point& scale_,const int& digit_ , const int& score_  ,const float& order_, bool flag)
{
	Score::SP score = Score::SP(new Score());
	if (score)
	{
		if (!score->Score_Parameter(taskname_ ,objecttype_, position_ , scale_ ,digit_ ,score_,order_))
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