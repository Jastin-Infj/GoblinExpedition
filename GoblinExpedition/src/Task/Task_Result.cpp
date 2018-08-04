#include "Task_Result.h"
#include "../TaskSystem/TaskSystem.h"
#include "../ResourceManager/ResourceManager.h"
#include <iostream>

#include "../Assets/UI.h"
#include "../Assets/Score.h"

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
bool Result::Init(const std::pair<std::string, std::string>& taskname_ , const int& score_, const int& destroyingcount_)
{
	__super::setTaskName(taskname_);
	__super::setDrawOrder(1.0f);
	this->set_gameData(score_, destroyingcount_);
	{
		rm->setTexture("リザルトロゴ", Texture(L"./data/image/Result.png"));
		auto resultrogo = UI::Create(TASKNAME("UI", "リザルトロゴ"), UI::ObjectType::ResultRogo, Vec2(Window::Center().x - 128 /2 , 0), Point(128, 90));
	}
	{
		for (int i = 0; i < 5; ++i)
		{
			//スコア表示
			auto scores = Score::Create(TASKNAME("UI", "スコア"), Vec2(32 * i, Window::Size().y - 50), Point(32, 50), i + 1, this->score);
		}
	}
	{
		for (int i = 0; i < 3; ++i)
		{
			auto scores = Score::Create(TASKNAME("UI", "撃退数"), Vec2(Window::Size().x - 32 * (3 - i), Window::Size().y - 50), Point(32, 50),i + 1,this->destroyingcount);
		}
	}
	return true;
}
/*ゲームデータを送ります*/
void Result::set_gameData(const int& score_, const int& destroyingcount_)
{
	this->score = score_;
	this->destroyingcount = destroyingcount_;
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
TaskObject::SP Result::Create(const std::pair<std::string, std::string>& taskname , const int& score_ , const int& destroyingcount_,  bool flag)
{
	Result::SP result = Result::SP(new Result());
	if (result)
	{
		if (!result->Init(taskname,score_,destroyingcount_))
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