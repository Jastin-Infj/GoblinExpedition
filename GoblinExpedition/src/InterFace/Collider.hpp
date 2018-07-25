#pragma once
#include <Siv3D.hpp>

/// <summary>
/// 当たり判定クラス
/// </summary>
class Collider
{
public:
	/// <summary>
	/// 当たり判定図形タイプ
	/// </summary>
	enum class ShapeHitType
	{
		Cube,	//矩形
	};

	
	/// <summary>
	/// コンストラクタ
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
	Collider(const ShapeHitType& shapehittype_, const Point& position_, const Point& scale_)
		:
		shapehittype(shapehittype_),
		hitbace(position_ , scale_)
	{}


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
	bool Hit(Shape& shape)
	{
		return this->hitbace.intersects(shape);
	}
		

	/// <summary>
	/// 当たり判定矩形を返します
	/// </summary>
	/// <returns>
	/// 当たり判定矩形
	/// </returns>
	Rect getHitBace()const
	{
		return hitbace;
	}

	
private:
	ShapeHitType shapehittype;	//当たり判定の形
	Rect         hitbace;		//当たり判定矩形
};