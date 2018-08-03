#include "Player.h"
#include <iostream>
#include "../TaskSystem/TaskSystem.h"
#include "UI.h"

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
bool Player::Init_Parameter(const TASKNAME& taskname_ , const Vec2& position_, const Point& scale_ ,const int& life_  ,  const float& order_)
{
	/*�^�X�N����ݒ�*/
	__super::setTaskName(taskname_);
	/*�`��D�揇�ʂ�ݒ�*/
	__super::setDrawOrder(this->order = order_);


	this->position = position_;
	this->scale = scale_;
	this->life = life_;

	this->LifeUICreate();

	//�ǉ��̏���������
	this->collider = Collider::Addcomponent(Collider::ShapeHitType::Cube, Vec2(this->position.x - this->scale.x, 0), Point(8, Window::Size().y));
	this->mouse_colider = Collider::Addcomponent(Collider::ShapeHitType::Cube, Vec2(this->mouse_cursor_position), Point(MOUSE_SCALE_W, MOUSE_SCALE_H));
	this->draw = DrawInterFace::Addcomponent(RectF(this->position,this->scale));


	return true;
}
/*�������*/
bool Player::Finalize()
{
	if (this->mouse_colider)
	{
		delete this->mouse_colider;
	}
	return true;
}
/*�X�V����*/
void Player::Update()
{
	this->mouse_cursor_position = this->Mouse_Pos();
	/*�����蔻��̍X�V*/
	this->mouse_colider->setHitBace(this->mouse_cursor_position, Point(MOUSE_SCALE_W, MOUSE_SCALE_H));

	//���o�A�C�e���̎g�p
	auto musouitems = taskSystem->GetTasks_TaskName<UI>("���o�A�C�e��");
	auto musouitems_it = musouitems->rbegin();

	if (musouitems)
	{
		for (auto it = musouitems->begin(); it != musouitems->end(); ++it)
		{
			if ((*it)->Hit(this->mouse_colider->getHitBace()))
			{
				if ((*it)->MouseLclicked())
				{
					if (this->mouseclickcount == 0)
					{
						(*musouitems_it)->Receive_Player();
					}
					this->mouseclickcount++;
				}
				else
				{
					mouseclickcount = 0;
				}
			}
		}
	}
}
/*�`������܂�*/
void Player::Render()
{
	this->draw->PaletteColorDraw(this->collider->getHitBace(),Palette::Red);
	this->draw->PaletteColorDraw(this->draw->getDrawBace(), Palette::White);
}
/*�����蔻���Ԃ��܂�*/
RectF Player::getHitBace()const
{
	return this->collider->getHitBace();
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
			auto player_life = UI::Create(TASKNAME("UI", "�v���C�����C�t"), UI::ObjectType::PlayerLife, Vec2(Window::Size().x - 64 - i * 64, 0), Point(64, 48));
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
	else if(this->isLifeMax())
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
/*�}�E�X���W�𖈎��X�V���܂�*/
Vec2 Player::Mouse_Pos()const
{
	return Mouse::Pos();
}
/*�}�E�X���W��Ԃ��܂�*/
Vec2 Player::getMousePos()const
{
	return this->mouse_cursor_position;
}
/*�}�E�X�Ɠ����蔻����s���܂�*/
bool Player::MouseHit(const RectF& target)const
{
	return this->mouse_colider->Hit(target);
}
/*�I�u�W�F�N�g�𐶐����܂�*/
TaskObject::SP Player::Create(const TASKNAME& taskname, const Vec2& position, const Point& scale,const int& life_ ,const float& order, bool flag)
{
	Player::SP create = Player::SP(new Player());
	if (create)
	{
		/*�E�B�[�N�|�C���^���������Ă���*/
		create->me = create;
		if (!create->Init_Parameter(taskname, position, scale,life_ ,order))
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