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
	Collider(const ShapeHitType& shapehittype_, const Vec2& position_, const Point& scale_)
		:
		shapehittype(shapehittype_),
		hitbace(position_ , scale_)
	{}


	/// <summary>
	/// �R���C�_�[��ǉ����܂�
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
	/// <returns>
	/// ���������R���C�_�[�̃A�h���X
	/// </returns>
	static Collider* Addcomponent(const ShapeHitType& shapehittype_, const Vec2& position_, const Point& scale_)
	{
		return new Collider(shapehittype_, position_, scale_);
	}


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
	bool Hit(const Shape& shape)
	{
		return this->hitbace.intersects(shape);
	}


	/// <summary>
	/// �����蔻���`���J�[�\���̏�ɂ��邩�𔻒肵�܂�
	/// </summary>
	/// <returns>
	/// �ڐG���Ă��� true / �ڐG���Ă��Ȃ� false
	/// </returns>
	bool MouseOver()
	{
		return this->hitbace.mouseOver;
	}
	

	/// <summary>
	/// ���N���b�N��������邩�𔻒肵�܂�
	/// </summary>
	/// <returns>
	/// �N���b�N���� true / �N���b�N���Ă��Ȃ� false
	/// </returns>
	bool MouseLeftPressed()
	{
		return this->hitbace.leftPressed;
	}


	/// <summary>
	/// �����蔻���`��Ԃ��܂�
	/// </summary>
	/// <returns>
	/// �����蔻���`
	/// </returns>
	RectF getHitBace()const
	{
		return hitbace;
	}

	
	/// <summary>
	/// �����蔻���`��ݒ�E�ύX���܂�
	/// </summary>
	/// <param name="pos">
	/// �����蔻����W
	/// </param>
	/// <param name="scale">
	/// �����蔻��T�C�Y
	/// </param>
	void setHitBace(const Point& pos , const Point& scale)
	{
		this->hitbace = { pos,scale };
	}
	

	/// <summary>
	/// �����蔻���`��ݒ�E�ύX���܂�
	/// </summary>
	/// <param name="pos">
	/// �����蔻����W
	/// </param>
	/// <param name="scale">
	/// �����蔻��T�C�Y
	/// </param>
	void setHitBace(const Vec2& pos, const Point& scale)
	{
		this->hitbace = { pos,scale };
	}
private:
	ShapeHitType shapehittype;	//�����蔻��̌`
	RectF        hitbace;		//�����蔻���`
};