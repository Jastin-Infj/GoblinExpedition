#pragma once

#include <Siv3D.hpp>

//追加機能
#include "../TaskSystem/TaskSystem.h"			//TaskSystemを使用出来るようにする
#include "../TaskSystem/TaskObject.h"			//TaskSystemに登録できるクラスを使用出来るようにします

#include "../InterFace/Collider.hpp"			//当たり判定
#include "../InterFace/DrawInterFace.hpp"		//描画機能
#include "../InterFace/MoveInterFace.hpp"		//移動機能
#include "../InterFace/ShapeMouseCursor.hpp"	//マウスカーソル図形機能

using TASKNAME = std::pair<std::string, std::string>;

/// <summary>
/// オブジェクトを生成するクラス
/// </summary>
class GameObject : public TaskObject
{
public:
	typedef std::shared_ptr<GameObject> SP;		//シェアポインタ
	typedef std::weak_ptr<GameObject> WP;		//ウィークポインタ


	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameObject();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameObject();


	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update()override {};


	/// <summary>
	/// 描画をします
	/// </summary>
	virtual void Render()override {};


	/// <summary>
	/// 解放処理
	/// </summary>
	/// <returns>
	/// 解放完了 true / 解放出来ない false
	/// </returns>
	virtual bool Finalize() { return true; }


	/// <summary>
	/// 当たり判定矩形を返します
	/// </summary>
	/// <returns></returns>
	RectF getRecthitbace()const;


	/// <summary>
	/// 当たり判定の円型を返します
	/// </summary>
	Circle getCirclehitbace()const;


	/// <summary>
	/// 中身が空であるかを判定します
	/// </summary>
	/// <returns>
	/// 空 true / 中身が存在する false
	/// </returns>
	bool isExpiredCollider()const;


	/// <summary>
	/// 中身が空であるかを判定します
	/// </summary>
	/// <returns>
	/// 空 true / 中身が存在する false
	/// </returns>
	bool isExpiredDraw()const;


	/// <summary>
	/// 中身が空であるかを判定します
	/// </summary>
	/// <returns>
	/// 空 true / 中身が存在する false
	/// </returns>
	bool isExpiredMove()const;


	/// <summary>
	/// 中身が空であるかを判定します
	/// </summary>
	/// <returns>
	/// 空 true / 中身が存在する false
	/// </returns>
	bool isExpiredShapemouse()const;


	/// <summary>
	/// 座標を返します
	/// </summary>
	/// <returns>
	/// 座標
	/// </returns>
	Vec2  getPosition()const;


	/// <summary>
	/// 大きさを返します
	/// </summary>
	/// <returns>
	/// 大きさ
	/// </returns>
	Point getScale()const;
protected:
	Vec2			  position;		//現在の座標
	Point			  scale;		//オブジェクトの大きさ
	float             order;		//描画優先順位
	Collider*         collider;		//当たり判定
	DrawInterFace*    draw;			//描画機能
	MoveInterFace*    move;			//移動機能
	ShapeMouseCursor* shapemouse;	//マウス図形
};




///// <summary>
///// 引数値のベクトル分座標移動を行います
///// </summary>
///// <param name="offset">
///// 移動させる座標値
///// </param>
//void OffsetPosition(const Vec2& offset);
