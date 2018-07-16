#pragma once
#include "../TaskSystem/TaskSystem.h"
#include "../TaskSystem/TaskObject.h"

///<summary>
///タスクシステムを扱う雛形クラスです
///</summary>
class TaskObjectExample : public TaskObject
{
public:
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
	static TaskObject::SP Create(std::pair<std::string,std::string>&, bool = true);


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