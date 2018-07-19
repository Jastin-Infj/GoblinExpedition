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
	enum Type
	{
		UniformLinearMotion		//等速直線運動
	};


	///<summary>
	///<para>コンストラクタ</para>
	///<para>引数 : 移動スピード , 移動タイプ </para>
	///</summary>
	///<param name = 'speed'>移動スピード</param>
	///<param name = 'type'>移動タイプ</param>
	MoveInterFace(const Point& speed , const Type& type_)
		:moveVec(speed),
		type(type_) 
	{}


	///<summary>
	///デストラクタ
	///<summary>
	~MoveInterFace() {}


private:
	Point moveVec;		//移動ベクトル
	Type  type;			//移動タイプ
};
