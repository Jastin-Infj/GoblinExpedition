#include "Task_Title.h"
#include "../TaskSystem/TaskSystem.h"
#include "../ResourceManager/ResourceManager.h"
#include "Task_HowPlay.h"
#include "../Assets/UI.h"
#include <iostream>
using TASKNAME = std::pair<std::string, std::string>;


/* �R���X�g���N�^ */
Title::Title()
{
#if _DEBUG
	std::cout << "Title()" << std::endl;
#endif // _DEBUG
}
/* �f�X�g���N�^ */
Title::~Title()
{
	this->Finalize();
#if _DEBUG
	std::cout << "~Title()" << std::endl;
#endif // _DEBUG

}
/* ���������� */
bool Title::Init(const std::pair<std::string,std::string>& taskname_)
{
	__super::setTaskName(taskname_);
	this->setDrawOrder(1.0f);

	//�ǉ��������I�u�W�F�N�g�������ɋL�q����

	rm->setTexture("�^�C�g�����S",Texture(L"./data/image/Title.png"));
	auto titlerogo = UI::Create(TASKNAME("UI", "�^�C�g�����S"), UI::ObjectType::TitleRogo, Vec2(Window::Center().x - 256 / 2, 0), Point(256, 96));

	return true;
}
/* �X�V���� */
void Title::Update()
{
	if (Input::KeyS.pressed)
	{
		this->Kill();
	}
}
/*�`�揈��*/
void Title::Render()
{
	
}
/*�������*/
bool Title::Finalize()
{
	auto uis = taskSystem->GetTasks_GroupName<UI>("UI");
	for (auto it = uis->begin(); it != uis->end(); ++it)
	{
		(*it)->Kill();
	}
	if (System::Update())
	{
		auto howplay = HowPlay::Create(TASKNAME("�V�[��","�V�ѕ�"));
	}
	return true;
}
/*�I�u�W�F�N�g�𐶐����܂�*/
TaskObject::SP Title::Create(const std::pair<std::string, std::string>& taskname, bool flag)
{
	Title::SP to = Title::SP(new Title());
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