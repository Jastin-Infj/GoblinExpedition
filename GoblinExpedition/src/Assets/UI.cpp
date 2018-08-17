#include "UI.h"
#include "../Task/Task_Game.h"
#include "../Task/Task_Title.h"
#include "../Task/Task_Result.h"
#include "../Task/Task_HowPlay.h"
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
	/*�^�X�N����ݒ�*/
	__super::setTaskName(taskname_);
	/*�`��D�揇�ʂ�ݒ�*/
	__super::setDrawOrder(this->order = order_);

	this->position = position_;
	this->scale = scale_;
	this->objecttype = objecttype_;
	this->killcheck = false;
	this->itemuseflag = false;

	//�@�\�̐ݒ�
	void(UI::*set_parametar[])(const Rect&) =
	{
		&UI::Normal,
		&UI::AddCollider
	};
	(this->*set_parametar[(int)initformat])(src);

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
//��������������������������������������������������������������������������������������������������������

/*�����ݒ�Őݒ肷�鐗�`�@�摜�T�C�Y���̕`�������*/
void UI::Normal(const Rect& src_)
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), src_);
	this->draw->setTexture(rm->getTexture(this->getTaskname().second));
}
/*�����蔻��̐ݒ�����鐗�`�@�摜�T�C�Y���̓����蔻��ƕ`������܂�*/
void UI::AddCollider(const Rect& src_)
{
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), src_);
	this->draw->setTexture(rm->getTexture(this->getTaskname().second));
	this->collider = Collider::Addcomponent(Collider::ShapeT::Rect,this->position, this->scale);
}
/*���N���b�N�������ꂽ��̏������܂Ƃ߂��֐�*/
void UI::TitleStartUI_LeftClicked()
{
	auto title = taskSystem->GetTask_TaskName<Title>("�^�C�g��");
	if (title)
	{
		title->Kill();
	}
}
/*�}�E�X�ō��N���b�N�������ꂽ��̏������s���܂�*/
void UI::ToGameUI_LeftClicked()
{
	auto howplay = taskSystem->GetTask_TaskName<HowPlay>("�V�ѕ�");
	if (howplay)
	{
		howplay->Kill();
	}
}
/*�^�C�g���֖߂�UI�������ꂽ��̏������s���܂�*/
void UI::TotitleUI_LeftClicked()
{
	auto result = taskSystem->GetTask_TaskName<Result>("���U���g");
	if (result)
	{
		result->Kill();
	}
}
/*�^�C�g���p�I���{�^��UI�̐ݒ���s���܂�*/
void UI::TitleExitUI_LeftClicked()
{
	taskSystem->Application_Exit();
}
//��������������������������������������������������������������������������������������������������������

/*���o�A�C�e�����g�p���܂�*/
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
/*�Q�[�����I�������܂�*/
void UI::Escape_Use()
{
	auto game = taskSystem->GetTask_TaskName<Game>("�C���Q�[��");
	if (game)
	{
		game->ChengeGameState(Game::GameState::ESCAPE);
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
					if (!(*it)->getleftrightinversionflag())
					{
						//�X�R�A�̐���
						(*it)->KillScoreCreate();
					}
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
		this->itemuseflag = false;
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
	case ObjectType::TitleStart:
		this->TitleStartUI_LeftClicked();	//���N���b�N�ŉ����ꂽ��̏���
		break;
	case ObjectType::toGame:
		this->ToGameUI_LeftClicked();		//���N���b�N�ŉ����ꂽ��̏���
		break;
	case ObjectType::TitleExit:
		this->TitleExitUI_LeftClicked();	//���N���b�N�������ꂽ��̏���
		break;
	case ObjectType::toTitle:
		this->TotitleUI_LeftClicked();		//���N���b�N�������ꂽ��̏���
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
/*�A�C�e�����g�p�����ǂ������肵�܂�*/
bool UI::isUseItem()const
{
	return this->itemuseflag;
}