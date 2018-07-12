#include <iostream>
#include <string>
#include "ResourceManager.h"

/*�R���X�g���N�^*/
DrawOrder::DrawOrder()
{
#if (_DEBUG)
	std::cout << "DrawOrder()" << std::endl;
#endif // (_DEBUG)
}
/*�f�X�g���N�^*/
DrawOrder::~DrawOrder()
{
#if (_DEBUG)
	std::cout << "~DrawOrder()" << std::endl;
#endif // (_DEBUG)
}
/*�`�揇��ݒ肵�܂�*/
void DrawOrder::setDrawOrder(float& order_)
{
	this->order = order_;
}
/*�`�揇��Ԃ��܂�*/
float DrawOrder::getDrawOrder()const
{
	return this->order;
}



/* �R���X�g���N�^ */
ResourceManager::ResourceManager()
{
#if (_DEBUG)
	std::cout << "ResourceManager()" << std::endl;
#endif // (_DEBUG)

}
/* �f�X�g���N�^ */
ResourceManager::~ResourceManager()
{
#if (_DEBUG)
	std::cout << "~ResourceManager()" << std::endl;
#endif // (_DEBUG)
}
/*�e�N�X�`�����V�X�e���ɓo�^���܂�*/
void ResourceManager::setTextrue(const std::string& texname_,Textrue* image_)
{
	/*�����̖��O���������ꍇ�͊֐����I��������*/
	for (auto it = this->textrues.begin(); it != this->textrues.end(); ++it)
	{
		if ((*it).first == texname_)
		{
			return;
		}
	}

	std::pair<std::string, Textrue*> textrue;
	textrue.first = texname_;
	textrue.second = image_;
	this->textrues.push_back(textrue);
}
/*�T�E���h���V�X�e���ɓo�^���܂�*/
void ResourceManager::setSound(const std::string& soundname_, Sound* sound_)
{
	for (auto it = this->sounds.begin(); it != this->sounds.end(); ++it)
	{
		if ((*it).first == soundname_)
		{
			return;
		}
	}

	std::pair<std::string, Sound*>  sound;
	sound.first = soundname_;
	sound.second = sound_;
	this->sounds.push_back(sound);
}
/*�o�^���Ă���e�N�X�`������w�肳�ꂽ�e�N�X�`����Ԃ��܂�*/
Textrue* ResourceManager::getTextrue(const std::string& texname_)const
{
	for (auto it = this->textrues.begin(); it != this->textrues.end(); ++it)
	{
		if ((*it).first == texname_)
		{
			return (*it).second;
		}
	}
	return nullptr;
}
/*�o�^���Ă���T�E���h����w�肳�ꂽ�T�E���h��Ԃ��܂�*/
Sound* ResourceManager::getSound(const std::string& texname_)const
{
	for (auto it = this->sounds.begin(); it != this->sounds.end(); ++it)
	{
		if ((*it).first == texname_)
		{
			return (*it).second;
		}
	}
	return nullptr;
}
/*���\�[�X��S�폜�����܂�*/
void ResourceManager::DeleteResource()
{
	this->textrues.clear();
	this->sounds.clear();
}