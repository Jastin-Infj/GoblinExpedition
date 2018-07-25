#pragma once
#include <Siv3D.hpp>

/// <summary>
/// �����蔻��N���X
/// </summary>
class Collider
{
public:
	/// <summary>
	/// �����蔻��}�`�^�C�v
	/// </summary>
	enum class ShapeHitType
	{
		Cube,	//��`
	};

	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="shapehittype_">
	/// �����蔻��̐}�`
	/// </param>
	/// <param name="position_">
	/// �����蔻����W
	/// </param>
	/// <param name="scale_">
	/// �����蔻��T�C�Y 
	/// </param>
	Collider(const ShapeHitType& shapehittype_, const Point& position_, const Point& scale_)
		:
		shapehittype(shapehittype_),
		hitbace(position_ , scale_)
	{}


	/// <summary>
	/// ���̃I�u�W�F�N�g�Ƃ̓����蔻����s���܂�
	/// </summary>
	/// <param name="target">
	/// �����蔻�肷��^�[�Q�b�g
	/// </param>
	/// <returns>
	/// �ڐG true / �ڐG���Ă��Ȃ� false
	/// </returns>
	template <class Shape>
	bool Hit(Shape& shape)
	{
		return this->hitbace.intersects(shape);
	}
		

	/// <summary>
	/// �����蔻���`��Ԃ��܂�
	/// </summary>
	/// <returns>
	/// �����蔻���`
	/// </returns>
	Rect getHitBace()const
	{
		return hitbace;
	}

	
private:
	ShapeHitType shapehittype;	//�����蔻��̌`
	Rect         hitbace;		//�����蔻���`
};