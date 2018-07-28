#include "GameObject.h"

/*�R���X�g���N�^*/
GameObject::GameObject()
{
	/*�����̋@�\�͏��񎞂�nullptr�ɂ���*/
	this->collider = nullptr;
	this->draw = nullptr;
	this->move = nullptr;
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
}