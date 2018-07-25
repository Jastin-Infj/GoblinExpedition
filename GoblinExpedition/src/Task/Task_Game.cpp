#include "Task_Game.h"
#include "../TaskSystem/TaskSystem.h"

#include "../InterFace/ObjectType.h"
#include "../Assets/CharaBace.h"
#include "../ResourceManager/ResourceManager.h"

#include <iostream>
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
		auto back = CharaBace::Create(std::pair<std::string, std::string>("�w�i", "�C���Q�[���w�i"), ObjectType::Back, Point(0, 0), Point(Window::Size().x, Window::Size().y), 0.1f,false,true);
	}
	{
		rm->setTexture("�S�u����", Texture(L"./data/image/Goburin.png"));
		auto enemy = CharaBace::Create(std::pair<std::string, std::string>("�����X�^�[", "�S�u����"), ObjectType::Enemy, Point(0, Window::Size().y / 2), Point(64, 64), 0.8f,false,true,true);
	}
	{
		auto player = CharaBace::Create(std::pair<std::string, std::string>("�v���C��", "���L����"), ObjectType::Player, Point(Window::Size().x - 32 ,Window::Size().y / 2), Point{32,32}, 0.8f,true,true);
		auto mouse = CharaBace::Create(std::pair<std::string, std::string>("�}�E�X", "�v���C��"), ObjectType::Mouse, Point(Mouse::Pos()), Point{}, 0.8f,false,true);
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
	auto backs = taskSystem->GetTasks<CharaBace>(std::pair<std::string, std::string>("�w�i", "�C���Q�[���w�i"));
	for (auto it = backs->begin(); it != backs->end(); ++it)
	{
		(*it)->Kill();
	}
	auto enemys = taskSystem->GetTasks<CharaBace>(std::pair<std::string, std::string>("�����X�^�[", "�S�u����"));
	for (auto it = enemys->begin(); it != enemys->end(); ++it)
	{
		(*it)->Kill();
	}
	auto players = taskSystem->GetTasks<CharaBace>(std::pair<std::string, std::string>("�v���C��", "���L����"));
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