#include "Task_Example.h"
#include <string>
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
	std::cout << this->getTaskname().second <<  "~TaskObjectExample()" << std::endl;
#endif
}
/*初期化処理*/
bool TaskObjectExample::Init(std::pair<std::string, std::string>& taskname_)
{
#if(_DEBUG)
	std::cout << this->getTaskname().second << "TaskObjectExample.Init()" << std::endl;
#endif
	/*名前を登録します*/
	__super::setTaskName(taskname_);
	/*描画順位を格納する*/
	__super::setDrawOrder();

	return true;
}
/*更新処理*/
void TaskObjectExample::UpDate()
{
#if(_DEBUG)
	std::cout << this->getTaskname().second  << "    "<< "TaskObjectExample.UpDate()" << std::endl;
#endif
}
/*描画処理*/
void TaskObjectExample::Render()
{
#if(_DEBUG)
	std::cout << this->getTaskname().second << "     "<< "TaskObjectExample.Render()" << std::endl;
#endif
}
/*オブジェクトを生成します*/
TaskObject::SP TaskObjectExample::Create(std::pair<std::string, std::string>& taskname_, bool flag)
{
	TaskObject::SP to = TaskObject::SP(new TaskObjectExample());
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
		return to;
	}
	return nullptr;
}
