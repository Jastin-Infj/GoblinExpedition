#pragma once
#include "../TaskSystem/TaskObject.h"
#include "../InterFace/ShapeMouseCursor.hpp"
class Title : public TaskObject
{
public:
	typedef std::shared_ptr<Title> SP;		//シェアポインタ
	typedef std::weak_ptr<Title>   WP;		//ウィークポインタ


	///<summary>
	///コンストラクタ
	///</summary>
	Title();


	///<summary>
	///デストラクタ
	///</summary>
	virtual ~Title();

	
	///<summary>
	///<para>初期化処理</para>
	///引数:グループ名・タスク名
	///</summary>
	///<param name = "taskname">グループ名・タスク名</param>
	bool Init(const std::pair<std::string, std::string>& taskname);


	///<summary>
	///更新処理
	///</summary>
	void Update()override;


	///<summary>
	///描画処理 使用しない
	///</summary>
	void Render()override;


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

private:

	/// <summary>
	/// マウスと対象の図形との当たり判定を行います
	/// </summary>
	void MouseHitleftClicked_update();
private:
	ShapeMouseCursor* shapemouse;		//マウスカーソル図形
};