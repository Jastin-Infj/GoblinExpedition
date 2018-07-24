#include "CharaBace.h"
#include "../TaskSystem/TaskSystem.h"
#include "../ResourceManager/ResourceManager.h"
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
bool CharaBace::ParameterInit(const std::pair<std::string, std::string>& taskname_, ObjectType objecttype_, Point& pos, Point& scale_,float order_)
{
	__super::setTaskName(taskname_);

	//�Ώۂ̃^�C�v�ݒ�
	this->objecttype = objecttype_;
	
	//DrawInterFace�𐶐�����
	this->draw = new DrawInterFace();
	/*�ΏۃI�u�W�F�N�g�ɂ���Ă��ꂼ��̃e�N�X�`����\��t����*/
	this->draw->setTexture(this->getResoruceManagerTexture());


	//�������W�ʒu�̐ݒ�
	this->position = pos;
	//�`��T�C�Y��ݒ�
	this->scale = scale_;
	//�`���`�̐���
	this->draw->setDrawBace(this->position, this->scale);
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
		this->draw->Draw(this->draw->getDrawBace(),this->draw->getSrcBace());
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
CharaBace::SP CharaBace::Create(const std::pair<std::string, std::string>& taskname, ObjectType objecttype, Point pos, Point scale, float order, bool flag)
{
	CharaBace::SP to = CharaBace::SP(new CharaBace());
	if (to)
	{
		/*�����̃A�h���X�l��n��*/
		to->me = to;
		/*�e�l�̏������l��ݒ�*/
		if (!to->ParameterInit(taskname,objecttype,pos,scale,order))
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
		//�摜����`�̐���

		//�e�N�X�`���̓\��t��
		return rm->getTexture("�v���C��");
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