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
bool Title::Init(const std::pair<std::string, std::string>& taskname_)
{
	__super::setTaskName(taskname_);
	this->setDrawOrder(1.0f);

	//追加したいオブジェクトをここに記述する

	rm->setTexture("タイトルロゴ", Texture(L"./data/image/TextImage/Title.png"));
	auto titlerogo = UI::Create(TASKNAME("UIfont", "タイトルロゴ"), UI::ObjectType::TitleRogo, Vec2(Window::Center().x - 256 / 2, 0), Point(256, 96), UI::InitFormat::Normal, Rect(0, 0, 418, 64));

	rm->setTexture("タイトル用スタート", Texture(L"./data/image/TextImage/Start.png"));
	auto start = UI::Create(TASKNAME("UIfont", "タイトル用スタート"), UI::ObjectType::TitleStart, Vec2(Window::Center().x - 256 / 2, Window::Center().y - 96), Point(256, 96), UI::InitFormat::AddCollider, Rect(0, 0, 316, 110));

	rm->setTexture("タイトル用終了ボタン", Texture(L"./data/image/TextImage/Exit.png"));
	auto exit = UI::Create(TASKNAME("UI", "タイトル用終了ボタン"), UI::ObjectType::TitleExit, Vec2(Window::Center().x - 256 / 2, Window::Center().y + 96), Point(256, 96), UI::InitFormat::AddCollider, Rect(0, 0, 258, 110));

	this->shapemouse = ShapeMouseCursor::AddComponent<Point>(ShapeMouseCursor::ShapeT::Rect, Point(5, 5));
	this->shapemouse->MouseColliderAddComponent();
	return true;
}
/* 更新処理 */
void Title::Update()
{
	this->MouseHitleftClicked_update();
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
	auto uifonts = taskSystem->GetTasks_GroupName<UI>("UIfont");
	for (auto it = uifonts->begin(); it != uifonts->end(); ++it)
	{
		(*it)->Kill();
	}
	auto uis = taskSystem->GetTasks_GroupName<UI>("UI");
	for (auto it = uis->begin(); it != uis->end(); ++it)
	{
		(*it)->Kill();
	}
	if (this->shapemouse)
	{
		delete this->shapemouse;
		this->shapemouse = nullptr;
	}
	if (System::Update())
	{
		auto howplay = HowPlay::Create(TASKNAME("シーン", "遊び方"));
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
/*マウスと対象の図形との当たり判定を行います*/
void Title::MouseHitleftClicked_update()
{
	auto startui = taskSystem->GetTask_TaskName<UI>("タイトル用スタート");
	if (!startui)
	{
		return;
	}
	if (this->shapemouse->LeftClicked(startui->getRecthitbace()))
	{
		startui->Receive_Player();
	}
	auto exitui = taskSystem->GetTask_TaskName<UI>("タイトル用終了ボタン");
	if (!exitui)
	{
		return;
	}
	if (this->shapemouse->LeftClicked(exitui->getRecthitbace()))
	{
		exitui->Receive_Player();
	}
}
