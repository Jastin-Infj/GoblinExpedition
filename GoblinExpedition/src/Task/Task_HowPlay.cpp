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

	rm->setTexture("遊び方UI", Texture(L"./data/image/TextImage/遊び方UI.png"));
	auto howplayui = UI::Create(TASKNAME("UIfont", "遊び方UI"), UI::ObjectType::HowPlayUI, Vec2(Window::Center().x - 256 / 2, 0), Point(256, 96),UI::InitFormat::Normal,Rect(0,0,602,133));

	rm->setTexture("ゲームへ", Texture(L"./data/image/TextImage/ゲームスタート.png"));
	auto gamestart = UI::Create(TASKNAME("UIfont", "ゲームへ"), UI::ObjectType::toGame, Vec2(Window::Width() - 256, Window::Height() - 96), Point(256, 96), UI::InitFormat::AddCollider, Rect(0, 0, 624, 101));
	rm->setTexture("左クリックfont", Texture(L"./data/image/TextImage/LeftClick.png"));
	auto leftclick = UI::Create(TASKNAME("UIfont", "左クリックfont"), UI::ObjectType::Leftclickfont, Vec2(340, 220), Point(128, 64), UI::InitFormat::Normal, Rect(0, 0, 375, 105));
	rm->setTexture("攻撃font", Texture(L"./data/image/TextImage/attackfont.png"));
	auto attackfont = UI::Create(TASKNAME("UIfont", "攻撃font"), UI::ObjectType::Attackfont, Vec2(340 + 128 + 30, 220), Point(96, 64), UI::InitFormat::Normal, Rect(0, 0, 176, 106));

	this->textfile = TextInterFace::Create("./data/Text/howplay1.c",TextInterFace::FormatText::TXT,Font(20,Typeface::Heavy));
	this->textfile->setArrayString(this->textfile->ReadText(TextInterFace::ReaderType::TextLen));
	this->textfile->StringAssignment(this->textfile->getArrayString(), 0);

	this->shapemouse = ShapeMouseCursor::AddComponent<Point>(ShapeMouseCursor::ShapeT::Rect,Point(5,5));
	this->shapemouse->MouseColliderAddComponent();
	return true;
}
/* 更新処理 */
void HowPlay::Update()
{
	this->MouseHitleftClicked_update();
	//仮処理
	if (Input::KeyS.clicked)
	{
		this->Kill();
	}
}
/*描画処理*/
void HowPlay::Render()
{
	this->textfile->draw(Vec2(300, 400));
}
/*解放処理*/
bool HowPlay::Finalize()
{
	auto uis = taskSystem->GetTasks_GroupName<UI>("UIfont");
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
	if (this->textfile)
	{
		delete this->textfile;
		this->textfile = nullptr;
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
/*マウスと対象の図形との当たり判定を行います*/
void HowPlay::MouseHitleftClicked_update()
{
	auto toGame = taskSystem->GetTask_TaskName<UI>("ゲームへ");
	if (!toGame)
	{
		return;
	}
	if (this->shapemouse->LeftClicked(toGame->getRecthitbace()))
	{
		toGame->Receive_Player();
	}
}