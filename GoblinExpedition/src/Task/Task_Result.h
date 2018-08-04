#pragma once
#include "../TaskSystem/TaskObject.h"

class Result : public TaskObject
{
public:
	typedef std::shared_ptr<Result> SP;		//スマートポインタ
	typedef std::weak_ptr<Result>   WP;		//ウィークポインタ


	/// <summary>
	/// コンストラクタ
	/// </summary>
	Result();


	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Result();


	/// <summary>
	/// リザルト初期化
	/// </summary>
	/// <param name="taskname_">
	/// タスク名(グループ名・タスク名)
	/// </param>
	/// <param name="score_">
	/// スコア
	/// </param>
	/// <param name="destroyingcount_">
	/// 敵の撃破数
	/// </param>
	/// <returns>
	/// 初期化終了 true 
	/// </returns>
	bool Init(const std::pair<std::string, std::string>& taskname_ , const int& score_ , const int& destroyingcount_);


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update()override;


	/// <summary>
	/// 描画処理
	/// </summary>
	void Render()override {};


	/// <summary>
	/// 解放処理
	/// </summary>
	/// <returns>
	/// 解放する true 
	/// </returns>
	bool Finalize()override;


	/// <summary>
	/// リザルト画面を生成します
	/// </summary>
	/// <param name="taskname">
	/// タスク名(グループ名・タスク名)
	/// </param>
	/// <param name="score_">
	/// スコア
	/// </param>
	/// <param name="destroyingcount_">
	/// 敵の撃破数
	/// </param>
	/// <param name="flag">
	/// タスクシステムに登録をするか する true /  しない false
	/// </param>
	/// <returns>
	/// 生成出来た true / 生成出来ない false
	/// </returns>
	static TaskObject::SP Create(const std::pair<std::string, std::string>& taskname,const int& score_ , const int& destroyingcount_, bool flag = true);


	/// <summary>
	/// ゲームデータを送ります
	/// </summary>
	/// <param name="score_">
	/// スコア
	/// </param>
	/// <param name="destroyingcount_">
	/// 敵の撃破数
	/// </param>
	void set_gameData(const int& score_ , const int& destroyingcount_);
private:
	int score;					//スコア
	int destroyingcount;		//撃破数
};