#include <Siv3D.hpp>
#include "SceceTask.h"

/*�ǉ��������^�X�N�͂����ɓ���*/
#include "../TaskSystem/Task_Example.h"

void TaskStartCreate()
{
	 std::pair<std::string, std::string> taskname = { "FF","FF5" };
	 auto obj = TaskObjectExample::Create(taskname);
}
void Init()
{
	
}