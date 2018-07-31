#pragma once

#include "GameObject.h"

#define SCORE_INIT 0		//初期スコア値
#define SCORE_MIN  0		//スコア最低値
#define SCORE_MAX  99999	//スコア上限値


/// <summary>
/// スコアクラス
/// </summary>
class Score : public GameObject
{
public:
	typedef std::shared_ptr<Score> SP;		//シェアポインタ
	typedef std::weak_ptr<Score>   WP;		//ウィークポインタ

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Score();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~Score();


	/// <summary>
	/// スコアを初期化設定します
	/// </summary>
	/// <param name="taskname_">
	/// オブジェクト名(グループ名・タスク名)
	/// </param>
	/// <param name="position_">
	/// 初期座標値(X座標 , Y座標)
	/// </param>
	/// <param name="scale_">
	/// 大きさ(X , Y)
	/// </param>
	/// <param name="digit_">
	/// 数字の桁数
	/// </param>
	/// <param name="order_">
	/// 描画優先順位
	/// </param>
	/// <returns>
	/// 初期化設定終了 true
	/// </returns>
	bool Score_Parameter(
		const TASKNAME&   taskname_,
		const Vec2&       position_,
		const Point&      scale_,
		const int&        digit_,
		const float&      order_
		);


	/// <summary>
	/// スコアを生成します
	/// </summary>
	/// <param name="taskname_">
	/// オブジェクト名(グループ名・タスク名)
	/// </param>
	/// <param name="position_">
	/// 初期座標値(X座標 , Y座標)
	/// </param>
	/// <param name="scale_">
	/// 大きさ(X , Y)
	/// </param>
	/// <param name="digit_">
	/// 割り当てる桁数
	/// </param>
	/// <param name="order_">
	/// 描画優先順位
	/// </param>
	/// <param name="flag">
	/// タスクシステムに登録をするか true / false
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	TaskObject::SP Create(
		const TASKNAME&   taskname_, 
		const Vec2&       position_, 
		const Point&      scale_, 
		const int&        digit_,
		const float&      order_ = 1.0f, 
		bool              flag = true
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
	/// 解放 true 
	/// </returns>
	bool Finalize()override;


	/// <summary>
	/// スコア計算をします
	/// </summary>
	void Score_UpDate();


	/// <summary>
	/// 現在のスコアを返します
	/// </summary>
	/// <returns>
	/// 現在のスコア
	/// </returns>
	int getScore()const;


	/// <summary>
	/// 指定の桁数の数字を返します
	/// </summary>
	/// <param name="digit_">
	/// 調べる桁数
	/// </param>
	/// <returns>
	/// 対応した桁数の数字
	/// </returns>
	std::string Digit();


	/// <summary>
	/// 各数字の画像元矩形を設定します
	/// </summary>
	/// <param name="value">
	/// 指定された桁数の数値
	/// </param>
	void setvalueSrc(const std::string& value);
private:
	int score;			//スコア
	int selectdigit;	//対応させる桁数
};