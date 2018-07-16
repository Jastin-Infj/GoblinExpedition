#include <Siv3D.hpp>
#include "SceceTask.h"

/*追加したいタスクはここに入力*/
#include "Task_Game.h"


void TaskStartCreate()
{
	auto game = Game::Create(std::pair<std::string, std::string>("シーン","インゲーム"));
}
void Init()
{
	
}