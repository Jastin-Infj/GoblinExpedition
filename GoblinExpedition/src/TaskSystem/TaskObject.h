#pragma once
#include <vector>
#include <memory>

///<summary>
///
///</summary>
///<returns>
///
///</returns>

///<summary>
///タスクを消滅させるクラス
///</summary>
class KillTaskSystem
{
public:

	///メンバ関数

	///<summary>
	///コンストラクタ
	///</summary>
	KillTaskSystem();


	///<summary>
	///デストラクタ
	///</summary>
	~KillTaskSystem();


	///<summary>
	///キルカウンタを増加させます
	///</summary>
	///<returns>
	///なし
	///</returns>
	void KillCount();


	///<summary>
	///消滅させるかどうかを判定します
	///</summary>
	///<returns>
	///消滅させる　true : 消滅しない false
	///</returns>
	bool KillCheck();


	///<summary>
	///killcountを返します
	///</summary>
	int getKillcount()const;

private:

	///メンバ変数

	///<summary>
	///キルカウンタ
	///</summary>
	int killcount;
};


///<summary>
///新しいオブジェクトを生成するクラス
///</summary>
class TaskObject : private KillTaskSystem
{
public:
///メンバ変数

	///<summary>
	///スマートポインタ
	///</summary>
	typedef std::shared_ptr<TaskObject> SP;


	///<summary>
	///ウィークポインタ
	///</summary>
	typedef std::weak_ptr<TaskObject>   WP;


	///<summary>
	///自分のデータ
	///</summary>
	TaskObject::WP me;

///メンバ関数


	///<summary>
	///コンストラクタ
	///</summary>
	///<returns>
	///なし
	///</returns>
	TaskObject();


	///<summary>
	///デストラクタ
	///</summary>
	virtual ~TaskObject();


	///<summary>
	///初期化処理
	///</summary>
	///<returns>
	///初期化処理終了 true
	///</returns>
	virtual bool Init(std::pair<std::string, std::string>&);

	///<summary>
	///更新処理
	///</summary>
	///<returns>
	///なし
	///</returns>
	virtual void UpDate();


	///<summary>
	///描画処理
	///</summary>
	///<returns>
	///なし
	///</returns>
	virtual void Render();


	///<summary>
	///解放処理
	///</summary>
	///<returns>
	///解放処理終了　true
	///</returns>
	virtual bool Finalize();


	///<summary>
	///キルカウンタを増加させます
	///</summary>
	///<returns>
	///なし
	///</returns>
	void Kill();

	///<summary>
	///Killカウンタを返します
	///</summary>
	int  getKillCounter()const;



	///<summary>
	///グループ名・タスク名を返します
	///</summary>
	std::pair<std::string,std::string> getTaskname()const;


	///<summary>
	///グループ名・タスク名をセットします
	///</summary>
	void setTaskName(std::pair<std::string, std::string>&);


	///<summary>
	///次回のタスクが生成できる状況かを返します
	///</summary>
	bool getNextTask()const;


	///<summary>
	///次回のタスクを生成出来るかを変更します
	///</summary>
	void setNextTask(const bool);


	///<summary>
	///ポーズフラグを返します
	///</summary>
	///<returns>
	///ポーズ中:true ポーズではない:false
	///</returns>
	bool getisPause()const;


	///<summary>
	///<para>ポーズを設定します</para>
	///<para>中断する true 中断解除 false </para>
	///</summary>
	///<returns>
	///なし
	///</returns>
	void setPause(const bool);


private:

///メンバ変数

	///<summary>
	///グループ名 , タスク名
	///</summary>
	std::pair<std::string, std::string> taskname;

	///<summary>
	///終了時に次のタスクが生成できるか
	///</summary>
	bool NextTask;

	///<summary>
	///<para>ポーズ処理フラグ</para>
	///<para>ポーズ中:true ポーズしていない:false</para>
	///</summary>
	bool isPause;


///メンバ関数
	


};