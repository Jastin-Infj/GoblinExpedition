#include "Task_Game.h"
#include "../TaskSystem/TaskSystem.h"

#include "../InterFace/ObjectType.h"
#include "../Assets/CharaBace.h"
#include "../ResourceManager/ResourceManager.h"

#include <iostream>
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

	//追加したいオブジェクトをここに記述する
	
	/*ResourceManagerにリソースを追加する*/
	{
		//画像の指定
		rm->setTexture("インゲーム背景", Texture(L"./data/image/doukutu.png"));
		auto back = CharaBace::Create(std::pair<std::string, std::string>("背景", "インゲーム背景"), ObjectType::Back, Point(0,0), Point(680, 480), 0.1f);
	}
	{
		rm->setTexture("ゴブリン", Texture(L"./data/image/Goburin.png"));
		auto enemy = CharaBace::Create(std::pair<std::string, std::string>("モンスター", "ゴブリン"), ObjectType::Enemy, Point(0, 480 /2), Point(64, 64), 0.8f);
	}
	{
		auto mouseplayer = CharaBace::Create(std::pair<std::string, std::string>("マウス", "マウスPlayer"), ObjectType::Mouse, Point(Mouse::Pos()), Point{}, 0.8f);
	}
	return true;
}
/* 更新処理 */
void Game::UpDate()
{

}
/*解放処理*/
bool Game::Finalize()
{
	/*ゲームタスクが終了したら同時にここで生成したオブジェクトを削除する*/
	auto backs = taskSystem->GetTasks<CharaBace>(std::pair<std::string, std::string>("背景", "インゲーム背景"));
	for (auto it = backs->begin(); it != backs->end(); ++it)
	{
		(*it)->Kill();
	}
	auto enemys = taskSystem->GetTasks<CharaBace>(std::pair<std::string, std::string>("モンスター", "ゴブリン"));
	for (auto it = enemys->begin(); it != enemys->end(); ++it)
	{
		(*it)->Kill();
	}
	return true;
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