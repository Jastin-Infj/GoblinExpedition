#include "Task_Title.h"
#include "../TaskSystem/TaskSystem.h"
#include <iostream>
/* コンストラクタ */
Title::Title()
{
#if _DEBUG
	std::cout << "Title()" << std::endl;
#endif // _DEBUG
}
/* デストラクタ */
Title::~Title()
{
#if _DEBUG
	std::cout << "~Title()" << std::endl;
#endif // _DEBUG

}
/* 初期化処理 */
bool Title::Init(std::pair<std::string,std::string>& taskname_)
{
	__super::setTaskName(taskname_);
	this->setDrawOrder(0.9f);

	//追加したいオブジェクトをここに記述する


	return true;
}
/* 更新処理 */
void Title::UpDate()
{

}
/*解放処理*/
bool Title::Finalize()
{
	return true;
}
/*オブジェクトを生成します*/
TaskObject::SP Title::Create(std::pair<std::string, std::string>& taskname, bool flag)
{
	TaskObject::SP to = TaskObject::SP(new Title());
	if (to)
	{
		/*自分のデータを渡す*/
		to->me = to;
		if (!to->Init(taskname))
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