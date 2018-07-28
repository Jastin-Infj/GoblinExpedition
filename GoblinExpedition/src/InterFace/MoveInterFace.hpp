#pragma once
#include <Siv3D.hpp>
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
	MoveInterFace(const Point& movespeed)
		:
		moveVec(movespeed)
	{}


	///<summary>
	///�ړ��ʐݒ���R���X�g���N�^
	///</summary>
	///<param name = 'speed'>
	/// �ړ��X�s�[�h
	///</param>
	MoveInterFace(const Vec2& movespeed)
		:
		moveVec(movespeed)
	{}


	///<summary>
	///�f�X�g���N�^
	///<summary>
	~MoveInterFace() {}


	///<summary>
	///�ړ��@�\��ǉ����܂�
	///</summary>
	///<param name = 'speed'>
	///�ړ��X�s�[�h(X , Y)
	///</param>
	///<returns>
	///�ړ��@�\
	///</returns>
	static MoveInterFace* Addcomponent(const Vec2& movespeed)
	{
		return new MoveInterFace(movespeed);
	}


	///<summary>
	///�ړ��@�\��ǉ����܂�
	///</summary>
	///<param name = 'speed'>
	///�ړ��X�s�[�h(X , Y)
	///</param>
	///<returns>
	///�ړ��@�\
	///</returns>
	static MoveInterFace* Addcomponent(const Point& movespeed)
	{
		return new MoveInterFace(movespeed);
	}


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
	/// �ړ��ʂ�ύX���܂�
	/// </summary>
	/// <param name="movespeed">
	/// �ړ���(x , y)
	/// </param>
	void setMovespeed(const Vec2& movespeed)
	{
		this->moveVec = movespeed;
	}


	/// <summary>
	/// �ړ��ʂ�Ԃ��܂�
	/// </summary>
	/// <returns>
	/// �ړ���
	/// </returns>
	Vec2 getMoveVec()const
	{
		return this->moveVec;
	}


	/// <summary>
	/// ���������^���ňړ������܂�
	/// </summary>
	/// <param name="position">
	/// �ړ��Ώ�
	/// </param>
	void UniformLinearMotion(Vec2& position)
	{
		position += this->moveVec;
	}


private:
	Vec2     moveVec;			//�ړ��x�N�g��
};
