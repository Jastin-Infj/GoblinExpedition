#include "Task_Result.h"
#include "../TaskSystem/TaskSystem.h"
#include "../ResourceManager/ResourceManager.h"
#include <iostream>

#include "../Assets/UI.h"
#include "../Assets/Score.h"
#include "Task_Title.h"

/*�R���X�g���N�^*/
Result::Result()
{
#ifdef _DEBUG
	std::cout << "Result()" << std::endl;
#endif // _DEBUG

}
/*�f�X�g���N�^*/
Result::~Result()
{
	this->Finalize();
#ifdef _DEBUG
	std::cout << "~Result()" << std::endl;
#endif // _DEBUG

}
/*����������*/
bool Result::Init(const std::pair<std::string, std::string>& taskname_ , const int& score_, const int& destroyingcount_)
{
	__super::setTaskName(taskname_);
	__super::setDrawOrder(1.0f);
	this->set_gameData(score_, destroyingcount_);
	{
		rm->setTexture("���U���g���S", Texture(L"./data/image/Result.png"));
		auto resultrogo = UI::Create(TASKNAME("UI", "���U���g���S"), UI::ObjectType::ResultRogo, Vec2(Window::Center().x - 128 /2 , 0), Point(128, 90),UI::InitFormat::Normal,Rect(0,0,536,106));
	}
	{
		rm->setTexture("�^�C�g���֖߂�", Texture(L"./data/image/toTitle.png"));
		auto totitle = UI::Create(TASKNAME("UI","�^�C�g���֖߂�"),UI::ObjectType::toTitle,Vec2(Window::Size().x - 256, Window::Size().y - 64),Point(256,64),UI::InitFormat::AddCollider,Rect(0,0,626,103));
	}
	{
		for (int i = 0; i < 5; ++i)
		{
			//�X�R�A�\��
			auto scores = Score::Create(TASKNAME("UI", "�X�R�A"), Vec2(32 * i, Window::Size().y - 50), Point(32, 50), i + 1, this->score);
		}
	}
	{
		for (int i = 0; i < 3; ++i)
		{
			auto scores = Score::Create(TASKNAME("UI", "���ސ�"), Vec2(Window::Size().x - 32 * (3 - i), Window::Size().y - 50), Point(32, 50),i + 1,this->destroyingcount);
		}
	}
	this->shapemouse = ShapeMouseCursor::AddComponent<Point>(ShapeMouseCursor::ShapeT::RectF, Point(5, 5));
	this->shapemouse->MouseColliderAddComponent();
	return true;
}
/*�Q�[���f�[�^�𑗂�܂�*/
void Result::set_gameData(const int& score_, const int& destroyingcount_)
{
	this->score = score_;
	this->destroyingcount = destroyingcount_;
}
/*�X�V����*/
void Result::Update()
{
	this->MouseHitleftClicked_update();
	if (Input::KeyS.pressed)
	{
		this->Kill();
	}
}
/*�������*/
bool Result::Finalize()
{
	auto uis = taskSystem->GetTasks_GroupName<UI>("UI");
	for (auto it = uis->begin(); it != uis->end(); ++it)
	{
		(*it)->Kill();
	}
	auto scores = taskSystem->GetTasks_GroupName<Score>("�X�R�A");
	for (auto it = scores->begin(); it != scores->end(); ++it)
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
		auto title = Title::Create(TASKNAME("�V�[��", "�^�C�g��"));
	}
	return true;
}
/*���U���g��ʂ𐶐����܂�*/
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
/*�}�E�X�ƑΏۂ̐}�`�Ƃ̓����蔻����s���܂�*/
void Result::MouseHitleftClicked_update()
{
	auto totitle = taskSystem->GetTask_TaskName<UI>("�^�C�g���֖߂�");
	if (!totitle)
	{
		return;
	}
	if (this->shapemouse->LeftClicked(totitle->getRecthitbace()))
	{
		totitle->Receive_Player();
	}
}