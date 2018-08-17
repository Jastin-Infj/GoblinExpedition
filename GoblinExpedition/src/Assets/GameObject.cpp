#include "GameObject.h"

/*�R���X�g���N�^*/
GameObject::GameObject()
{
	/*�����̋@�\�͏��񎞂�nullptr�ɂ���*/
	this->collider = nullptr;
	this->draw = nullptr;
	this->move = nullptr;
	this->shapemouse = nullptr;
}
/*�f�X�g���N�^*/
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
/*�����蔻���`��Ԃ��܂�*/
RectF GameObject::getRecthitbace()const
{
	return this->collider->gethitbaceRect();
}
/*�����蔻���`��Ԃ��܂�*/
Circle GameObject::getCirclehitbace()const
{
	return this->collider->gethitbaceCircle();
}
/*���g����ł��邩�𔻒肵�܂�*/
bool GameObject::isExpiredCollider()const
{
	return this->collider == nullptr ? true : false;
}
/*���g����ł��邩�𔻒肵�܂�*/
bool GameObject::isExpiredDraw()const
{
	return this->draw == nullptr ? true : false;
}
/*���g����ł��邩�𔻒肵�܂�*/
bool GameObject::isExpiredMove()const
{
	return this->move == nullptr ? true : false;
}
/*���g����ł��邩�𔻒肵�܂�*/
bool GameObject::isExpiredShapemouse()const
{
	return this->shapemouse == nullptr ? true : false;
}
/*���W��Ԃ��܂�*/
Vec2 GameObject::getPosition()const
{
	return this->position;
}
/*�傫����Ԃ��܂�*/
Point GameObject::getScale()const
{
	return this->scale;
}
/*���W*/




///*�����l�̃x�N�g�������W�ړ����s���܂�*/
//void GameObject::OffsetPosition(const Vec2& offset)
//{
//	this->position += offset;
//	std::cout << this->position << std::endl;
//}