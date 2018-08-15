#include "Task_HowPlay.h"
#include "../Assets/UI.h"
#include "Task_Game.h"
using TASKNAME = std::pair<std::string, std::string>;


/* コンストラクタ */
HowPlay::HowPlay()
{
#if _DEBUG
	std::cout << "HowPlay()" << std::endl;
#endif // _DEBUG
}
/* デストラクタ */
HowPlay::~HowPlay()
{
	this->Finalize();
#if _DEBUG
	std::cout << "~HowPlay()" << std::endl;
#endif // _DEBUG

}
/* 初期化処理 */
bool HowPlay::Init(const std::pair<std::string, std::string>& taskname_)
{
	__super::setTaskName(taskname_);
	this->setDrawOrder(1.0f);

	//追加したいオブジェクトをここに記述する

	rm->setTexture("遊び方UI", Texture(L"./data/image/遊び方UI.png"));
	auto howplayui = UI::Create(TASKNAME("UI", "遊び方UI"), UI::ObjectType::HowPlayUI, Vec2(Window::Center().x - 256 / 2, 0), Point(256, 96));

	this->shapemouse = ShapeMouseCursor::AddComponent<Point>(ShapeMouseCursor::ShapeT::Rect,Point(5,5));
	return true;
}
/* 更新処理 */
void HowPlay::Update()
{
	//仮処理
	if (Input::KeyS.clicked)
	{
		this->Kill();
	}
}
/*描画処理*/
void HowPlay::Render()
{
	
}
/*解放処理*/
bool HowPlay::Finalize()
{
	auto uis = taskSystem->GetTasks_GroupName<UI>("UI");
	if (uis)
	{
		for (auto it = uis->begin(); it != uis->end(); ++it)
		{
			(*it)->Kill();
		}
	}
	if (this->shapemouse)
	{
		delete this->shapemouse;
		this->shapemouse = nullptr;
	}
	if (System::Update())
	{
		auto game = Game::Create(TASKNAME("シーン", "インゲーム"));
	}
	return true;
}
/*オブジェクトを生成します*/
TaskObject::SP HowPlay::Create(const std::pair<std::string, std::string>& taskname, bool flag)
{
	HowPlay::SP to = HowPlay::SP(new HowPlay());
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
/**/