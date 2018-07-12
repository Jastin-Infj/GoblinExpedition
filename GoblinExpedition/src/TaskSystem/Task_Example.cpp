#include "Task_Example.h"

/*コンストラクタ*/
TaskObjectExample::TaskObjectExample()
{
#if(_DEBUG)
	std::cout << "TaskObjectExample()" << std::endl;
#endif
}
/*デストラクタ*/
TaskObjectExample::~TaskObjectExample()
{
#if(_DEBUG)
	std::cout << "~TaskObjectExample()" << std::endl;
#endif
}
/*初期化処理*/
bool TaskObjectExample::Init(std::pair<std::string, std::string>& taskname_)
{
#if(_DEBUG)
	std::cout << "TaskObjectExample.Init()" << std::endl;
#endif
	/*名前を登録します*/
	__super::setTaskName(taskname_);
	return true;
}
/*更新処理*/
void TaskObjectExample::UpDate()
{
#if(_DEBUG)
	std::cout << "TaskObjectExample.UpDate()" << std::endl;
#endif
}
/*描画処理*/
void TaskObjectExample::Render()
{
#if(_DEBUG)
	std::cout << "TaskObjectExample.Render()" << std::endl;
#endif
}
/*オブジェクトを生成します*/
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
