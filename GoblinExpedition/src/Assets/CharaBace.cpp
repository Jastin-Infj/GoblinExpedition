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
	const Point&							   pos,
	const Point&							   scale_,
	float									   order_,
	bool							           draw_,
	bool								       collider_,
	bool						               move_
)
{
	__super::setTaskName(taskname_);

	//�������W�ʒu�̐ݒ�
	this->position = pos;
	//�`��T�C�Y��ݒ�
	this->scale = scale_;

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
		break;
		/* UI */
	case ObjectType::UI:
		//�摜����`�̐���
		if (this->isTasknameSecond("�v���C�����C�t"))
		{
			
		}
		break;
		/* �v���C�� */
	case ObjectType::Player:

		break;
		/* �G */
	case ObjectType::Enemy:
		//�摜����`�̐���
		
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
		
		break;
	case ObjectType::Enemy:
		
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

		if (this->enemyfunction->getleftrightinversionflag() && this->position.x <= -this->scale.x)
		{
			std::cout << "�}�b�v�O" << std::endl;
			this->Kill();
		}
		else
		{
			std::cout << Window::GetPos().x << "   " << this->position.x << std::endl;
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



//��������������������������������������������������������������������������������������������������



//��������������������������������������������������������������������������������������������������

