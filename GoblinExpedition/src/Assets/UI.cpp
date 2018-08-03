#include "UI.h"
#include "Enemy.h"
#include "../Task/Task_Game.h"
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
	this->killcheck = false;

	//�@�\�̐ݒ�
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
/*�������*/
bool UI::Finalize()
{
	return true;
}
/*�X�V����*/
void UI::Update()
{
	if (this->killcheck)
	{
		this->EnemiesKill();
	}
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
/*�X�R�AUI�̐ݒ���s���܂�*/
void UI::ScoreUI_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 185, 75));
	this->draw->setTexture(rm->getTexture("�X�R�AUI"));
}
/*���o�A�C�e���̐ݒ���s���܂�*/
void UI::MusouItem_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 64, 64));
	this->draw->setTexture(rm->getTexture("���o�A�C�e��"));
	this->collider = Collider::Addcomponent(Collider::ShapeHitType::Cube,this->position,this->scale);
}
/*���U���g���S�̐ݒ���s���܂�*/
void UI::ResultRogo_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0,0,536,106));
	this->draw->setTexture(rm->getTexture("���U���g���S"));
}
//��������������������������������������������������������������������������������������������������������

/*���o�A�C�e�����g�p���܂�*/
void UI::MusouItem_Use()
{
	this->killcheck = true;
}
/*�E�B���h�E���ɂ��邩�𔻒肵�܂�*/
bool UI::isInWindow(const Vec2& position_, const Point& scale_)
{
	//�E�B���h�E��`�𐶐�����
	RectF window = { 0,0,Window::Size()};
	return window.intersects(RectF(position_, scale_));
}
/*�E�B���h�E���ɂ��邩�𔻒肵�܂�*/
bool UI::isInWindow(const RectF& drawbase)
{
	RectF window = { 0,0,Window::Size() };
	return window.intersects(RectF(drawbase));
}
/*�G��S�ł����܂�*/
void UI::EnemiesKill()
{
	auto game = taskSystem->GetTask_TaskName<Game>("�C���Q�[��");

	auto enemys = taskSystem->GetTasks_TaskName<Enemy>("�S�u����");
	if (enemys && game)
	{
		for (auto it = enemys->begin(); it != enemys->end(); ++it)
		{
			if (this->isInWindow((*it)->getHitBace()))
			{
				(*it)->Opaque_Decrement();
				if ((*it)->isOpaque_Zero())
				{
					//�X�R�A�����Z
					game->ScoreAddition(ENEMY_SCORE);
					//���j�������Z
					game->Enemy_DestroyingCount_Add(ENEMY_DESTROYINGSCORE);
					//�����X�^�[�̏��Ńt���O��true
					(*it)->setMusouitemkill(true);
					//�����X�^�[�̏���
					(*it)->Kill();
					//���g�̍폜
					this->Kill();
				}
			}
		}
	}
}
/*�}�E�X�̔��肵����̏���*/
void UI::Receive_Player()
{
	this->MusouItem_Use();
}
/*���N���b�N�������ꂽ���𔻒肵�܂�*/
bool UI::MouseLclicked()
{
	return this->collider->MouseLeftPressed();
}
/*UI�Ɠ����蔻���Ԃ��܂�*/
bool UI::Hit(const RectF& drawbace)
{
	if (this->collider)
	{
		return this->collider->Hit(drawbace);
	}
	return false;
}


///*���o�A�C�e���̓����蔻���`��Ԃ��܂�*/
//RectF UI::getDrawBase_MusuoItem()const
//{
//	return this->collider->getHitBace();
//}