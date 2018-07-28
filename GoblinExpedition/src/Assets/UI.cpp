#include "UI.h"
#include <iostream>
/*�R���X�g���N�^*/
UI::UI()
{
#ifdef _DEBUG
	std::cout << "UI()" << std::endl;
#endif // _DEBUG
}
/*�f�X�g���N�^*/
UI::~UI()
{
	this->Finalize();
#ifdef _DEBUG
	std::cout << __super::getTaskname().second <<  "~UI()" << std::endl;
#endif // _DEBUG
}
/*�p�����[�^�̏����������܂�*/
bool UI::Init_Parameter(const TASKNAME& taskname_, const ObjectType& objecttype_, const Vec2& position_, const Point& scale_, const float& order_)
{
	/*�^�X�N����ݒ�*/
	__super::setTaskName(taskname_);
	/*�`��D�揇�ʂ�ݒ�*/
	__super::setDrawOrder(this->order = order_);

	this->position = position_;
	this->scale = scale_;
	this->objecttype = objecttype_;

	//�@�\�̐ݒ�
	void(UI::*function[])() =
	{
		&UI::BackGround_Parameter,
		&UI::Player_Life_Parameter
	};
	(this->*function[(int)this->objecttype])();

	return true;
}
/*�������*/
bool UI::Finalize()
{
	return true;
}
/*�X�V����*/
void UI::UpDate()
{
	
}
/*�`������܂�*/
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
/*�I�u�W�F�N�g�𐶐����܂�*/
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
//��������������������������������������������������������������������������������������������������������

/*�w�i�̐ݒ���s���܂�*/
void UI::BackGround_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF (this->position, this->scale) , Rect(0, 0, 680, 480));
	this->draw->setTexture(rm->getTexture("�C���Q�[���w�i"));
}
/*Player���C�t�̐ݒ���s���܂�*/
void UI::Player_Life_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 64, 48));
	this->draw->setTexture(rm->getTexture("�v���C�����C�t"));
}
//��������������������������������������������������������������������������������������������������������
