#include "Task_HowPlay.h"
#include "../Assets/UI.h"
#include "Task_Game.h"
using TASKNAME = std::pair<std::string, std::string>;


/* �R���X�g���N�^ */
HowPlay::HowPlay()
{
#if _DEBUG
	std::cout << "HowPlay()" << std::endl;
#endif // _DEBUG
}
/* �f�X�g���N�^ */
HowPlay::~HowPlay()
{
	this->Finalize();
#if _DEBUG
	std::cout << "~HowPlay()" << std::endl;
#endif // _DEBUG

}
/* ���������� */
bool HowPlay::Init(const std::pair<std::string, std::string>& taskname_)
{
	__super::setTaskName(taskname_);
	this->setDrawOrder(1.0f);

	//�ǉ��������I�u�W�F�N�g�������ɋL�q����

	rm->setTexture("�V�ѕ�UI", Texture(L"./data/image/�V�ѕ�UI.png"));
	auto howplayui = UI::Create(TASKNAME("UI", "�V�ѕ�UI"), UI::ObjectType::HowPlayUI, Vec2(Window::Center().x - 256 / 2, 0), Point(256, 96),UI::InitFormat::Normal,Rect(0,0,602,133));

	rm->setTexture("�Q�[����", Texture(L"./data/image/�Q�[���X�^�[�g.png"));
	auto gamestart = UI::Create(TASKNAME("UI", "�Q�[����"), UI::ObjectType::toGame, Vec2(Window::Width() - 256, Window::Height() - 96), Point(256, 96), UI::InitFormat::AddCollider, Rect(0, 0, 624, 101));
	this->shapemouse = ShapeMouseCursor::AddComponent<Point>(ShapeMouseCursor::ShapeT::Rect,Point(5,5));
	this->shapemouse->MouseColliderAddComponent();
	return true;
}
/* �X�V���� */
void HowPlay::Update()
{
	this->MouseHitleftClicked_update();
	//������
	if (Input::KeyS.clicked)
	{
		this->Kill();
	}
}
/*�`�揈��*/
void HowPlay::Render()
{
	
}
/*�������*/
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
		auto game = Game::Create(TASKNAME("�V�[��", "�C���Q�[��"));
	}
	return true;
}
/*�I�u�W�F�N�g�𐶐����܂�*/
TaskObject::SP HowPlay::Create(const std::pair<std::string, std::string>& taskname, bool flag)
{
	HowPlay::SP to = HowPlay::SP(new HowPlay());
	if (to)
	{
		/*�����̃f�[�^��n��*/
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
/*�}�E�X�ƑΏۂ̐}�`�Ƃ̓����蔻����s���܂�*/
void HowPlay::MouseHitleftClicked_update()
{
	auto toGame = taskSystem->GetTask_TaskName<UI>("�Q�[����");
	if (!toGame)
	{
		return;
	}
	if (this->shapemouse->LeftClicked(toGame->getRecthitbace()))
	{
		toGame->Receive_Player();
	}
}