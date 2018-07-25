#include "CharaBace.h"
#include "../TaskSystem/TaskSystem.h"
#include "../ResourceManager/ResourceManager.h"
#include "../InterFace/Collider.hpp"
#include "../InterFace/MoveInterFace.hpp"
#include <iostream>
#include <Windows.h>
/*�R���X�g���N�^*/
CharaBace::CharaBace()
{
#if _DEBUG
	std::cout << "CharaBace()" << std::endl;
#endif // _DEBUG
}
/*�f�X�g���N�^*/
CharaBace::~CharaBace()
{
#if _DEBUG
	std::cout << "~CharaBace()" << std::endl;
#endif // _DEBUG
	this->Finalize();
}
/*���������������܂�*/
bool CharaBace::ParameterInit(
	const std::pair<std::string, std::string>& taskname_,
	ObjectType								   objecttype_,
	const Point&							   pos,
	const Point&							   scale_,
	float									   order_,
	bool								       collider_,
	bool							           draw_,
	bool						               move_
)
{
	__super::setTaskName(taskname_);

	//�������W�ʒu�̐ݒ�
	this->position = pos;
	//�`��T�C�Y��ݒ�
	this->scale = scale_;

	//�Ώۂ̃^�C�v�ݒ�
	this->objecttype = objecttype_;

	if (this->ObjectTypeCheck(this->objecttype, ObjectType::Enemy))
	{
		this->enemyfunction = new EnemyFunction;
		this->enemyfunction->setleftrightinversionflag(false);
	}
	else
	{
		this->enemyfunction = nullptr;
	}

	//�����蔻��@�\
	if (collider_)
	{
		//�����蔻���`��ݒ�
		this->setObjectTypeCollider();
	}
	else
	{
		this->collider = nullptr;
	}

	//DrawInterFace�𐶐�����
	if (draw_)
	{
		this->draw = new DrawInterFace();
		/*�ΏۃI�u�W�F�N�g�ɂ���Ă��ꂼ��̃e�N�X�`����\��t����*/
		this->setResoruceManagerTexture();
		//�`���`�̐���
		this->draw->setDrawBace(this->position, this->scale);
	}
	else
	{
		this->draw = nullptr;
	}

	//�ړ��@�\������
	if (move_)
	{
		this->move = new MoveInterFace();
		this->setObjectTypeMoveSpeed();
	}
	else
	{
		this->move = nullptr;
	}

	//�`��D�揇�ʂ̐ݒ�
	this->setDrawOrder(order_);


	return true;
}
/*�X�V����*/
void CharaBace::UpDate()
{
	/*�ړ��o����I�u�W�F�N�g�͈ړ����[�V�������܂�*/
	if (this->move != nullptr)
	{
		this->ObjectTypeMove();
	}
	
}
/*�`�揈��*/
void CharaBace::Render()
{
	/*�A�h���X�l��nullptr*/
	if (!draw)
	{
		MessageBox(NULL, L"�A�h���X�l���~�X���Ă��܂�", L"���g��nullptr�ł���", MB_OK);
	}
	/*�`�������*/
	{
		Rect src = this->draw->getSrcBace();
		this->ObjecytypeDraw();
	}
}
bool CharaBace::Finalize()
{
	if (this->enemyfunction != nullptr)
	{
		delete this->enemyfunction;
		this->enemyfunction = nullptr;
	}
	if (this->collider != nullptr)
	{
		delete this->collider;
		this->collider = nullptr;
	}
	if (this->draw != nullptr)
	{
		delete this->draw;
		this->draw = nullptr;
	}
	if (this->move != nullptr)
	{
		delete this->move;
		this->move = nullptr;
	}
	return true;
}
/*�I�u�W�F�N�g�̐���*/
CharaBace::SP CharaBace::Create(
	const std::pair<std::string, std::string>& taskname,
	ObjectType								   objecttype,
	const Point&							   pos,
	const Point&							   scale,
	float									   order,
	bool								       collider,
	bool									   drawinterface,
	bool								       moveinterface,
	bool									   flag
)
{
	CharaBace::SP to = CharaBace::SP(new CharaBace());
	if (to)
	{
		/*�����̃A�h���X�l��n��*/
		to->me = to;
		/*�e�l�̏������l��ݒ�*/
		if (!to->ParameterInit(taskname, objecttype, pos, scale, order, collider, drawinterface, moveinterface))
		{
			/*���������������Ȃ���΍폜*/
			to->Kill();
		}
		if (flag)
		{
			/*�V�X�e���ɓo�^*/
			taskSystem->Add(to);
		}
		return to;
	}
	return nullptr;
}
/*ResourceManager����Texture��\��t�����܂�*/
void CharaBace::setResoruceManagerTexture()const
{
	switch (this->objecttype)
	{
		/* �w�i */
	case ObjectType::Back:
		//�摜����`�̐���
		this->draw->setDrawSrc(0, 0, 680, 480);
		//�e�N�X�`���̓\��t��
		this->draw->setTexture(rm->getTexture("�C���Q�[���w�i"));
		break;
		/* UI */
	case ObjectType::UI:
		//�摜����`�̐���

		//�e�N�X�`���̓\��t��
		this->draw->setTexture(rm->getTexture("���C�t"));
		break;
		/* �v���C�� */
	case ObjectType::Player:

		break;
		/* �G */
	case ObjectType::Enemy:
		//�摜����`�̐���
		this->draw->setDrawSrc(0, 0, 64, 64);
		//�e�N�X�`���̓\��t��
		this->draw->setTexture(rm->getTexture("�S�u����"));
		break;
		/* �A�C�e�� */
	case ObjectType::Item:
		//�摜����`�̐���

		//�e�N�X�`���̓\��t��
		this->draw->setTexture(rm->getTexture("�A�C�e��"));
		break;
	default:
		break;
	}
}
/*�I�u�W�F�N�g�^�C�v�ɂ���ĕ`����@��ω������܂�*/
void CharaBace::ObjecytypeDraw()
{
	switch (this->objecttype)
	{
	case ObjectType::Player:
		this->draw->PaletteColorDraw(this->draw->getDrawBace(), Palette::Red);
		//�����蔻���`�`��
		this->draw->PaletteColorDraw(this->collider->getHitBace(), Palette::White);
		break;
	case ObjectType::Enemy:
		if (this->enemyfunction->getleftrightinversionflag())
		{
			this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace(),true);
		}
		else
		{
			this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
		}
		break;
	default:
		this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
		break;
	}
}
/*�����蔻���`���e���ݒ肵�܂�*/
void CharaBace::setObjectTypeCollider()
{
	switch (this->objecttype)
	{
	case ObjectType::Player:
		this->collider = new Collider(Collider::ShapeHitType::Cube, Point(this->position.x - this->scale.x , 0), Point(8, Window::Size().y));
		break;
	case ObjectType::Enemy:
		this->collider = new Collider(Collider::ShapeHitType::Cube, this->position, this->scale);
		break;
	default:
		break;
	}
}
/*�I�u�W�F�N�g�^�C�v�ɂ���Ĉړ��ʂ̐ݒ���s���܂�*/
void CharaBace::setObjectTypeMoveSpeed()
{
	switch (this->objecttype)
	{
	case ObjectType::Enemy:
		if (this->enemyfunction->getleftrightinversionflag())
		{
			this->move->setMovespeed(Point(-3,0));
		}
		else
		{
			this->move->setMovespeed(Point(3, 0));
		}
		break;
	default:
		break;
	}
}
/*�I�u�W�F�N�g�^�C�v�ɂ���Ĉړ����@��ݒ肵�܂�*/
void CharaBace::ObjectTypeMove()
{
	switch (this->objecttype)
	{
	case ObjectType::Enemy:
		//���������^���œ���
		this->move->UniformLinearMotion(this->position);
		//��`���Đݒ�
		if (this->draw != nullptr)
		{
			this->draw->setDrawBace(this->position, this->scale);
		}
		if (this->collider != nullptr)
		{
			this->collider->setHitBace(this->position, this->scale);
		}

		//�}�E�X�����蔻�菈��
		if (this->collider->MouseLeftPressed())
		{
			//�G��|��
			this->Kill();
		}

		//�ڐG���]�t���O
		{
			if (ObjectTypeCheck(this->objecttype, ObjectType::Enemy))
			{
				auto enemy = taskSystem->GetTask_TaskName<CharaBace>("�S�u����");
				auto player = taskSystem->GetTask_TaskName<CharaBace>("���L����");
				if (this->enemyfunction->onHitbaceExit(enemy, player))
				{
					//�X�s�[�h�ݒ���Đݒ�
					this->setObjectTypeMoveSpeed();
					//���E���]�t���O��true�ɂ���
					this->enemyfunction->setleftrightinversionflag(true);
				}
			}
		}
		break;
	default:
		break;
	}
}
/*�I�u�W�F�N�g�^�C�v��target�ł��邩�𔻒肵�܂�*/
constexpr bool CharaBace::ObjectTypeCheck(const ObjectType& ObjectType_, const ObjectType& target)const
{
	return ObjectType_ == target ? true : false;
}
/*���W��ݒ�E�ύX���܂�*/
void CharaBace::setPosition(const Point& pos)
{
	this->position = pos;
}
/*���݂̍��W��Ԃ��܂�*/
Point CharaBace::getPosition()const
{
	return this->position;
}
/*�I�u�W�F�N�g�^�C�v��Ԃ��܂�*/
ObjectType CharaBace::getObjectType()const
{
	return this->objecttype;
}


//��������������������������������������������������������������������������������������������������

/*Player�����蔻���`�ƐڐG������s���܂�*/
bool CharaBace::EnemyFunction::onHitbaceExit(const CharaBace::SP& me_ , const CharaBace::SP& target_)const
{
	if (me_->collider != nullptr && target_->collider != nullptr)
	{
		return me_->collider->Hit(target_->collider->getHitBace());
	}
	return false;
}
/*���E���]�t���O��Ԃ��܂�*/
bool CharaBace::EnemyFunction::getleftrightinversionflag()const
{
	return this->leftrightinversionflag;
}
/*���E���]�t���O��ݒ肵�܂�*/
void CharaBace::EnemyFunction::setleftrightinversionflag(bool flag)
{
	this->leftrightinversionflag = flag;
}
/*���E���]�t���O���`�F���W���܂�*/
void CharaBace::EnemyFunction::changeleftrightinversionflag()
{
	this->leftrightinversionflag = !this->leftrightinversionflag;
}

//��������������������������������������������������������������������������������������������������

