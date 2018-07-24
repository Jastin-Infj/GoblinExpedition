#include "Task_Title.h"
#include "../TaskSystem/TaskSystem.h"

#include <iostream>
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

	

	return true;
}
/* �X�V���� */
void Title::UpDate()
{

}
/*�������*/
bool Title::Finalize()
{
	return true;
}
/*�I�u�W�F�N�g�𐶐����܂�*/
TaskObject::SP Title::Create(const std::pair<std::string, std::string>& taskname, bool flag)
{
	TaskObject::SP to = TaskObject::SP(new Title());
	if (to)
	{
		/*�����̃f�[�^��n��*/
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