#include <Siv3D.hpp>
#include "SceceTask.h"

/*追加したいタスクはここに入力*/
#include "../TaskSystem/Task_Example.h"

void TaskStartCreate()
{
	 std::pair<std::string, std::string> taskname = { "FF","FF5" };
	 auto obj = TaskObjectExample::Create(taskname);
}
void Init()
{
	
}