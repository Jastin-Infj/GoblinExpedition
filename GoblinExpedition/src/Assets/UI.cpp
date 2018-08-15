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
	void(UI::*set_parametar[])() =
	{
		&UI::BackGround_Parameter,		//�w�i
		&UI::Player_Life_Parameter,		//�v���C�����C�t
		&UI::ScoreUI_Parameter,			//�X�R�A�\��UI
		&UI::MusouItem_Parameter,		//���o�A�C�e��
		&UI::ResultRogo_Parameter,		//���U���g���S
		&UI::TitleRogo_Parameter,		//�^�C�g��UI
		&UI::Escape_Parameter,			//�G�X�P�[�v�L�[
		&UI::HowplayUI_Parameter,		//�V�ѕ�UI
		&UI::TotitleUI_Parameter		//�^�C�g���֖߂�UI
	};
	(this->*set_parametar[(int)this->objecttype])();

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
	this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
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
	this->collider = Collider::Addcomponent(Collider::ShapeT::RectF,this->position,this->scale);
}
/*���U���g���S�̐ݒ���s���܂�*/
void UI::ResultRogo_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0,0,536,106));
	this->draw->setTexture(rm->getTexture("���U���g���S"));
}
/*�^�C�g�����S�̐ݒ���s���܂�*/
void UI::TitleRogo_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 418, 64));
	this->draw->setTexture(rm->getTexture("�^�C�g�����S"));
}
/*�G�X�P�[�v���S�̐ݒ���s���܂�*/
void UI::Escape_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 285, 88));
	this->draw->setTexture(rm->getTexture("�G�X�P�[�v���S"));
	this->collider = Collider::Addcomponent(Collider::ShapeT::RectF, this->position,this->scale);
}
/*�V�ѕ�UI�̐ݒ���s���܂�*/
void UI::HowplayUI_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 602,133));
	this->draw->setTexture(rm->getTexture("�V�ѕ�UI"));
}
/*�^�C�g���֖߂�UI�̐ݒ���s���܂�*/
void UI::TotitleUI_Parameter()
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 606, 135));
	this->draw->setTexture(rm->getTexture("�^�C�g���֖߂�"));
	this->collider = Collider::Addcomponent(Collider::ShapeT::RectF, this->position, this->scale);
}
//��������������������������������������������������������������������������������������������������������

/*���o�A�C�e�����g�p���܂�*/
void UI::MusouItem_Use()
{
	this->killcheck = true;
}
/*�Q�[�����I�������܂�*/
void UI::Escape_Use()
{
	Game::WP game = taskSystem->GetTask_TaskName<Game>("�C���Q�[��");
	if (!game.expired())
	{
		Game::SP temp = game.lock();
		temp->ChengeGameState(Game::GameState::ESCAPE);
	}
}
/*�E�B���h�E���ɂ��邩�𔻒肵�܂�*/
bool UI::isInWindow(const Vec2& position_)
{
	//�E�B���h�E��`�𐶐�����
	RectF window = { 0,0, Window::Size()};
	return window.intersects(Vec2(position_));
}
/*�E�B���h�E���ɂ��邩�𔻒肵�܂�*/
bool UI::isInWindow(const RectF& drawbase)
{
	RectF window = { 0,0,Window::Size() };
	return window.intersects(Vec2(drawbase.x , drawbase.y));
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
				(*it)->SE_Play_frame();
				if (!(*it)->isOpaque_Zero())
				{
					(*it)->Opaque_Decrement();
				}
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
	switch (this->objecttype)
	{
	case ObjectType::MusouItem:		//���o�A�C�e���̎g�p
		this->MusouItem_Use();
		break;
	case ObjectType::ESCAPERogo:	//�G�X�P�[�v�������ꂽ
		this->Escape_Use();
		break;
	}
}
/*���N���b�N�������ꂽ�𔻒肵�܂�*/
bool UI::MouseLclicked()
{
	return this->collider->MouseLeftClicked();
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
/*���g�����I�u�W�F�N�g�^�C�v��Ԃ��܂�*/
UI::ObjectType UI::getObjecttype()const
{
	return this->objecttype;
}