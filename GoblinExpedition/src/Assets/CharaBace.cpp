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
	}
	else
	{
		this->draw = nullptr;
	}
	if (draw != nullptr)
	{
		/*�ΏۃI�u�W�F�N�g�ɂ���Ă��ꂼ��̃e�N�X�`����\��t����*/
		this->draw->setTexture(this->getResoruceManagerTexture());
		//�`���`�̐���
		this->draw->setDrawBace(this->position, this->scale);
	}

	//�ړ��@�\������
	if (move_)
	{
		this->move = new MoveInterFace();
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
Texture CharaBace::getResoruceManagerTexture()const
{
	switch (this->objecttype)
	{
		/* �w�i */
	case ObjectType::Back:
		//�摜����`�̐���
		this->draw->setDrawSrc(0, 0, 680, 480);
		//�e�N�X�`���̓\��t��
		return rm->getTexture("�C���Q�[���w�i");
		break;
		/* UI */
	case ObjectType::UI:
		//�摜����`�̐���

		//�e�N�X�`���̓\��t��
		return rm->getTexture("���C�t");
		break;
		/* �v���C�� */
	case ObjectType::Player:

		break;
		/* �G */
	case ObjectType::Enemy:
		//�摜����`�̐���
		this->draw->setDrawSrc(0, 0, 64, 64);
		//�e�N�X�`���̓\��t��
		return rm->getTexture("�S�u����");
		break;
		/* �A�C�e�� */
	case ObjectType::Item:
		//�摜����`�̐���

		//�e�N�X�`���̓\��t��
		return rm->getTexture("�A�C�e��");
		break;
	default:
		break;
	}
	/*��̃e�N�X�`��*/
	return Texture();
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
	default:
		break;
	}
}
/*�I�u�W�F�N�g�^�C�v��target�ł��邩�𔻒肵�܂�*/
constexpr bool CharaBace::ObjectTypeCheck(const ObjectType& ObjectType_, const ObjectType& target)const
{
	return ObjectType_ == target ? true : false;
}