#pragma once
#include "../TaskSystem/TaskObject.h"

#define ENEMY_CREATE_TIME 30		//敵が生成までにかかる時間
#define ENEMY_CREATE_SIZE 5			//一回の生成でどれくらいの敵を生成するか
#define ENEMY_RANDOM_Y    352		//ランダムの範囲

#define SCORE_INIT        0			//スコアの初期化値
#define SCORE_MIN         0			//スコアの最小値
#define SCORE_MAX         99999     //スコア最大値

class Game : public TaskObject
{
public:
	typedef std::shared_ptr<Game> SP;


	///<summary>
	///コンストラクタ
	///</summary>
	Game();


	///<summary>
	///デストラクタ
	///</summary>
	virtual ~Game();

	
	///<summary>
	///<para>初期化処理<para>
	///引数:グループ名・タスク名
	///<summary>
	///<param name="taskname">グループ名・タスク名</param>
	bool Init(const std::pair<std::string, std::string>& taskname);


	///<summary>
	///更新処理
	///</summary>
	void UpDate()override;


	///<summary>
	///描画処理 使用しない
	///</summary>
	void Render()override {};


	///<summary>
	///<para>解放処理</para>
	///<para>解放 成功/失敗 true:false</para>
	///</summary>
	bool Finalize()override;


	///<summary>
	///<para>オブジェクトを生成します</para>
	///<para>引数: グループ名・タスク名 , (タスクシステムに登録するか)
	///<returns>オブジェクトのスマートポインタを返します</returns>
	///</summary>
	static TaskObject::SP Create(const std::pair<std::string, std::string>& taskname, bool flag = true);


	/// <summary>
	/// 敵をランダム生成します
	/// </summary>
	void Enemy_Create();


//外部で使用するメソッド

	/// <summary>
	/// スコアを加算させます
	/// </summary>
	/// <param name="addtion">
	/// スコアに加算する値
	/// </param>
	void ScoreAddition(const int& addition);


	/// <summary>
	/// 現在のスコアを返します
	/// </summary>
	/// <returns>
	/// 現在のスコア
	/// </returns>
	int  getScore()const;
private:
	float enemycreatetime;		//敵が生成するまでの時間
	int   score;				//スコア
};