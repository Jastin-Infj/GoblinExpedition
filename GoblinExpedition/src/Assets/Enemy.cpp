#include "Enemy.h"
#include <iostream>
#include "../Task/Task_Game.h"
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
	this->opaque = OPAQUE_INIT;
	this->mouse_hitflag = false;
	this->musouitemkill = false;
	this->se = rm->getSound("�G����SE");
	this->se_play = false;
	this->se_frametime = SE_INITCOUNT;
	//�ǉ��̏���������
	void(Enemy::*Func[OBJECT_TYPESIZE])() = { &Enemy::Goburin_Parameter , nullptr};
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
void Enemy::Update()
{
	if (this->getleftrightinversionflag())
	{
		this->move->setMovespeed(Point(-ENEMY_MOVE_SPEED_X, 0));
		this->collider->setHitBace(this->position, this->scale);
	}
	else
	{
		this->move->setMovespeed(Point(ENEMY_MOVE_SPEED_X, 0));
		this->collider->setHitBace(this->position, this->scale);
	}
	this->move->UniformLinearMotion(this->position);
	
	/*���]������s���܂�*/
	this->LeftRightInversion();
	/*�}�E�X������s���܂�*/
	this->Mouse_Hit();
	/*�}�b�v�O������s���܂�*/
	if (this->OutsideMap() && this->getleftrightinversionflag())
	{
		this->Kill();
	}
}
/*�`������܂�*/
void Enemy::Render()
{
	/*�`���`�̍X�V*/
	this->draw->setDrawBace(this->position, this->scale);

	if (this->getleftrightinversionflag())
	{
		this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace(),Color(255,255,255, (uint32)this->opaque) ,true);
	}
	else
	{
		this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace(),Color(255,255,255,(uint32)this->opaque));
	}
}
/*�s�����������v�Z�œ��߂����܂�*/
void Enemy::Opaque_Decrement()
{
	if (this->isOpaque_Zero())
	{
		return;
	}
	this->opaque *= OPAQUE_DECREASERATE;
	if (this->opaque <= OPAQUE_MIN)
	{
		this->opaque = OPAQUE_MIN;
	}
	std::cout << this->opaque << std::endl;
}
/*�s�����x��0�ł��邩�𔻒肵�܂�*/
bool Enemy::isOpaque_Zero()const
{
	return (int)this->opaque == OPAQUE_MIN ? true : false;
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
		if (this->onHitbaceExit(temp->getHitBace()) && !this->getleftrightinversionflag() && !this->isOpaque_Zero())
		{
			/*���]�t���O��true�ɂ���*/
			this->setleftrightinversionflag(true);
			temp->Receive_Enemy();
		}
	}
}
/*�}�b�v�O�ɂ��邩�𔻒肵�܂�*/
bool Enemy::OutsideMap()
{
	return this->position.x <= -this->scale.x ? true : false;
}
/*�����蔻���`��Ԃ��܂�*/
RectF Enemy::getHitBace()const
{
	return this->collider->getHitBace();
}
/*�X�R�A��Ԃ��܂�*/
const int Enemy::getScore()
{
	return ENEMY_SCORE;
}
/*�}�E�X�ƓG�̓����蔻����s���܂�*/
void Enemy::Mouse_Hit()
{
	Player::WP player = taskSystem->GetTask_TaskName<Player>("���L����");
	if (!player.expired())
	{
		auto temp = player.lock();
		//�}�E�X����
		if (temp->MouseHit(this->collider->getHitBace()))
		{
			if (this->collider->MouseLeftPressed())
			{
				this->SE_Play();
				this->mouse_hitflag = true;
			}	
		}
		/*���N���b�N�������ꂽ��̏���*/
		if (this->mouse_hitflag && !this->isOpaque_Zero())
		{
			this->Opaque_Decrement();
		}
		else if (this->isOpaque_Zero() && !this->getleftrightinversionflag() && !this->musouitemkill)
		{
			auto game = taskSystem->GetTask_TaskName<Game>("�C���Q�[��");
			if (game)
			{
				//�X�R�A�����Z����
				game->ScoreAddition(ENEMY_SCORE);
				//���j�������Z����
				game->Enemy_DestroyingCount_Add(ENEMY_DESTROYINGSCORE);
				//���j�A�C�e���̐���
				game->MusouItem_Create();
				this->Kill();
			}
		}
	}
}
/*���o�A�C�e���t���O��ݒ�E�ύX���܂�*/
void Enemy::setMusouitemkill(const bool flag)
{
	this->musouitemkill = flag;
}
/*���o�A�C�e���t���O��Ԃ��܂�*/
bool Enemy::getMusouitemkill()const
{
	return this->musouitemkill;
}
/*����SE�𗬂��܂�*/
void Enemy::SE_Play()
{
	if (!this->se_play)
	{
		this->se_play = true;
		this->se.play();
	}
}
/*����SE�𗬂��܂�*/
void Enemy::SE_Play(const int& frametime)
{
	if (!this->se_play)
	{
		this->se_play = true;
		this->se_frametime++;
		if (this->se_frametime >= frametime)
		{
			this->SE_Play();
		}
	}
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
	this->move = MoveInterFace::Addcomponent(Point(ENEMY_MOVE_SPEED_X, ENEMY_MOVE_SPEED_Y));
}

//��������������������������������������������������������������������������������������������������������
