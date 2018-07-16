#include <Siv3D.hpp>
#include "SceceTask.h"

/*追加したいタスクはここに入力*/
#include "../InterFace/ObjectType.h"
#include "../Assets/CharaBace.h"
#include "../ResourceManager/ResourceManager.h"


void TaskStartCreate()
{
	/*ResourceManagerにリソースを追加する*/
	{
		//画像の指定
		rm->setTexture("インゲーム背景", Texture(L"./data/image/doukutu.png"));
		std::pair<std::string, std::string> taskname = { "背景","インゲーム背景" };
		auto back = CharaBace::Create(taskname, Type::Back, Point(100,100), Point(680, 480), 1.0f);
	}
	{

	}
}
void Init()
{
	
}