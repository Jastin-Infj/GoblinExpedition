#pragma once
#include <Siv3D.hpp>
///<summary>
///移動に関する機能を使用できるクラス
///</summary>
class MoveInterFace
{
public:

	/// <summary>
	/// 引数なしコンストラクタ
	/// </summary>
	MoveInterFace() {}


	///<summary>
	///移動量設定つきコンストラクタ
	///</summary>
	///<param name = 'speed'>
	/// 移動スピード
	///</param>
	MoveInterFace(const Point& movespeed)
		:
		moveVec(movespeed)
	{}


	///<summary>
	///移動量設定つきコンストラクタ
	///</summary>
	///<param name = 'speed'>
	/// 移動スピード
	///</param>
	MoveInterFace(const Vec2& movespeed)
		:
		moveVec(movespeed)
	{}


	///<summary>
	///デストラクタ
	///<summary>
	~MoveInterFace() {}


	///<summary>
	///移動機能を追加します
	///</summary>
	///<param name = 'speed'>
	///移動スピード(X , Y)
	///</param>
	///<returns>
	///移動機能
	///</returns>
	static MoveInterFace* Addcomponent(const Vec2& movespeed)
	{
		return new MoveInterFace(movespeed);
	}


	///<summary>
	///移動機能を追加します
	///</summary>
	///<param name = 'speed'>
	///移動スピード(X , Y)
	///</param>
	///<returns>
	///移動機能
	///</returns>
	static MoveInterFace* Addcomponent(const Point& movespeed)
	{
		return new MoveInterFace(movespeed);
	}


	/// <summary>
	/// 移動量を変更します
	/// </summary>
	/// <param name="movespeed">
	/// 移動量(x , y)
	/// </param>
	void setMovespeed(const Point& movespeed)
	{
		this->moveVec = movespeed;
	}


	/// <summary>
	/// 移動量を変更します
	/// </summary>
	/// <param name="movespeed">
	/// 移動量(x , y)
	/// </param>
	void setMovespeed(const Vec2& movespeed)
	{
		this->moveVec = movespeed;
	}


	/// <summary>
	/// 移動量を返します
	/// </summary>
	/// <returns>
	/// 移動量
	/// </returns>
	Vec2 getMoveVec()const
	{
		return this->moveVec;
	}


	/// <summary>
	/// 等速直線運動で移動をします
	/// </summary>
	/// <param name="position">
	/// 移動対象
	/// </param>
	void UniformLinearMotion(Vec2& position)
	{
		position += this->moveVec;
	}


private:
	Vec2     moveVec;			//移動ベクトル
};
