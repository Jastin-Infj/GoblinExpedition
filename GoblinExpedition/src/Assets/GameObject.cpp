#include "GameObject.h"

/*コンストラクタ*/
GameObject::GameObject()
{
	/*これらの機能は初回時はnullptrにする*/
	this->collider = nullptr;
	this->draw = nullptr;
	this->move = nullptr;
	this->shapemouse = nullptr;
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
	if (this->shapemouse)
	{
		delete this->shapemouse;
		this->shapemouse = nullptr;
	}
}
/*当たり判定矩形を返します*/
RectF GameObject::getRecthitbace()const
{
	return this->collider->gethitbaceRect();
}
/*当たり判定矩形を返します*/
Circle GameObject::getCirclehitbace()const
{
	return this->collider->gethitbaceCircle();
}
/*中身が空であるかを判定します*/
bool GameObject::isExpiredCollider()const
{
	return this->collider == nullptr ? true : false;
}
/*中身が空であるかを判定します*/
bool GameObject::isExpiredDraw()const
{
	return this->draw == nullptr ? true : false;
}
/*中身が空であるかを判定します*/
bool GameObject::isExpiredMove()const
{
	return this->move == nullptr ? true : false;
}
/*中身が空であるかを判定します*/
bool GameObject::isExpiredShapemouse()const
{
	return this->shapemouse == nullptr ? true : false;
}
/*座標を返します*/
Vec2 GameObject::getPosition()const
{
	return this->position;
}
/*大きさを返します*/
Point GameObject::getScale()const
{
	return this->scale;
}
/*座標*/




///*引数値のベクトル分座標移動を行います*/
//void GameObject::OffsetPosition(const Vec2& offset)
//{
//	this->position += offset;
//	std::cout << this->position << std::endl;
//}