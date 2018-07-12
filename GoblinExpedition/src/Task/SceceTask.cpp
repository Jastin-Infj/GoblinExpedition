#include <Siv3D.hpp>
#include "SceceTask.h"

/*’Ç‰Á‚µ‚½‚¢ƒ^ƒXƒN‚Í‚±‚±‚É“ü—Í*/
#include "../TaskSystem/Task_Example.h"

void TaskStartCreate()
{
	 std::pair<std::string, std::string> taskname = { "FF","FF5" };
	 auto obj = TaskObjectExample::Create(taskname);
}
void Init()
{
	
}