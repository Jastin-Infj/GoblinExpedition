#pragma once
#include <Siv3D.hpp>

///<summary>
///移動に関する機能を使用できるクラス
///</summary>
class MoveInterFace
{
public:

	///<summary>
	///移動タイプ
	///</summary>
	enum MoveType
	{
		UniformLinearMotion		//等速直線運動
	};

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
	MoveInterFace(const Point& movespeed , const MoveType& movetype_)
		:
		moveVec(movespeed),
		MoveType(movetype_) 
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
	/// 移動方法のタイプを変更します
	/// </summary>
	/// <param name="movetype">
	/// 移動方法
	/// </param>
	void setMoveType(const MoveType& movetype)
	{
		this->MoveType = movetype;
	}
private:
	Point     moveVec;			//移動ベクトル
	MoveType  MoveType;			//移動タイプ
};
