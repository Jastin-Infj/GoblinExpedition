#include <Siv3D.hpp>
#include "SceceTask.h"

/*�ǉ��������^�X�N�͂����ɓ���*/
#include "../InterFace/ObjectType.h"
#include "../Assets/CharaBace.h"
#include "../ResourceManager/ResourceManager.h"


void TaskStartCreate()
{
	/*ResourceManager�Ƀ��\�[�X��ǉ�����*/
	{
		//�摜�̎w��
		rm->setTexture("�C���Q�[���w�i", Texture(L"./data/image/doukutu.png"));
		std::pair<std::string, std::string> taskname = { "�w�i","�C���Q�[���w�i" };
		auto back = CharaBace::Create(taskname, Type::Back, Point(100,100), Point(680, 480), 1.0f);
	}
	{

	}
}
void Init()
{
	
}