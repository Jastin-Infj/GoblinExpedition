#include "Task_Example.h"

/*�R���X�g���N�^*/
TaskObjectExample::TaskObjectExample()
{
#if(_DEBUG)
	std::cout << "TaskObjectExample()" << std::endl;
#endif
}
/*�f�X�g���N�^*/
TaskObjectExample::~TaskObjectExample()
{
#if(_DEBUG)
	std::cout << "~TaskObjectExample()" << std::endl;
#endif
}
/*����������*/
bool TaskObjectExample::Init(std::pair<std::string, std::string>& taskname_)
{
#if(_DEBUG)
	std::cout << "TaskObjectExample.Init()" << std::endl;
#endif
	/*���O��o�^���܂�*/
	__super::setTaskName(taskname_);
	return true;
}
/*�X�V����*/
void TaskObjectExample::UpDate()
{
#if(_DEBUG)
	std::cout << "TaskObjectExample.UpDate()" << std::endl;
#endif
}
/*�`�揈��*/
void TaskObjectExample::Render()
{
#if(_DEBUG)
	std::cout << "TaskObjectExample.Render()" << std::endl;
#endif
}
/*�I�u�W�F�N�g�𐶐����܂�*/
TaskObjectExample::SP TaskObjectExample::Create(std::pair<std::string, std::string>& taskname_, bool flag)
{
	TaskObjectExample::SP to = TaskObjectExample::SP(new TaskObjectExample());
	if (to != nullptr)
	{
		to->me = to;
		if (!to->Init(taskname_))
		{
			to->Kill();
		}
		if (flag)
		{
			taskSystem->Add(to);
		}
	}
	return nullptr;
}
