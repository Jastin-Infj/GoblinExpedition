#include <Siv3D.hpp>
#include "SceceTask.h"

/*’Ç‰Á‚µ‚½‚¢ƒ^ƒXƒN‚Í‚±‚±‚É“ü—Í*/
#include "../InterFace/ObjectType.h"
#include "../Assets/CharaBace.h"
#include "../ResourceManager/ResourceManager.h"


void TaskStartCreate()
{
	/*ResourceManager‚ÉƒŠƒ\[ƒX‚ğ’Ç‰Á‚·‚é*/
	{
		//‰æ‘œ‚Ìw’è
		rm->setTexture("ƒCƒ“ƒQ[ƒ€”wŒi", Texture(L"./data/image/doukutu.png"));
		std::pair<std::string, std::string> taskname = { "”wŒi","ƒCƒ“ƒQ[ƒ€”wŒi" };
		auto back = CharaBace::Create(taskname, Type::Back, Point(100,100), Point(680, 480), 1.0f);
	}
	{

	}
}
void Init()
{
	
}