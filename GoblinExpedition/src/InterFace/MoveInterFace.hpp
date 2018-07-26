#pragma once
#include <Siv3D.hpp>
#include "../Assets/CharaBace.h"
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
	///<param name = 'movetype'>
	/// 移動タイプ
	///</param>
	MoveInterFace(const Point& movespeed)
		:
		moveVec(movespeed)
	{}


	///<summary>
	///デストラクタ
	///<summary>
	~MoveInterFace() {}


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
	/// 移動量を返します
	/// </summary>
	/// <returns>
	/// 移動量
	/// </returns>
	Point getMoveVec()const
	{
		return this->moveVec;
	}


	/// <summary>
	/// 等速直線運動で移動をします
	/// </summary>
	/// <param name="position">
	/// 移動対象
	/// </param>
	void UniformLinearMotion(Point& position)
	{
		position += this->moveVec;
	}
private:
	Point     moveVec;			//移動ベクトル
};
