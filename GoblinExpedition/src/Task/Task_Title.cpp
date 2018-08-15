#include "Task_Title.h"
#include "../TaskSystem/TaskSystem.h"
#include "../ResourceManager/ResourceManager.h"
#include "Task_HowPlay.h"
#include "../Assets/UI.h"
#include <iostream>
using TASKNAME = std::pair<std::string, std::string>;


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
	this->Finalize();
#if _DEBUG
	std::cout << "~Title()" << std::endl;
#endif // _DEBUG

}
/* 初期化処理 */
bool Title::Init(const std::pair<std::string,std::string>& taskname_)
{
	__super::setTaskName(taskname_);
	this->setDrawOrder(1.0f);

	//追加したいオブジェクトをここに記述する

	rm->setTexture("タイトルロゴ",Texture(L"./data/image/Title.png"));
	auto titlerogo = UI::Create(TASKNAME("UI", "タイトルロゴ"), UI::ObjectType::TitleRogo, Vec2(Window::Center().x - 256 / 2, 0), Point(256, 96));

	return true;
}
/* 更新処理 */
void Title::Update()
{
	if (Input::KeyS.pressed)
	{
		this->Kill();
	}
}
/*描画処理*/
void Title::Render()
{
	
}
/*解放処理*/
bool Title::Finalize()
{
	auto uis = taskSystem->GetTasks_GroupName<UI>("UI");
	for (auto it = uis->begin(); it != uis->end(); ++it)
	{
		(*it)->Kill();
	}
	if (System::Update())
	{
		auto howplay = HowPlay::Create(TASKNAME("シーン","遊び方"));
	}
	return true;
}
/*オブジェクトを生成します*/
TaskObject::SP Title::Create(const std::pair<std::string, std::string>& taskname, bool flag)
{
	Title::SP to = Title::SP(new Title());
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