#pragma once
#include "GameObject.h"

//追加機能
#include "../InterFace/DrawInterFace.hpp"


class UI : public GameObject
{
public:
	typedef std::shared_ptr<UI> SP;		//スマートポインタ
	typedef std::weak_ptr<UI>	WP;		//ウィークポインタ


	/// <summary>
	/// オブジェクトタイプ
	/// </summary>
	enum class ObjectType
	{
		Background = 0,	//背景関係
		PlayerLife = 1,	//Playerのライフ
		ScoreUI    = 2, //スコアUI
		MusouItem  = 3, //無双アイテム
		ResultRogo = 4,	//リザルトロゴ
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UI();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~UI();


	/// <summary>
	/// パラメータの初期化をします
	/// </summary>
	/// <param name="taskname">
	/// オブジェクトタスク名(グループ名・タスク名)
	/// </param>
	/// <param name="objecttype">
	/// オブジェクトタイプ
	/// </param>
	/// <param name="position">
	/// 初期座標(X座標 , Y座標)
	/// </param>
	/// <param name="scale">
	/// 大きさ(X座標 , Y座標)
	/// </param>
	/// <param name="order">
	/// 描画優先順位(0.0f ～ 1.0f)
	/// </param>
	/// <returns>
	/// 初期化設定終了 true (falseなし)
	/// </returns>
	bool Init_Parameter(
		const TASKNAME&   taskname,
		const ObjectType& objecttype  , 
		const Vec2&       position, 
		const Point&      scale, 
		const float&      order
		);


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update()override;


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
	/// オブジェクトを生成します
	/// </summary>
	/// <param name="taskname">
	/// オブジェクトタスク名(グループ名・タスク名)
	/// </param>
	/// <param name="objecttype">
	/// オブジェクトタイプ
	/// </param>
	/// <param name="position">
	/// 初期座標(x座標 , y座標)
	/// </param>
	/// <param name="scale">
	/// 大きさ(横 , 縦)
	/// </param>
	/// <param name="order">
	/// 描画優先順位(0.0f ~ 1.0f)
	/// </param>
	/// <param name="flag">
	/// タスクシステムに登録　する  true / しない false
	/// </param>
	/// <returns>
	/// 生成したスマートポインタ
	/// </returns>
	static TaskObject::SP Create(
		const TASKNAME&   taskname, 
		const ObjectType& objecttype, 
		const Vec2&       position, 
		const Point&      scale, 
		const float&      order = 1.0f, 
		const bool        flag = true
		);


	/// <summary>
	/// 背景の設定を行います
	/// </summary>
	void BackGround_Parameter();


	/// <summary>
	/// PlayerのライフUIの設定を行います
	/// </summary>
	void Player_Life_Parameter();


	/// <summary>
	/// スコアUIの設定を行います
	/// </summary>
	void ScoreUI_Parameter();


	/// <summary>
	/// 無双アイテムの設定を行います
	/// </summary>
	void MusouItem_Parameter();


	/// <summary>
	/// 無双アイテムを使用します
	/// </summary>
	void MusouItem_Use();


	/// <summary>
	/// 敵を全滅させます
	/// </summary>
	void EnemiesKill();


	/// <summary>
	/// リザルトロゴの設定を行います
	/// </summary>
	void ResultRogo_Parameter();

//外部クラスで使用するメソッド
	

	/// <summary>
	/// ウィンドウ内にあるかを判定します
	/// </summary>
	/// <param name="position">
	/// 座標( x , y )
	/// </param>
	/// <param name="scale">
	/// 大きさ(縦 , 横)
	/// </param>
	/// <returns>
	/// ウィンドウ内 true / ウィンドウ外 false
	/// </returns>
	bool isInWindow(const Vec2& position, const Point& scale);


	/// <summary>
	/// ウィンドウ内にあるかを判定します
	/// </summary>
	/// <param name="drawbase">
	/// 描画矩形
	/// </param>
	/// <returns>
	/// ウィンドウ内 true / ウィンドウ外 false
	/// </returns>
	bool isInWindow(const RectF& drawbase);


	/// <summary>
	/// UIとの当たり判定を行います
	/// </summary>
	/// <param name="drawbase">
	/// 判定する矩形
	/// </param>
	/// <returns>
	/// 接触 true / 接触していない false
	/// </returns>
	bool Hit(const RectF& drawbase);


	/// <summary>
	/// マウスの判定した後の処理
	/// </summary>
	void Receive_Player();


	/// <summary>
	/// マウスが左クリックされたかを判定します
	/// </summary>
	/// <returns>
	/// 押された : true 押されていない false 
	/// </returns>
	bool MouseLclicked();


private:
	ObjectType objecttype;		//オブジェクトタイプ
	bool       killcheck;		//死んでいるか？
};


///// <summary>
///// 無双アイテムの当たり判定矩形を返します
///// </summary>
///// <returns>
///// 無双アイテム当たり判定矩形
///// </returns>
//RectF getDrawBase_MusuoItem()const;