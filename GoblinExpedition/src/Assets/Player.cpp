#include "Player.h"
#include <iostream>
#include "../TaskSystem/TaskSystem.h"
#include "UI.h"
#include "Enemy.h"

#include "../Task/Task_Game.h"
/*�R���X�g���N�^*/
Player::Player()
{
#ifdef _DEBUG
	std::cout << "Player()" << std::endl;
#endif // _DEBUG
}
/*�f�X�g���N�^*/
Player::~Player()
{
	this->Finalize();
#ifdef _DEBUG
	std::cout << this->getTaskname().second << "~Player()" << std::endl;
#endif // _DEBUG
}
/*�p�����[�^�̏������ݒ�*/
bool Player::Init_Parameter(const TASKNAME& taskname_, const Vec2& position_, const Point& scale_, const int& life_, const float& order_)
{
	/*�^�X�N����ݒ�*/
	__super::setTaskName(taskname_);
	/*�`��D�揇�ʂ�ݒ�*/
	__super::setDrawOrder(this->order = order_);


	this->position = position_;
	this->scale = scale_;
	this->life = life_;

	//�ǉ��̏���������
	this->collider = Collider::Addcomponent(Collider::ShapeT::RectF, Vec2(this->position.x - this->scale.x, 0), Point(8, Window::Size().y));
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale));
	this->shapemouse = ShapeMouseCursor::AddComponent<Point>(ShapeMouseCursor::ShapeT::Rect, Point(MOUSE_SCALE_W, MOUSE_SCALE_H));
	this->shapemouse->MouseColliderAddComponent();
	this->LifeUICreate();

	return true;
}
/*�������*/
bool Player::Finalize()
{
	return true;
}
/*�X�V����*/
void Player::Update()
{
	////�}�E�X�̍��W���X�V
	this->shapemouse->Posupdate();
	////�����蔻���`�̍X�V
	this->shapemouse->MouseHitBaceupdate();
	//�}�E�X����Ƒ��̃I�u�W�F�N�g�̐ڐG���m������
	this->Mousehitupdate();

	if (this->isLifeZero())
	{
		auto game = taskSystem->GetTask_TaskName<Game>("�C���Q�[��");
		if (game)
		{
			game->ChengeGameState(Game::GameState::LifeZero);
		}
	}
}
/*�`������܂�*/
void Player::Render()
{
	this->draw->PaletteColorDraw(this->collider->gethitbaceRect(), Palette::Red);
	this->draw->PaletteColorDraw(this->draw->getDrawBace(), Palette::White);
}
/*�}�E�X�̓����蔻��𖈃t���[�����m���܂�*/
void Player::Mousehitupdate()
{
	{
		//���o�A�C�e���̎g�p
		auto musouitems = taskSystem->GetTasks_GroupName<UI>("�A�C�e��");
		auto musouitems_it = musouitems->rbegin();
		if (musouitems)
		{
			for (auto it = musouitems->begin(); it != musouitems->end(); ++it)
			{
				if ((*it)->Hit(this->shapemouse->getrectHitbace()))
				{
					if (this->shapemouse->LeftClicked((*it)->getRecthitbace()))
					{
						(*musouitems_it)->Receive_Player();
					}
				}
			}
		}
	}
	{
		auto escape = taskSystem->GetTask_TaskName<UI>("�G�X�P�[�v���S");
		if (escape)
		{
			if (escape->Hit(this->shapemouse->getrectHitbace()))
			{
				if (this->shapemouse->LeftClicked(escape->getRecthitbace()))
				{
					escape->Receive_Player();
				}
			}
		}
	}
}
/*Player�̗̑͒l��Ԃ��܂�*/
int Player::getLife()const
{
	return this->life;
}
/*Player�̗̑͒l���𐶐����܂�*/
void Player::LifeUICreate()
{
	{
		rm->setTexture("�v���C�����C�t", Texture(L"./data/image/heart.png"));
		for (int i = 0; i < this->life; ++i)
		{
			auto player_life = UI::Create(TASKNAME("UI", "�v���C�����C�t"), UI::ObjectType::PlayerLife, Vec2(Window::Size().x - 64 - i * 64, 0), Point(64, 48), UI::InitFormat::Normal,Rect(0,0,64,48));
		}
	}
}
/*Player�̗̑͒l��ύX�E�ݒ肵�܂�*/
void Player::setLife(int life_)
{
	this->life = life_;
	if (this->isLifeZero())
	{
		this->life = this->LifeMin();
	}
	else if (this->isLifeMax())
	{
		this->life = this->LifeMax();
	}
}
/*���C�t�l��0�ȉ��ł��邩�𔻒肵�܂�*/
constexpr bool Player::isLifeZero()const
{
	return this->life < PLAYER_LIFE_MIN ? true : false;
}
/*���C�t�l������ɒB���Ă��邩�𔻒肵�܂�*/
constexpr bool Player::isLifeMax()const
{
	return this->life >= PLAYER_LIFE_MAX ? true : false;
}
/*���C�t�̍ŏ��l��Ԃ��܂�*/
const int Player::LifeMin()
{
	return PLAYER_LIFE_MIN;
}
/*���C�t�̏���l��Ԃ��܂�*/
const int Player::LifeMax()
{
	return PLAYER_LIFE_MAX;
}
/*���C�t�l�����������܂�*/
void Player::LifeDecrement()
{
	this->life -= PLAYER_LIFE_DECREMENT;
}
/*�G�Ɠ����荶�N���b�N�������ꂽ���ǂ����𔻒肵�܂�*/
bool Player::MouseHit_toEnemy(const Rect& target)const
{
	return this->shapemouse->LeftClicked(target);
}
/*Enemy�ɐڐG�������Ƃ̏���*/
void Player::Receive_Enemy()
{
	if (this->isLifeZero())
	{
		//�Q�[���I�[�o�[�����ֈڍs����
		this->Kill();
	}
	this->LifeDecrement();

	/*UI�̏������s��*/
	auto playerlifeui = taskSystem->GetTasks_TaskName<UI>("�v���C�����C�t");
	auto it = playerlifeui->rbegin();
	if (playerlifeui)
	{
		(*it)->Kill();
	}
}
/*�I�u�W�F�N�g�𐶐����܂�*/
TaskObject::SP Player::Create(const TASKNAME& taskname, const Vec2& position, const Point& scale, const int& life_, const float& order, bool flag)
{
	Player::SP create = Player::SP(new Player());
	if (create)
	{
		/*�E�B�[�N�|�C���^���������Ă���*/
		create->me = create;
		if (!create->Init_Parameter(taskname, position, scale, life_, order))
		{
			/*���������o���Ȃ��ꍇ�͏�������*/
			create->Kill();
		}
		if (flag)
		{
			taskSystem->Add(create);
		}
		return create;
	}
	return nullptr;
}