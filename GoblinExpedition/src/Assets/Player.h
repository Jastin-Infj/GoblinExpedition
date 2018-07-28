#pragma once
#include "GameObject.h"

//追加機能
#include "../InterFace/DrawInterFace.hpp"
#include "../InterFace/Collider.hpp"
#include "../InterFace/MoveInterFace.hpp"

#define PLAYER_LIFE_MIN 1
#define PLAYER_LIFE_MAX 10

class Player : public GameObject
{
public:
	typedef std::shared_ptr<Player> SP;		//スマートポインタ
	typedef std::weak_ptr<Player>   WP;		//ウィークポインタ


	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();


	/// <summary>
	/// パラメータの初期化をします
	/// </summary>
	/// <param name="taskname">
	/// オブジェクトタスク名(グループ名・タスク名)
	/// </param>
	/// <param name="position">
	/// 初期座標(X座標 , Y座標)
	/// </param>
	/// <param name="scale">
	/// 大きさ(X座標 , Y座標)
	/// </param>
	/// <param name="life">
	/// ライフ値
	/// </param>
	/// <param name="order">
	/// 描画優先順位(0.0f 〜 1.0f)
	/// </param>
	/// <returns>
	/// 初期化設定終了 true (falseなし)
	/// </returns>
	bool Init_Parameter(
		const TASKNAME& taskname, 
		const Vec2&     position, 
		const Point&    scale , 
		const int&      life,
		const float&    order
		);


	/// <summary>
	/// 更新処理
	/// </summary>
	void UpDate()override;


	/// <summary>
	/// 描画処理
	/// </summary>
	void Render()override;


	/// <summary>
	/// 解放処理
	/// </summary>
	/// <returns>
	/// 解放 true (falseなし)
	/// </returns>
	bool Finalize()override;


	/// <summary>
	/// 体力を返します
	/// </summary>
	/// <returns>
	/// 体力
	/// </returns>
	int getLife()const;


	/// <summary>
	/// 体力の数によってライフUIの数を生成します
	/// </summary>
	void LifeUICreate();


	/// <summary>
	/// 体力値を変更・設定します
	/// </summary>
	/// <param name="life">
	/// 体力値
	/// </param>
	void setLife(int life);


	/// <summary>
	/// 体力値が負の記号または0かを判定します
	/// </summary>
	constexpr bool isLifeZero()const;


	/// <summary>
	/// 体力の最小値を返します
	/// </summary>
	/// <returns>
	/// 最小ライフ値
	/// </returns>
	const int  LifeMin();


	/// <summary>
	/// オブジェクトを生成します
	/// </summary>
	/// <param name="taskname">
	/// オブジェクトタスク名(グループ名・タスク名)の設定します
	/// </param>
	/// <param name="position">
	/// 初期座標を設定・変更します(X座標 , Y座標)
	/// </param>
	/// <param name="scale">
	/// 大きさを設定・変更します(X座標 , Y座標)
	/// </param>
	/// <param name="life">
	/// ライフ値(1 - 10)
	/// </param>
	/// <param name="order">
	/// <para>描画優先順位(0.0f 〜 1.0f)</para>
	/// <para>※大きいほどレイヤーが前に行きます</para>
	/// </param>
	/// <param name="flag">
	/// タスクシステムに登録 (する true / しない false)
	/// </param>
	/// <returns>
	/// 生成したオブジェクトのシェアポインタ
	/// </returns>
	static TaskObject::SP Create(
		const TASKNAME& taskname, 
		const Vec2&     position, 
		const Point&    scale, 
		const int&		life,
		const float&    order= 1.0f, 
		bool            flag = true
		);


/*外部クラスでメソッド使用*/

	/// <summary>
	/// 当たり判定矩形を返します
	/// </summary>
	/// <returns>
	/// 当たり判定矩形
	/// </returns>
	RectF getHitBace()const;


private:
	int            life;			//体力 
};