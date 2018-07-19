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
	enum Type
	{
		UniformLinearMotion		//���������^��
	};


	///<summary>
	///<para>�R���X�g���N�^</para>
	///<para>���� : �ړ��X�s�[�h , �ړ��^�C�v </para>
	///</summary>
	///<param name = 'speed'>�ړ��X�s�[�h</param>
	///<param name = 'type'>�ړ��^�C�v</param>
	MoveInterFace(const Point& speed , const Type& type_)
		:moveVec(speed),
		type(type_) 
	{}


	///<summary>
	///�f�X�g���N�^
	///<summary>
	~MoveInterFace() {}


private:
	Point moveVec;		//�ړ��x�N�g��
	Type  type;			//�ړ��^�C�v
};
