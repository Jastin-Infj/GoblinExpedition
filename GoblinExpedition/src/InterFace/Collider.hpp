#pragma once
#include <Siv3D.hpp>

/// <summary>
/// 当たり判定クラス
/// </summary>
class Collider
{
public:

	using ShapeT = Shape::Type;		//図形のタイプ


	/// <summary>
	/// コンストラクタ(矩形)
	/// </summary>
	/// <param name="shapehittype_">
	/// 当たり判定の図形
	/// </param>
	/// <param name="rectf">
	/// 生成した小数点座標ありの矩形
	/// </param>
	Collider(const ShapeT& shapetype_,const RectF& rectf)
		:
		shapehittype(shapetype_),
		hitbaceRect(rectf)
	{}


	/// <summary>
	/// コンストラクタ(矩形)
	/// </summary>
	/// <param name="shapehittype_">
	/// 当たり判定の図形
	/// </param>
	/// <param name="circle">
	/// 生成した円
	/// </param>
	explicit Collider(const ShapeT& shapetype_, const Rect& rect)
		:
		shapehittype(shapetype_),
		hitbaceRect(rect)
	{}


	/// <summary>
	/// コンストラクタ(円)
	/// </summary>
	/// <param name="shapehittype_">
	/// 当たり判定の図形
	/// </param>
	/// <param name="circle">
	/// 生成した円
	/// </param>
	explicit Collider(const ShapeT& shapetype_,const Circle& circle)
		:
		shapehittype(shapetype_),
		hitbaceCircle(circle)
	{}


	/// <summary>
	/// コライダーを追加します
	/// </summary>
	/// <param name="shapehittype_">
	/// 当たり判定の図形
	/// </param>
	/// <param name="position_">
	/// 当たり判定座標
	/// </param>
	/// <param name="scale_">
	/// 当たり判定サイズ
	/// </param>
	/// <returns>
	/// 生成したコライダーのアドレス
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
	/// コライダーを追加します
	/// </summary>
	/// <param name="shapehittype_">
	/// 当たり判定の図形
	/// </param>
	/// <param name="position_">
	/// 当たり判定座標
	/// </param>
	/// <param name="scale_">
	/// 当たり判定サイズ
	/// </param>
	/// <returns>
	/// 生成したコライダーのアドレス
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
	/// 他のオブジェクトとの当たり判定を行います
	/// </summary>
	/// <param name="target">
	/// 当たり判定するターゲット
	/// </param>
	/// <returns>
	/// 接触 true / 接触していない false
	/// </returns>
	template <class Shape>
	bool Hit(const Shape& shape)
	{
		return this->hitbaceRect.intersects(shape);
	}


	/// <summary>
	/// 当たり判定矩形がカーソルの上にあるかを判定します
	/// </summary>
	/// <returns>
	/// 接触している true / 接触していない false
	/// </returns>
	bool MouseOver()
	{
		return this->hitbaceRect.mouseOver;
	}
	

	/// <summary>
	/// 左クリックを押されている状態であるかを判定します
	/// </summary>
	/// <returns>
	/// クリックした true / クリックしていない false
	/// </returns>
	bool MouseLeftPressed()
	{
		return this->hitbaceRect.leftPressed;
	}


	/// <summary>
	/// 左クリックが押された状態であるかを判定します
	/// </summary>
	/// <returns></returns>
	bool MouseLeftClicked()
	{
		return this->hitbaceRect.leftClicked;
	}


	/// <summary>
	/// 当たり判定矩形を返します
	/// </summary>
	/// <returns>
	/// 当たり判定矩形
	/// </returns>
	RectF gethitbaceRect()const
	{
		return this->hitbaceRect;
	}


	/// <summary>
	/// 当たり判定の円を返します
	/// </summary>
	/// <returns>
	/// 当たり判定の円
	/// </returns>
	Circle gethitbaceCircle()const
	{
		return this->hitbaceCircle;
	}


	/// <summary>
	/// 当たり判定矩形を設定・変更します
	/// </summary>
	/// <param name="pos">
	/// 当たり判定座標
	/// </param>
	/// <param name="scale">
	/// 当たり判定サイズ
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
	/// 当たり判定矩形を設定・変更します
	/// </summary>
	/// <param name="pos">
	/// 当たり判定座標
	/// </param>
	/// <param name="scale">
	/// 当たり判定サイズ
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
	ShapeT		 shapehittype;		//当たり判定の形
	RectF        hitbaceRect;		//当たり判定矩形
	Circle       hitbaceCircle;		//当たり判定円
};