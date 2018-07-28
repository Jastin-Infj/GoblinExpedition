#pragma once

#include <Siv3D.hpp>

//追加機能
#include "../TaskSystem/TaskSystem.h"			//TaskSystemを使用出来るようにする
#include "../TaskSystem/TaskObject.h"			//TaskSystemに登録できるクラスを使用出来るようにします

#include "../InterFace/Collider.hpp"			//当たり判定
#include "../InterFace/DrawInterFace.hpp"		//描画機能
#include "../InterFace/MoveInterFace.hpp"		//移動機能

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
	virtual void UpDate() {};


	/// <summary>
	/// 描画をします
	/// </summary>
	virtual void Render() {};


	/// <summary>
	/// 解放処理
	/// </summary>
	/// <returns>
	/// 解放完了 true / 解放出来ない false
	/// </returns>
	virtual bool Finalize() { return true; }


protected:
	Vec2  position;					//現在の座標
	Point scale;					//オブジェクトの大きさ
	float          order;			//描画優先順位
	Collider*      collider;		//当たり判定
	DrawInterFace* draw;			//描画機能
	MoveInterFace* move;			//移動機能
};


