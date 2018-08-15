#pragma once
#include <Siv3D.hpp>

#include "DrawInterFace.hpp"		//描画機能
#include "Collider.hpp"				//当たり判定


/// <summary>
/// マウスカーソル図形を扱うクラスです
/// </summary>
class ShapeMouseCursor
{
public:
	using ShapeT = Shape::Type;		//図形のタイプ

	/// <summary>
	/// コンストラクタ(矩形設定あり)
	/// </summary>
	/// <param name="hitbaceScale_">
	/// 当たり判定の大きさ
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
	/// コンストラクタ(円)
	/// </summary>
	/// <param name="hitbace_scale">
	/// 当たり判定の大きさ
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
	/// デストラクタ
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
	/// マウスの座標を更新します
	/// </summary>
	void Posupdate()
	{
		this->position = Mouse::Pos();
	}


	/// <summary>
	/// マウスの当たり判定を毎フレーム更新します
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
	/// 図形のタイプが引数と同じであるかを判定します
	/// </summary>
	/// <param name="checktype">
	/// 検索する図形
	/// </param>
	/// <returns>
	/// 一致 している true / していない false
	/// </returns>
	bool istypeMatched(const ShapeT& checktype)
	{
		return this->shapetype == checktype ? true : false;
	}


	/// <summary>
	/// マウスに当たり判定を追加します
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
	/// マウスカーソルが図形の上にあるかを調べます
	/// </summary>
	/// <param name="shape">
	/// 調べる図形
	/// </param>
	/// <returns>
	/// 上に ある true / ない false
	/// </returns>
	template <class Shape>
	bool MouseOver(const Shape& shape)const
	{
		return shape.mouseOver;
	}


	/// <summary>
	/// 図形に対して左クリックを押されたかを判定します
	/// </summary>
	/// <param name="shape">
	/// 調べる図形
	/// </param>
	/// <returns>
	/// 押された true / 押されていない false
	/// </returns>
	template<class Shape>
	bool LeftClicked(const Shape& shape)const
	{
		return shape.leftClicked;
	}


	/// <summary>
	/// 図形に対して左クリックを押されているかを判定します
	/// </summary>
	/// <param name="shape">
	/// 調べる図形
	/// </param>
	/// <returns>
	/// 押されている true / いない false
	/// </returns>
	template<class Shape>
	bool LeftPressed(const Shape& shape)const
	{
		return shape.leftPressed;
	}


	/// <summary>
	/// 図形に対して左クリックを離しているかを判定します
	/// </summary>
	/// <param name="shape">
	/// 調べる図形
	/// </param>
	/// <returns>
	/// 離している true / 離していない false
	/// </returns>
	template<class Shape>
	bool LeftReleased(const Shape& shape)const
	{
		return shape.leftReleased;
	}


	/// <summary>
	/// 図形に対して右クリックが押されたかを判定します
	/// </summary>
	/// <param name="shape">
	/// 調べる図形
	/// </param>
	/// <returns>
	/// 押された true / 押されていない false
	/// </returns>
	template <class Shape>
	bool RightClicked(const Shape& shape)const
	{
		return shape.rightClicked;
	}


	/// <summary>
	/// 図形に対して右クリックが押されているかを判定します
	/// </summary>
	/// <param name="shape">
	/// 調べる図形
	/// </param>
	/// <returns>
	/// 右クリックが押された true / false
	/// </returns>
	template<class Shape>
	bool RightPressed(const Shape& shape)const
	{
		return shape.rightPressed;
	}


	/// <summary>
	/// 図形に対して右クリックが離されているかを判定します
	/// </summary>
	/// <param name="shape">
	/// 調べる図形
	/// </param>
	/// <returns>
	/// 右クリックが離されている true / いない false
	/// </returns>
	template<class Shape>
	bool RightReleased(const Shape& shape)const
	{
		return shape.rightReleased;
	}
private:
	Vec2			position;			//現在のマウス座標
	Point			hitbaceRectSize;	//当たり判定サイズ
	double			hitbaceCircleSize;	//円の半径のサイズ
	ShapeT			shapetype;			//図形のタイプ

	DrawInterFace*  draw;				//描画機能
	Collider*		collider;			//当たり判定機能
};