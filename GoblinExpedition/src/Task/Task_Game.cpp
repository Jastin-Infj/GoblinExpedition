#include "Task_Game.h"
#include "../TaskSystem/TaskSystem.h"
#include "../ResourceManager/ResourceManager.h"

#include <iostream>

#include "../Assets/GameObject.h"
#include "../Assets/Enemy.h"
#include "../Assets/Player.h"
#include "../Assets/UI.h"

/* �R���X�g���N�^ */
Game::Game()
{
#if _DEBUG
	std::cout << "Game()" << std::endl;
#endif // _DEBUG
}
/* �f�X�g���N�^ */
Game::~Game()
{
#if _DEBUG
	std::cout << "~Game()" << std::endl;
#endif // _DEBUG

}
/* ���������� */
bool Game::Init(const std::pair<std::string,std::string>& taskname_)
{
	__super::setTaskName(taskname_);
	this->setDrawOrder(1.0f);

	//�ǉ��������I�u�W�F�N�g�������ɋL�q����
	
	/*ResourceManager�Ƀ��\�[�X��ǉ�����*/
	{
		//�摜�̎w��
		rm->setTexture("�C���Q�[���w�i", Texture(L"./data/image/doukutu.png"));
		auto back = UI::Create(std::pair<std::string, std::string>("�w�i", "�C���Q�[���w�i"),UI::ObjectType::Background ,Point(0, 0), Point(Window::Size().x, Window::Size().y), 0.1f);
	}
	{
		rm->setTexture("�S�u����", Texture(L"./data/image/Goburin.png"));
		auto enemy = Enemy::Create(std::pair<std::string, std::string>("�����X�^�[", "�S�u����") ,Enemy::ObjectType::Goburin ,Point(-48, Window::Size().y / 2), Point(64, 64), 0.8f);
	}
	{
		auto player = Player::Create(std::pair<std::string, std::string>("�v���C��", "���L����"),Point(Window::Size().x - 32 ,Window::Size().y / 2), Point{32,32} , 5 , 0.8f);
	}
	return true;
}
/* �X�V���� */
void Game::UpDate()
{

}
/*�������*/
bool Game::Finalize()
{
	/*�Q�[���^�X�N���I�������瓯���ɂ����Ő��������I�u�W�F�N�g���폜����*/
	auto backs = taskSystem->GetTasks<TaskObject>(std::pair<std::string, std::string>("�w�i", "�C���Q�[���w�i"));
	for (auto it = backs->begin(); it != backs->end(); ++it)
	{
		(*it)->Kill();
	}
	auto enemys = taskSystem->GetTasks<TaskObject>(std::pair<std::string, std::string>("�����X�^�[", "�S�u����"));
	for (auto it = enemys->begin(); it != enemys->end(); ++it)
	{
		(*it)->Kill();
	}
	auto players = taskSystem->GetTasks<TaskObject>(std::pair<std::string, std::string>("�v���C��", "���L����"));
	for (auto it = players->begin(); it != players->end(); ++it)
	{
		(*it)->Kill();
	}
	return true;
}
/*�I�u�W�F�N�g�𐶐����܂�*/
TaskObject::SP Game::Create(const std::pair<std::string, std::string>& taskname, bool flag)
{
	Game::SP to = Game::SP(new Game());
	if (to)
	{
		/*�����̃f�[�^��n��*/
		to->me = to;
		if (!to->Init(taskname))
		{
			to->Kill();
		}
		if (flag)
		{
			taskSystem->Add(to);
		}
		return to;
	}
	return nullptr;
}