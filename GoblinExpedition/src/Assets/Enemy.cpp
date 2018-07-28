#include "Enemy.h"
#include <iostream>
/*�R���X�g���N�^*/
Enemy::Enemy()
{
#ifdef _DEBUG
	std::cout << "Enemy()" << std::endl;
#endif // _DEBUG
}
/*�f�X�g���N�^*/
Enemy::~Enemy()
{
	this->Finalize();
#ifdef _DEBUG
	std::cout << this->getTaskname().second << "~Enemy()" << std::endl;
#endif // _DEBUG
}
/*�p�����[�^�̏������ݒ�*/
bool Enemy::Init_Parameter(const TASKNAME& taskname_, const ObjectType& objecttype_, const Vec2& position_, const Point& scale_, const float& order_)
{
	/*�^�X�N����ݒ�*/
	__super::setTaskName(taskname_);
	/*�`��D�揇�ʂ�ݒ�*/
	__super::setDrawOrder(this->order = order_);

	this->position = position_;
	this->scale = scale_;
	this->objecttype = objecttype_;

	//�ǉ��̏���������
	void(Enemy::*Func[2])() = { &Enemy::Goburin_Parameter , nullptr};
	(this->*Func[(int)this->objecttype])();
	this->setleftrightinversionflag(false);

	return true;
}
/*�������*/
bool Enemy::Finalize()
{
	return true;
}
/*�X�V����*/
void Enemy::UpDate()
{
	if (this->getleftrightinversionflag())
	{
		this->move->setMovespeed(Point(-3, 0));
		this->collider->setHitBace(this->position, this->scale);
	}
	else
	{
		this->move->setMovespeed(Point(3, 0));
		this->collider->setHitBace(this->position, this->scale);
	}
	this->move->UniformLinearMotion(this->position);
	
	/*���]������s���܂�*/
	this->LeftRightInversion();
	if (this->OutsideMap() && this->getleftrightinversionflag())
	{
		this->Kill();
	}
}
/*�`������܂�*/
void Enemy::Render()
{
	this->draw->setDrawBace(this->position, this->scale);
	this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
}
/*Player�����蔻���`�ƐڐG������s���܂�*/
bool Enemy::onHitbaceExit(const RectF& target)const
{
	return this->collider->Hit(target);
}
/*���E���]�t���O��Ԃ��܂�*/
bool Enemy::getleftrightinversionflag()const
{
	return this->leftrightinversionflag;
}
/*���E���]�t���O��ݒ肵�܂�*/
void Enemy::setleftrightinversionflag(bool flag)
{
	this->leftrightinversionflag = flag;
}
/*���E���]�t���O���`�F���W���܂�*/
void Enemy::changeleftrightinversionflag()
{
	this->leftrightinversionflag = !this->leftrightinversionflag;
}
/*���E���]��������܂�*/
void Enemy::LeftRightInversion()
{
	Player::WP player = taskSystem->GetTask_TaskName<Player>("���L����");
	if (!player.expired())
	{
		Player::SP temp = player.lock();
		if (this->onHitbaceExit(temp->getHitBace()))
		{
			/*���]�t���O��true�ɂ���*/
			this->setleftrightinversionflag(true);
		}
	}
	else
	{
		return;
	}
}
/*�}�b�v�O�ɂ��邩�𔻒肵�܂�*/
bool Enemy::OutsideMap()
{
	return this->position.x <= -this->scale.x ? true : false;
}
/*�G�𐶐����܂�*/
TaskObject::SP Enemy::Create(const TASKNAME& taskname_, const ObjectType& objecttype_, const Vec2& position_, const Point& scale_, const float& order_, const bool flag)
{
	Enemy::SP enemy = Enemy::SP(new Enemy());
	if (enemy)
	{
		enemy->me = enemy;
		if (!enemy->Init_Parameter(taskname_, objecttype_, position_, scale_, order_))
		{
			enemy->Kill();
		}
		if (flag)
		{
			taskSystem->Add(enemy);
		}
		return enemy;
	}
	return nullptr;
}

//��������������������������������������������������������������������������������������������������������

/*�S�u�����̐ݒ���s���܂�*/
void Enemy::Goburin_Parameter()
{
	//�e�N�X�`���̓\��t��
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 64, 64));
	this->draw->setTexture(rm->getTexture("�S�u����"));

	//�����蔻��̐ݒ�
	this->collider = Collider::Addcomponent(Collider::ShapeHitType::Cube, this->position, this->scale);

	//�����ړ��ʂ̐ݒ�
	this->move = MoveInterFace::Addcomponent(Point(3, 0));
}

//��������������������������������������������������������������������������������������������������������
