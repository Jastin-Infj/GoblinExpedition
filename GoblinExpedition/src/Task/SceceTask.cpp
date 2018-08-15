#include <Siv3D.hpp>
#include "SceceTask.h"

/*追加したいタスクはここに入力*/
#include "Task_Game.h"
#include "Task_Title.h"
#include "Task_Result.h"

using TASKNAME = std::pair<std::string, std::string>;

void TaskStartCreate()
{
	auto title = Title::Create(TASKNAME("シーン","タイトル"));
	//auto result = Result::Create(TASKNAME("シーン", "リザルト"), 0, 0);
}
void Init()
{
	
}