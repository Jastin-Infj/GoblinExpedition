#include "Task_Game.h"
#include "../TaskSystem/TaskSystem.h"
#include "../ResourceManager/ResourceManager.h"

#include <iostream>

#include "../Assets/GameObject.h"
#include "../Assets/Enemy.h"
#include "../Assets/Player.h"
#include "../Assets/UI.h"
#include "../Assets/Score.h"

/* コンストラクタ */
Game::Game()
{
#if _DEBUG
	std::cout << "Game()" << std::endl;
#endif // _DEBUG
}
/* デストラクタ */
Game::~Game()
{
#if _DEBUG
	std::cout << "~Game()" << std::endl;
#endif // _DEBUG

}
/* 初期化処理 */
bool Game::Init(const std::pair<std::string,std::string>& taskname_)
{
	__super::setTaskName(taskname_);
	this->setDrawOrder(1.0f);


	this->enemycreatetime = 0.f;
	//追加したいオブジェクトをここに記述する
	
	/*ResourceManagerにリソースを追加する*/
	{
		//画像の指定
		rm->setTexture("インゲーム背景", Texture(L"./data/image/doukutu.png"));
		auto back = UI::Create(TASKNAME("背景", "インゲーム背景"),UI::ObjectType::Background ,Point(0, 0), Point(Window::Size().x, Window::Size().y), 0.1f);
	}
	{
		rm->setTexture("ゴブリン", Texture(L"./data/image/Goburin.png"));
		auto enemy = Enemy::Create(TASKNAME("モンスター", "ゴブリン") ,Enemy::ObjectType::Goburin ,Vec2(-48, Window::Size().y / 2), Point(64, 64), 0.8f);
	}
	{
		auto player = Player::Create(TASKNAME("プレイヤ", "自キャラ"),Vec2(Window::Size().x - 32 ,Window::Size().y / 2), Point{32,32} , 5 , 0.8f);
	}
	{
		rm->setTexture("スコアUI", Texture(L"./data/image/Score.png"));
		auto scoreui = UI::Create(TASKNAME("UI", "スコアUI"), UI::ObjectType::ScoreUI, Vec2(0, 0), Point(128, 64));
	}
	{
		rm->setTexture("スコア", Texture(L"./data/image/Math.png"));
		auto score1 = Score::Create(TASKNAME("UI", "スコア"), Vec2(130, 5), Point(32, 50), 1);
		auto score2 = Score::Create(TASKNAME("UI", "スコア"), Vec2(130 + 32 , 5), Point(32, 50), 2);
		auto score3 = Score::Create(TASKNAME("UI", "スコア"), Vec2(130 + 32 * 2, 5), Point(32, 50), 3);
		auto score4 = Score::Create(TASKNAME("UI", "スコア"), Vec2(130 + 32 * 3, 5), Point(32, 50), 4);
		auto score5 = Score::Create(TASKNAME("UI", "スコア"), Vec2(130 + 32 * 3, 5), Point(32, 50), 5);
	}
	return true;
}
/* 更新処理 */
void Game::UpDate()
{
	//this->Enemy_Create();
}
/*解放処理*/
bool Game::Finalize()
{
	/*ゲームタスクが終了したら同時にここで生成したオブジェクトを削除する*/
	auto backs = taskSystem->GetTasks<TaskObject>(std::pair<std::string, std::string>("背景", "インゲーム背景"));
	for (auto it = backs->begin(); it != backs->end(); ++it)
	{
		(*it)->Kill();
	}
	auto enemys = taskSystem->GetTasks<TaskObject>(std::pair<std::string, std::string>("モンスター", "ゴブリン"));
	for (auto it = enemys->begin(); it != enemys->end(); ++it)
	{
		(*it)->Kill();
	}
	auto players = taskSystem->GetTasks<TaskObject>(std::pair<std::string, std::string>("プレイヤ", "自キャラ"));
	for (auto it = players->begin(); it != players->end(); ++it)
	{
		(*it)->Kill();
	}
	return true;
}
/*敵をランダム生成します*/
void Game::Enemy_Create()
{
	double random = Random();
	this->enemycreatetime++;
	if (enemycreatetime >= ENEMY_CREATE_TIME)
	{
		auto enemy = Enemy::Create(std::pair<std::string, std::string>("モンスター", "ゴブリン"), Enemy::ObjectType::Goburin, Vec2(-48, 64 + ENEMY_RANDOM_Y * random), Point(64, 64), 0.8f);
		this->enemycreatetime = 0.f;
	}
}
/*スコアに引数の値を加算します*/
void Game::ScoreAddition(const int& addition)
{
	this->score += addition;
	if (this->score >= SCORE_MAX)
	{
		this->score = SCORE_MAX;
	}
}
/*現在のスコアを返します*/
int Game::getScore()const
{
	return this->score;
}
/*オブジェクトを生成します*/
TaskObject::SP Game::Create(const std::pair<std::string, std::string>& taskname, bool flag)
{
	Game::SP to = Game::SP(new Game());
	if (to)
	{
		/*自分のデータを渡す*/
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
