#pragma once
#include <Siv3D.hpp>

/// <summary>
/// �����蔻��N���X
/// </summary>
class Collider
{
public:

	using ShapeT = Shape::Type;		//�}�`�̃^�C�v


	/// <summary>
	/// �R���X�g���N�^(��`)
	/// </summary>
	/// <param name="shapehittype_">
	/// �����蔻��̐}�`
	/// </param>
	/// <param name="rectf">
	/// �������������_���W����̋�`
	/// </param>
	Collider(const ShapeT& shapetype_,const RectF& rectf)
		:
		shapehittype(shapetype_),
		hitbaceRect(rectf)
	{}


	/// <summary>
	/// �R���X�g���N�^(��`)
	/// </summary>
	/// <param name="shapehittype_">
	/// �����蔻��̐}�`
	/// </param>
	/// <param name="circle">
	/// ���������~
	/// </param>
	explicit Collider(const ShapeT& shapetype_, const Rect& rect)
		:
		shapehittype(shapetype_),
		hitbaceRect(rect)
	{}


	/// <summary>
	/// �R���X�g���N�^(�~)
	/// </summary>
	/// <param name="shapehittype_">
	/// �����蔻��̐}�`
	/// </param>
	/// <param name="circle">
	/// ���������~
	/// </param>
	explicit Collider(const ShapeT& shapetype_,const Circle& circle)
		:
		shapehittype(shapetype_),
		hitbaceCircle(circle)
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
	static Collider* Addcomponent(const ShapeT& shapehittype_, const Vec2& position_, const Point& scale_)
	{
		switch (shapehittype_)
		{
		case ShapeT::Rect:
			return new Collider(shapehittype_, Rect((int)position_.x , (int)position_.y , scale_));
			break;
		case ShapeT::RectF:
			return new Collider(shapehittype_, RectF(position_, scale_));
			break;
		}
		return nullptr;
	}


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
	static Collider* Addcomponent(const ShapeT& shapehittype_, const Vec2& position_, const double& scale_)
	{
		switch (shapehittype_)
		{
		case ShapeT::Circle:
			return new Collider(shapehittype_, Circle(position_.x, position_.y, scale_));
			break;
		}
		return nullptr;
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
		return this->hitbaceRect.intersects(shape);
	}


	/// <summary>
	/// �����蔻���`���J�[�\���̏�ɂ��邩�𔻒肵�܂�
	/// </summary>
	/// <returns>
	/// �ڐG���Ă��� true / �ڐG���Ă��Ȃ� false
	/// </returns>
	bool MouseOver()
	{
		return this->hitbaceRect.mouseOver;
	}
	

	/// <summary>
	/// ���N���b�N��������Ă����Ԃł��邩�𔻒肵�܂�
	/// </summary>
	/// <returns>
	/// �N���b�N���� true / �N���b�N���Ă��Ȃ� false
	/// </returns>
	bool MouseLeftPressed()
	{
		return this->hitbaceRect.leftPressed;
	}


	/// <summary>
	/// ���N���b�N�������ꂽ��Ԃł��邩�𔻒肵�܂�
	/// </summary>
	/// <returns></returns>
	bool MouseLeftClicked()
	{
		return this->hitbaceRect.leftClicked;
	}


	/// <summary>
	/// �����蔻���`��Ԃ��܂�
	/// </summary>
	/// <returns>
	/// �����蔻���`
	/// </returns>
	RectF gethitbaceRect()const
	{
		return this->hitbaceRect;
	}


	/// <summary>
	/// �����蔻��̉~��Ԃ��܂�
	/// </summary>
	/// <returns>
	/// �����蔻��̉~
	/// </returns>
	Circle gethitbaceCircle()const
	{
		return this->hitbaceCircle;
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
	void sethitbace(const Vec2& pos, const Point& scale)
	{
		switch (this->shapehittype)
		{
		case ShapeT::Rect:
			this->hitbaceRect = { pos , scale };
			break;
		case ShapeT::RectF:
			this->hitbaceRect = { pos , scale };
			break;
		}
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
	void sethitbace(const Vec2& pos, const double& scale)
	{
		switch (this->shapehittype)
		{
		case ShapeT::Circle:
			this->hitbaceCircle = { pos , scale };
			break;
		}
	}
private:
	ShapeT		 shapehittype;		//�����蔻��̌`
	RectF        hitbaceRect;		//�����蔻���`
	Circle       hitbaceCircle;		//�����蔻��~
};