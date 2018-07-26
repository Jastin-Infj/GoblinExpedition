#pragma once
#include <Siv3D.hpp>
#include "../Assets/CharaBace.h"
///<summary>
///�ړ��Ɋւ���@�\���g�p�ł���N���X
///</summary>
class MoveInterFace
{
public:

	/// <summary>
	/// �����Ȃ��R���X�g���N�^
	/// </summary>
	MoveInterFace() {}


	///<summary>
	///�ړ��ʐݒ���R���X�g���N�^
	///</summary>
	///<param name = 'speed'>
	/// �ړ��X�s�[�h
	///</param>
	///<param name = 'movetype'>
	/// �ړ��^�C�v
	///</param>
	MoveInterFace(const Point& movespeed)
		:
		moveVec(movespeed)
	{}


	///<summary>
	///�f�X�g���N�^
	///<summary>
	~MoveInterFace() {}


	/// <summary>
	/// �ړ��ʂ�ύX���܂�
	/// </summary>
	/// <param name="movespeed">
	/// �ړ���(x , y)
	/// </param>
	void setMovespeed(const Point& movespeed)
	{
		this->moveVec = movespeed;
	}


	/// <summary>
	/// �ړ��ʂ�Ԃ��܂�
	/// </summary>
	/// <returns>
	/// �ړ���
	/// </returns>
	Point getMoveVec()const
	{
		return this->moveVec;
	}


	/// <summary>
	/// ���������^���ňړ������܂�
	/// </summary>
	/// <param name="position">
	/// �ړ��Ώ�
	/// </param>
	void UniformLinearMotion(Point& position)
	{
		position += this->moveVec;
	}
private:
	Point     moveVec;			//�ړ��x�N�g��
};
