#include <Siv3D.hpp>
#include "SceceTask.h"

/*�ǉ��������^�X�N�͂����ɓ���*/
#include "Task_Game.h"
#include "Task_Title.h"
#include "Task_Result.h"

using TASKNAME = std::pair<std::string, std::string>;

void TaskStartCreate()
{
	auto title = Title::Create(TASKNAME("�V�[��","�^�C�g��"));
	//auto result = Result::Create(TASKNAME("�V�[��", "���U���g"), 0, 0);
}
void Init()
{
	
}