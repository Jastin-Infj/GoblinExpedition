#pragma once
#include <Siv3D.hpp>

///<summary>
///�ړ��Ɋւ���@�\���g�p�ł���N���X
///</summary>
class MoveInterFace
{
public:

	///<summary>
	///�ړ��^�C�v
	///</summary>
	enum MoveType
	{
		UniformLinearMotion		//���������^��
	};


	///<summary>
	///�R���X�g���N�^
	///</summary>
	///<param name = 'speed'>
	/// �ړ��X�s�[�h
	///</param>
	///<param name = 'movetype'>
	/// �ړ��^�C�v
	///</param>
	MoveInterFace(const Point& speed , const MoveType& movetype_)
		:moveVec(speed),
		MoveType(movetype_) 
	{}


	///<summary>
	///�f�X�g���N�^
	///<summary>
	~MoveInterFace() {}


private:
	Point     moveVec;			//�ړ��x�N�g��
	MoveType  MoveType;			//�ړ��^�C�v
};
