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
	MoveInterFace(const Point& movespeed , const MoveType& movetype_)
		:
		moveVec(movespeed),
		MoveType(movetype_) 
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
	/// �ړ����@�̃^�C�v��ύX���܂�
	/// </summary>
	/// <param name="movetype">
	/// �ړ����@
	/// </param>
	void setMoveType(const MoveType& movetype)
	{
		this->MoveType = movetype;
	}
private:
	Point     moveVec;			//�ړ��x�N�g��
	MoveType  MoveType;			//�ړ��^�C�v
};
