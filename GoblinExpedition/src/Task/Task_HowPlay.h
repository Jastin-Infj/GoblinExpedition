#pragma once
#include "../TaskSystem/TaskObject.h"
#include "../InterFace/ShapeMouseCursor.hpp"

class HowPlay : public TaskObject
{
public:
	typedef std::shared_ptr<HowPlay> SP;		//スマートポインタ
	typedef std::weak_ptr<HowPlay>   WP;		//ウィークポインタ


											/// <summary>
											/// コンストラクタ
											/// </summary>
	HowPlay();


	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~HowPlay();


	/// <summary>
	/// リザルト初期化
	/// </summary>
	/// <param name="taskname_">
	/// タスク名(グループ名・タスク名)
	/// </param>
	/// <returns>
	/// 初期化終了 true 
	/// </returns>
	bool Init(const std::pair<std::string, std::string>& taskname_);


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
	/// 解放する true 
	/// </returns>
	bool Finalize()override;


	/// <summary>
	/// リザルト画面を生成します
	/// </summary>
	/// <param name="taskname">
	/// タスク名(グループ名・タスク名)
	/// </param>
	/// <param name="flag">
	/// タスクシステムに登録をするか する true /  しない false
	/// </param>
	/// <returns>
	/// 生成出来た true / 生成出来ない false
	/// </returns>
	static TaskObject::SP Create(const std::pair<std::string, std::string>& taskname, bool flag = true);


	/// <summary>
	/// マウスと対象の図形との当たり判定を行います
	/// </summary>
	void MouseHitleftClicked_update();
private:
	ShapeMouseCursor* shapemouse;		//図形ありマウスカーソル
};