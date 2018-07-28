#include "Player.h"
#include <iostream>

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
	this->draw = DrawInterFace::Addcomponent(RectF(this->position,this->scale));
	return true;
}
/*�������*/
bool Player::Finalize()
{
	return true;
}
/*�X�V����*/
void Player::UpDate()
{
	
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
	if (this->isLifeZero())
	{
		this->life = this->LifeMin();
	}
	this->life = life_;
}
/*���C�t�l��0�ȉ��ł��邩�𔻒肵�܂�*/
constexpr bool Player::isLifeZero()const
{
	return this->life <= 0 ? true : false;
}
/*���C�t�̍ŏ��l��Ԃ��܂�*/
const int Player::LifeMin()
{
	return PLAYER_LIFE_MIN;
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