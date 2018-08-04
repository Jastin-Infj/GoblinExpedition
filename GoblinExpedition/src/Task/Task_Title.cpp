#include "Task_Title.h"
#include "../TaskSystem/TaskSystem.h"
#include "../Task/Task_Game.h"
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
bool Title::Init(const TASKNAME& taskname_)
{
	__super::setTaskName(taskname_);
	this->setDrawOrder(1.0f);

	//追加したいオブジェクトをここに記述する

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
	this->draw->PaletteColorDraw(RectF(0, 0, Window::Size()),Color(125,125,0));
}
/*解放処理*/
bool Title::Finalize()
{
	if (this->draw)
	{
		delete this->draw;
		this->draw = nullptr;
	}

	if (System::Update())
	{
		auto game = Game::Create(TASKNAME("シーン","インゲーム"));
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
		if (!to->CreatedObjectInit(taskname))
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