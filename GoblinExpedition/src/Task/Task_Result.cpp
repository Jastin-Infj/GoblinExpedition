#include "Task_Result.h"
#include "../TaskSystem/TaskSystem.h"
#include "../ResourceManager/ResourceManager.h"
#include <iostream>

#include "../Assets/UI.h"
/*コンストラクタ*/
Result::Result()
{
#ifdef _DEBUG
	std::cout << "Result()" << std::endl;
#endif // _DEBUG

}
/*デストラクタ*/
Result::~Result()
{
	this->Finalize();
#ifdef _DEBUG
	std::cout << "~Result()" << std::endl;
#endif // _DEBUG

}
/*初期化処理*/
bool Result::Init(const std::pair<std::string, std::string>& taskname_)
{
	__super::setTaskName(taskname_);
	__super::setDrawOrder(1.0f);

	{
		rm->setTexture("リザルトロゴ", Texture(L"./data/image/Result.png"));
		auto resultrogo = UI::Create(TASKNAME("UI", "リザルトロゴ"), UI::ObjectType::ResultRogo, Vec2(Window::Center().x - 128 /2 , 0), Point(128, 90));
	}
	return true;
}
/*更新処理*/
void Result::Update()
{

}
/*解放処理*/
bool Result::Finalize()
{
	auto uis = taskSystem->GetTasks_GroupName<UI>("UI");
	for (auto it = uis->begin(); it != uis->end(); ++it)
	{
		(*it)->Kill();
	}
	return true;
}
/*リザルト画面を生成します*/
TaskObject::SP Result::Create(const std::pair<std::string, std::string>& taskname , bool flag)
{
	Result::SP result = Result::SP(new Result());
	if (result)
	{
		if (!result->Init(taskname))
		{
			result->Kill();
		}
		if (flag)
		{
			taskSystem->Add(result);
		}
		return result;
	}
	return nullptr;
}