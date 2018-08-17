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
	/// 雛形の描画フォーマットクラス
	/// </summary>
	enum class InitFormat
	{
		Normal,			//画像サイズのみの描画をする
		AddCollider,	//当たり判定つきの設定
	};


	/// <summary>
	/// オブジェクトタイプ
	/// </summary>
	enum class ObjectType
	{
		Background,		//背景関係
		PlayerLife,		//Playerのライフ
		ScoreUI   ,		//スコアUI
		MusouItem ,		//無双アイテム
		ResultRogo,		//リザルトロゴ
		TitleRogo ,		//タイトルロゴ
		ESCAPERogo,		//エスケープ
		HowPlayUI ,		//遊び方UI
		toTitle   ,		//タイトルへ戻る
		toGame    ,		//ゲームスタート
		TitleStart,		//タイトルのスタート
		TitleExit ,		//タイトルでの終了
		Leftclickfont,	//左クリックフォント
		Attackfont,		//攻撃フォント
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
	/// <param name="initformat">
	/// 初期化設定方法
	/// </param>
	/// <param name="src">
	/// 画像元矩形
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
		const InitFormat& initformat,
		const Rect&       src,
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
	/// <param name="initformat">
	/// 初期化設定方法
	/// </param>
	/// <param name="src">
	/// 画像元矩形
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
		const InitFormat& initformat,
		const Rect&       src,
		const float&      order = 1.0f, 
		const bool        flag = true
		);

private:

	/// <summary>
	/// 無双アイテムを使用します
	/// </summary>
	void MusouItem_Use();


	/// <summary>
	/// ゲームを終了させます
	/// </summary>
	void Escape_Use();


	/// <summary>
	/// 敵を全滅させます
	/// </summary>
	void EnemiesKill();


	/// <summary>
	/// マウスで左クリックが押された後の処理を行います
	/// </summary>
	void TitleStartUI_LeftClicked();

	
	/// <summary>
	/// マウスで左クリックが押された後の処理を行います
	/// </summary>
	void ToGameUI_LeftClicked();


	/// <summary>
	/// マウスで左クリックが押された後の処理を行います
	/// </summary>
	void TitleExitUI_LeftClicked();
	

	/// <summary>
	/// マウスで左クリックが押された後の処理を行います
	/// </summary>
	/// <param name="src_"></param>
	/// <returns></returns>
	void TotitleUI_LeftClicked();


	/// <summary>
	/// 初期設定で設定する雛形　画像サイズ分の描画をする
	/// </summary>
	/// <param name="src_">
	/// 画像元矩形
	/// </param>
	void Normal(const Rect& src_);


	/// <summary>
	/// 初期設定で設定する雛形　当たり判定の設定と画像サイズ分の当たり判定を描画をします
	/// </summary>
	/// <param name="src_">
	/// 画像元矩形
	/// </param>
	void AddCollider(const Rect& src_);

//外部クラスで使用するメソッド
	
public:
	/// <summary>
	/// ウィンドウ内にあるかを判定します
	/// </summary>
	/// <param name="position">
	/// 座標( x , y )
	/// </param>
	/// <returns>
	/// ウィンドウ内 true / ウィンドウ外 false
	/// </returns>
	bool isInWindow(const Vec2& position);


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


	/// <summary>
	/// 自身が持つオブジェクトタイプを返します
	/// </summary>
	/// <returns>
	/// オブジェクトタイプ
	/// </returns>
	ObjectType getObjecttype()const;


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