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
	bool								       hitbace_, 
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
	if (hitbace_)
	{
		this->hitbace = new Collider(Collider::ShapeHitType::Cube,this->position,this->scale);
	}

	//DrawInterFace�𐶐�����
	if (draw_)
	{
		this->draw = new DrawInterFace();
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

	Rect src = this->draw->getSrcBace();
	/*�`�������*/
	{
		if (this->objecttype != ObjectType::Player)
		{
			this->draw->Draw(this->draw->getDrawBace(),this->draw->getSrcBace());
		}
		else
		{
			this->draw->PalletColorDraw(this->position , this->scale , Palette::Red);
		}
	}
}
bool CharaBace::Finalize()
{
	if (draw != nullptr)
	{
		delete this->draw;
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
	bool								       hitbace,
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
		if (!to->ParameterInit(taskname,objecttype,pos,scale,order,hitbace,drawinterface,moveinterface))
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
		this->draw->setDrawSrc(0,0,680,480);
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
/*�I�u�W�F�N�g�^�C�v��Back�ł��邩�𔻒肵�܂�*/
constexpr bool CharaBace::ObjectTypeCheck(const ObjectType& ObjectType_ , const ObjectType& target)const
{
	return ObjectType_ == target ? true : false;
}