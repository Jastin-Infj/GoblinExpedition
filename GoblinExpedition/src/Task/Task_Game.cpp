#include "Task_Game.h"
#include "../TaskSystem/TaskSystem.h"
#include "../ResourceManager/ResourceManager.h"

#include <iostream>

#include "../Assets/GameObject.h"
#include "../Assets/Enemy.h"
#include "../Assets/Player.h"
#include "../Assets/UI.h"
#include "../Assets/Score.h"

#include "../Task/Task_Result.h"

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
	this->Finalize();
#if _DEBUG
	std::cout << "~Game()" << std::endl;
#endif // _DEBUG

}
/* ���������� */
bool Game::Init(const std::pair<std::string,std::string>& taskname_)
{
	__super::setTaskName(taskname_);
	this->setDrawOrder(1.0f);


	this->enemycreatetime = 0.0f;
	this->enemy_destroyingcount = ENEMY_DESTROYINGCOUNT_INIT;

	this->gamestate = GameState::Normal;
	
	/*ResourceManager�Ƀ��\�[�X��ǉ�����*/
	{
		//�摜�̎w��
		rm->setTexture("�C���Q�[���w�i", Texture(L"./data/image/doukutu.png"));
		auto back = UI::Create(TASKNAME("�w�i", "�C���Q�[���w�i"),UI::ObjectType::Background ,Point(0, 0), Point(Window::Size().x, Window::Size().y), 0.1f);
	}
	{
		rm->setTexture("�S�u����", Texture(L"./data/image/Goburin.png"));
		rm->setSound("�G����SE", Sound(L"./data/BGM/Hit.wav"));
		auto enemy = Enemy::Create(TASKNAME("�����X�^�[", "�S�u����") ,Enemy::ObjectType::Goburin ,Vec2(-48, Window::Size().y / 2), Point(64, 64), 0.8f);
	}
	{
		auto player = Player::Create(TASKNAME("�v���C��", "���L����"),Vec2(Window::Size().x - 32 ,Window::Size().y / 2), Point{32,32} , PLAYER_LIFE_INIT , 0.8f);
	}
	{
		rm->setTexture("�X�R�AUI", Texture(L"./data/image/Score.png"));
		auto scoreui = UI::Create(TASKNAME("UI", "�X�R�AUI"), UI::ObjectType::ScoreUI, Vec2(0, 0), Point(128, 64));
	}
	{
		rm->setTexture("�X�R�A", Texture(L"./data/image/Math.png"));
		auto score1 = Score::Create(TASKNAME("UI", "�X�R�A"), Vec2(130, 5), Point(32, 50),1);
		auto score2 = Score::Create(TASKNAME("UI", "�X�R�A"), Vec2(130 + 32 , 5), Point(32, 50),2);
		auto score3 = Score::Create(TASKNAME("UI", "�X�R�A"), Vec2(130 + 32 * 2, 5), Point(32, 50),3);
		auto score4 = Score::Create(TASKNAME("UI", "�X�R�A"), Vec2(130 + 32 * 3, 5), Point(32, 50),4);
		auto score5 = Score::Create(TASKNAME("UI", "�X�R�A"), Vec2(130 + 32 * 4, 5), Point(32, 50),5);
	}
	{
		rm->setTexture("�G�X�P�[�v���S", Texture(L"./data/image/escape.png"));
		auto escape = UI::Create(TASKNAME("UI", "�G�X�P�[�v���S"), UI::ObjectType::ESCAPERogo, Vec2(Window::Size().x - 128, Window::Size().y - 48), Point(128, 48));
	}
	rm->setTexture("���o�A�C�e��",Texture(L"./data/image/musou.png"));
	
	return true;
}
/* �X�V���� */
void Game::Update()
{
	this->Enemy_Create();
	Player::WP player = taskSystem->GetTask_TaskName<Player>("���L����");
	if (!player.expired())
	{
		Player::SP temp = player.lock();
		if (this->gamestate == GameState::LifeZero)
		{
			this->score = SCORE_MIN;
			this->enemy_destroyingcount = ENEMY_DESTROYINGCOUNT_MIN;
			//���U���g��ʏ����֍s���u��
			this->Kill();
		}
		else if(this->gamestate == GameState::ESCAPE)
		{
			this->Kill();
		}
	}
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
	auto scores = taskSystem->GetTasks_GroupName<TaskObject>("UI");
	for (auto it = scores->begin(); it != scores->end(); ++it)
	{
		(*it)->Kill();
	}
	//�A�v���P�[�V�������N����
	if (System::Update())
	{
		auto nexttask = Result::Create(TASKNAME("�V�[��", "���U���g"),this->score , this->enemy_destroyingcount);
	}
	return true;
}
/*�G�������_���������܂�*/
void Game::Enemy_Create()
{
	double random = Random();
	this->enemycreatetime++;
	if (enemycreatetime >= ENEMY_CREATE_TIME)
	{
		auto enemy = Enemy::Create(TASKNAME("�����X�^�[", "�S�u����"), Enemy::ObjectType::Goburin, Vec2(-48, 64 + ENEMY_RANDOM_Y * random), Point(64, 64), 0.8f);
		this->enemycreatetime = 0.f;
	}
}
/*�X�R�A�Ɉ����̒l�����Z���܂�*/
void Game::ScoreAddition(const int& addition)
{
	this->score += addition;
	if (this->score >= SCORE_MAX)
	{
		this->score = SCORE_MAX;
	}
}
/*���݂̃X�R�A��Ԃ��܂�*/
int Game::getScore()const
{
	return this->score;
}
/*���o�A�C�e���𐶐����܂�*/
void Game::MusouItem_Create()
{
	if (this->isMusouItemCreate())
	{
		auto musouitem_size = taskSystem->GetTasks_TaskName<UI>("���o�A�C�e��");
		if (musouitem_size)
		{
			//���o�A�C�e���̃T�C�Y���擾����
			int ms = (int)musouitem_size->size();
			auto musouitem = UI::Create(TASKNAME("�A�C�e��", "���o�A�C�e��"), UI::ObjectType::MusouItem, Vec2(ms * 64, Window::Size().y - 64), Point(64, 64));
		}
		else
		{
			auto musouitem = UI::Create(TASKNAME("�A�C�e��", "���o�A�C�e��"), UI::ObjectType::MusouItem, Vec2(0, Window::Size().y - 64), Point(64, 64));
		}
	}
}
/*���o�A�C�e���������o���邩�𔻒肵�܂�*/
bool Game::isMusouItemCreate()const
{
	return this->enemy_destroyingcount % ENEMY_DESTROYINGSCORE == 0 ? true : false;
}
/*�G�̌��j���J�E���g�𑝉������܂�*/
void Game::Enemy_DestroyingCount_Add(const int& destoyingcount)
{
	this->enemy_destroyingcount += destoyingcount;
	/*����l�ɗ������~������*/
	if (this->enemy_destroyingcount > ENEMY_DESTROYINGCOUNT_MAX)
	{
		this->enemy_destroyingcount = ENEMY_DESTROYINGCOUNT_MAX;
	}
}
/*�Q�[���󋵂�ύX�E�ݒ肵�܂�*/
void Game::ChengeGameState(const GameState gamestate_)
{
	this->gamestate = gamestate_;
}
/*�Q�[���󋵂�Ԃ��܂�*/
Game::GameState Game::getGameState()const
{
	return this->gamestate;
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
