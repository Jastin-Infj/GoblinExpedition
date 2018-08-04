#include <Siv3D.hpp>
#include "SceceTask.h"

/*追加したいタスクはここに入力*/
#include "Task_Game.h"
#include "Task_Title.h"

using TASKNAME = std::pair<std::string, std::string>;

void TaskStartCreate()
{
	auto title = Title::Create(TASKNAME("シーン","タイトル"));
}
void Init()
{
	
}