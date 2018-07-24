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


	///<summary>
	///コンストラクタ
	///</summary>
	///<param name = 'speed'>
	/// 移動スピード
	///</param>
	///<param name = 'movetype'>
	/// 移動タイプ
	///</param>
	MoveInterFace(const Point& speed , const MoveType& movetype_)
		:moveVec(speed),
		MoveType(movetype_) 
	{}


	///<summary>
	///デストラクタ
	///<summary>
	~MoveInterFace() {}


private:
	Point     moveVec;			//移動ベクトル
	MoveType  MoveType;			//移動タイプ
};
