#pragma once
#include "GameObject.h"


#include "Player.h"

#define SCORE				100		//倒されてたときのスコア

#define MOVE_SPEED_X        3		//X移動量
#define MOVE_SPEED_Y        0       //Y移動量

#define OPAQUE_INIT         255		//不透明度　初期値
#define OPAQUE_MIN          0		//不透明度　最小値
#define OPAQUE_MAX			255		//不透明度  最大値
#define OPAQUE_DECREASERATE 0.88	//1フレームあたりの不透明度減少率

#define OBJECT_TYPESIZE     2       //敵のオブジェクトタイプ数

class Enemy : public GameObject
{
public:
	typedef std::shared_ptr<Enemy> SP;		//スマートポインタ
	typedef std::weak_ptr<Enemy>   WP;		//ウィークポインタ

	enum class ObjectType
	{
		Goburin = 0,		//ゴブリン
	};


	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();


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
		const ObjectType& objecttype,
		const Vec2&       position,
		const Point&      scale,
		const float&      order
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
	/// Player当たり矩形と接触判定を行います
	/// </summary>
	/// <param name="target">
	/// 当たり判定をする矩形
	/// </param>
	/// <returns>
	/// 接触 true / 接触なし false
	/// </returns>
	bool onHitbaceExit(const RectF& target)const;


	/// <summary>
	/// 左右反転フラグを返します
	/// </summary>
	/// <returns>
	/// 左右反転フラグを返す
	/// </returns>
	bool getleftrightinversionflag()const;


	/// <summary>
	/// 左右反転フラグを入れ替えます
	/// </summary>
	void changeleftrightinversionflag();


	/// <summary>
	/// 左右反転フラグを設定します
	/// </summary>
	/// <param name="flag">
	/// true 反転 / false 反転なし
	/// </param>
	void setleftrightinversionflag(bool flag);


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
	/// ゴブリンの機能拡張設定を行います
	/// </summary>
	void Goburin_Parameter();


	/// <summary>
	/// 反転するかしないかを判定します
	/// </summary>
	void LeftRightInversion();


	/// <summary>
	/// マップ外判定をします
	/// </summary>
	bool OutsideMap();


	/// <summary>
	/// 不透明を減少させます
	/// </summary>
	void Opaque_Decrement();


	/// <summary>
	/// 不透明度が0になっているかを判定をします
	/// </summary>
	/// <returns>
	/// 0 true / 0以外 false
	/// </returns>
	bool isOpaque_Zero()const;


	/// <summary>
	/// マウスと敵の当たり判定
	/// </summary>
	void Mouse_Hit();


/*外部クラスで使用メソッド*/
	
	/// <summary>
	/// 当たり判定矩形を返します
	/// </summary>
	/// <returns>
	/// 当たり判定矩形
	/// </returns>
	RectF getHitBace()const;


	/// <summary>
	/// スコアを返します
	/// </summary>
	/// <returns>
	/// スコア
	/// </returns>
    const int getScore();
private:
	ObjectType	objecttype;					//オブジェクトタイプ
	bool leftrightinversionflag;			//左右反転フラグ
	bool mouse_hitflag;						//接触判定
	uint32      opaque;						//不透明度
};