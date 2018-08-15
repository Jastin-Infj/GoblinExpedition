#pragma once
#include <Siv3D.hpp>

#include "DrawInterFace.hpp"		//�`��@�\
#include "Collider.hpp"				//�����蔻��


/// <summary>
/// �}�E�X�J�[�\���}�`�������N���X�ł�
/// </summary>
class ShapeMouseCursor
{
public:
	using ShapeT = Shape::Type;		//�}�`�̃^�C�v

	/// <summary>
	/// �R���X�g���N�^(��`�ݒ肠��)
	/// </summary>
	/// <param name="hitbaceScale_">
	/// �����蔻��̑傫��
	/// </param>
	ShapeMouseCursor(const Point& hitbaceScale_)
		:
		position({}),
		hitbaceRectSize(hitbaceScale_),
		shapetype(ShapeT::Point)
	{
		this->collider = nullptr;
		this->draw = nullptr;
	}


	/// <summary>
	/// �R���X�g���N�^(�~)
	/// </summary>
	/// <param name="hitbace_scale">
	/// �����蔻��̑傫��
	/// </param>
	explicit ShapeMouseCursor(const double& hitbaceScale_)
		:
		position({}),
		hitbaceCircleSize(hitbaceScale_),
		shapetype(ShapeT::Circle)
	{
		this->collider = nullptr;
		this->draw = nullptr;
	}


	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ShapeMouseCursor() 
	{
		if (this->collider)
		{
			delete this->collider;
			this->collider = nullptr;
		}
		if (this->draw)
		{
			delete this->draw;
			this->draw = nullptr;
		}
	}


	/// <summary>
	/// �}�E�X�̍��W���X�V���܂�
	/// </summary>
	void Posupdate()
	{
		this->position = Mouse::Pos();
	}


	/// <summary>
	/// �}�E�X�̓����蔻��𖈃t���[���X�V���܂�
	/// </summary>
	void MouseHitBaceupdate()const
	{
		if (!this->collider)
		{
			return;
		}

		switch (this->shapetype)
		{
		case ShapeT::Circle:
			this->collider->sethitbace(this->position, this->hitbaceCircleSize);
			break;
		case ShapeT::Rect:
		case ShapeT::RectF:
			this->collider->sethitbace(this->position, this->hitbaceRectSize);
			break;
		default:
			break;
		}
	}


	/// <summary>
	/// �}�`�̃^�C�v�������Ɠ����ł��邩�𔻒肵�܂�
	/// </summary>
	/// <param name="checktype">
	/// ��������}�`
	/// </param>
	/// <returns>
	/// ��v ���Ă��� true / ���Ă��Ȃ� false
	/// </returns>
	bool istypeMatched(const ShapeT& checktype)
	{
		return this->shapetype == checktype ? true : false;
	}


	/// <summary>
	/// �}�E�X�ɓ����蔻���ǉ����܂�
	/// </summary>
	void MouseColliderAddComponent()
	{
		if (this->collider)
		{
			return;
		}

		switch (this->shapetype)
		{
		case ShapeT::Rect:
		case ShapeT::RectF:
			this->collider = Collider::Addcomponent(this->shapetype, this->position, this->hitbaceRectSize);
			break;
		case ShapeT::Circle:
			this->collider = Collider::Addcomponent(this->shapetype, this->position, this->hitbaceCircleSize);
			break;
		}
	}


	/// <summary>
	/// �}�E�X�J�[�\�����}�`�̏�ɂ��邩�𒲂ׂ܂�
	/// </summary>
	/// <param name="shape">
	/// ���ׂ�}�`
	/// </param>
	/// <returns>
	/// ��� ���� true / �Ȃ� false
	/// </returns>
	template <class Shape>
	bool MouseOver(const Shape& shape)const
	{
		return shape.mouseOver;
	}


	/// <summary>
	/// �}�`�ɑ΂��č��N���b�N�������ꂽ���𔻒肵�܂�
	/// </summary>
	/// <param name="shape">
	/// ���ׂ�}�`
	/// </param>
	/// <returns>
	/// �����ꂽ true / ������Ă��Ȃ� false
	/// </returns>
	template<class Shape>
	bool LeftClicked(const Shape& shape)const
	{
		return shape.leftClicked;
	}


	/// <summary>
	/// �}�`�ɑ΂��č��N���b�N��������Ă��邩�𔻒肵�܂�
	/// </summary>
	/// <param name="shape">
	/// ���ׂ�}�`
	/// </param>
	/// <returns>
	/// ������Ă��� true / ���Ȃ� false
	/// </returns>
	template<class Shape>
	bool LeftPressed(const Shape& shape)const
	{
		return shape.leftPressed;
	}


	/// <summary>
	/// �}�`�ɑ΂��č��N���b�N�𗣂��Ă��邩�𔻒肵�܂�
	/// </summary>
	/// <param name="shape">
	/// ���ׂ�}�`
	/// </param>
	/// <returns>
	/// �����Ă��� true / �����Ă��Ȃ� false
	/// </returns>
	template<class Shape>
	bool LeftReleased(const Shape& shape)const
	{
		return shape.leftReleased;
	}


	/// <summary>
	/// �}�`�ɑ΂��ĉE�N���b�N�������ꂽ���𔻒肵�܂�
	/// </summary>
	/// <param name="shape">
	/// ���ׂ�}�`
	/// </param>
	/// <returns>
	/// �����ꂽ true / ������Ă��Ȃ� false
	/// </returns>
	template <class Shape>
	bool RightClicked(const Shape& shape)const
	{
		return shape.rightClicked;
	}


	/// <summary>
	/// �}�`�ɑ΂��ĉE�N���b�N��������Ă��邩�𔻒肵�܂�
	/// </summary>
	/// <param name="shape">
	/// ���ׂ�}�`
	/// </param>
	/// <returns>
	/// �E�N���b�N�������ꂽ true / false
	/// </returns>
	template<class Shape>
	bool RightPressed(const Shape& shape)const
	{
		return shape.rightPressed;
	}


	/// <summary>
	/// �}�`�ɑ΂��ĉE�N���b�N��������Ă��邩�𔻒肵�܂�
	/// </summary>
	/// <param name="shape">
	/// ���ׂ�}�`
	/// </param>
	/// <returns>
	/// �E�N���b�N��������Ă��� true / ���Ȃ� false
	/// </returns>
	template<class Shape>
	bool RightReleased(const Shape& shape)const
	{
		return shape.rightReleased;
	}
private:
	Vec2			position;			//���݂̃}�E�X���W
	Point			hitbaceRectSize;	//�����蔻��T�C�Y
	double			hitbaceCircleSize;	//�~�̔��a�̃T�C�Y
	ShapeT			shapetype;			//�}�`�̃^�C�v

	DrawInterFace*  draw;				//�`��@�\
	Collider*		collider;			//�����蔻��@�\
};