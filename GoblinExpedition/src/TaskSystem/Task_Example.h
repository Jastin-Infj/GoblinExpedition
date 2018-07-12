#pragma once
#include "../TaskSystem/TaskSystem.h"
#include "../TaskSystem/TaskObject.h"

///<summary>
///タイトルシーン全体を扱うクラス
///</summary>
class TaskObjectExample : public TaskObject
{
public:

	///<summary>
	///スマートポインタ宣言を省略します
	///</summary>
	typedef std::shared_ptr<TaskObjectExample> SP;


	///<summary>
	///ウィークポインタ宣言を省略します
	///</summary>
	typedef std::shared_ptr<TaskObjectExample> WP;



///メンバ関数

	///<summary>
	///コンストラクタ
	///</summary>
	TaskObjectExample();


	///<summary>
	///デストラクタ
	///</summary>
	virtual ~TaskObjectExample();


	///<summary>
	///<para>初期化処理</para>
	///<para>引数: グループ名・タスク名</para>
	///</summary>
	bool Init(std::pair<std::string, std::string>&)override;


	///<summary>
	///オブジェクトを生成します
	///</summary>
	///<returns>
	///生成が出来た:スマートポインタ  出来ない:nullptr
	///</returns>
	static TaskObjectExample::SP Create(std::pair<std::string,std::string>&, bool = true);


private:


///メンバ関数

	///<summary>
	///更新処理
	///</summary>
	void UpDate()override;


	///<summary>
	///描画処理
	void Render()override;
};