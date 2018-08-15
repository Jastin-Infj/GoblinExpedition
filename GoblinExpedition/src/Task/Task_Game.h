#pragma once
#include "../TaskSystem/TaskObject.h"

#define ENEMY_CREATE_TIME 90		//敵が生成までにかかる時間
#define ENEMY_CREATE_SIZE 5			//一回の生成でどれくらいの敵を生成するか
#define ENEMY_RANDOM_Y    352		//ランダムの範囲

#define ENEMY_DESTROYINGCOUNT_INIT  0		//敵の撃破数　初期化値
#define ENEMY_DESTROYINGCOUNT_MIN   0		//敵の撃破数　最小値
#define ENEMY_DESTROYINGCOUNT_MAX  999		//敵の撃破数　最大値

#define SCORE_INIT        0			//スコアの初期化値
#define SCORE_MIN         0			//スコアの最小値
#define SCORE_MAX         99999     //スコア最大値

#define MUSOUITEM_CREATECOUNT  1	//無双アイテムを生成するタイミング

class Game : public TaskObject
{
public:
	typedef std::shared_ptr<Game> SP;		//シェアポインタ
	typedef std::weak_ptr<Game>   WP;		//ウィークポインタ


	/// <summary>
	/// ゲームの状況を示す
	/// </summary>
	enum class GameState
	{
		Normal,		//通常状態
		LifeZero,	//ライフが0
		ESCAPE,		//エスケープが押された
	};

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
	void Update()override;


	///<summary>
	///描画処理 使用しない
	///</summary>
	void Render()override {};


	///<summary>
	///<para>解放処理</para>
	///<para>解放 成功/失敗 true:false</para>
	///</summary>
	bool Finalize()override;


	/// <summary>
	/// ゲームシーンを生成します
	/// </summary>
	/// <param name="taskname">
	/// ゲームシーン名(グループ名・タスク名)
	/// </param>
	/// <param name="flag">
	/// タスクシステムに登録をするか true / false
	/// </param>
	/// <returns>
	/// ゲームシーンのポインタ
	/// </returns>
	static TaskObject::SP Create(const std::pair<std::string, std::string>& taskname, bool flag = true);


	/// <summary>
	/// 敵をランダム生成します
	/// </summary>
	void Enemy_Create();


	/// <summary>
	/// 無双アイテムを生成して良いかを判定します
	/// </summary>
	/// <returns>
	/// 生成出来る true / 生成出来ない false
	/// </returns>
	bool isMusouItemCreate()const;

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


	/// <summary>
	/// 敵の撃破数カウントを増加させます
	/// </summary>
	/// <param name="destroyingcount">
	/// 敵の撃破数ポイント
	/// </param>
	void Enemy_DestroyingCount_Add(const int& destroyingcount);


	/// <summary>
	/// 無双アイテムを生成します
	/// </summary>
	void MusouItem_Create();


	/// <summary>
	/// ゲーム状況を変化させます
	/// </summary>
	/// <param name="gamestate">
	/// 変化させるゲーム状態
	/// </param>
	void ChengeGameState(const GameState gamestate);


	/// <summary>
	/// ゲーム状況を返します
	/// </summary>
	/// <returns>
	/// ゲーム状況
	/// </returns>
	GameState getGameState()const;

private:
	float enemycreatetime;				//敵が生成するまでの時間
	int   score;						//スコア
	int   enemy_destroyingcount;		//敵の撃破数
	GameState gamestate;				//今のゲーム状況
};