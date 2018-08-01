#include "GameObject.h"

/*コンストラクタ*/
GameObject::GameObject()
{
	/*これらの機能は初回時はnullptrにする*/
	this->collider = nullptr;
	this->draw = nullptr;
	this->move = nullptr;
}
/*デストラクタ*/
GameObject::~GameObject() 
{
	if (this->draw)
	{
		delete this->draw;
		this->draw = nullptr;
	}
	if (this->collider)
	{
		delete this->collider;
		this->collider = nullptr;
	}
	if (this->move)
	{
		delete this->move;
		this->move = nullptr;
	}
}
/*引数値のベクトル分座標移動を行います*/
void GameObject::OffsetPosition(const Vec2& offset)
{
	this->position += offset;
	std::cout << this->position << std::endl;
}