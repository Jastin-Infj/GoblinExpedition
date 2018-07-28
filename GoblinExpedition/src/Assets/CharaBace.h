#pragma once
#include <Siv3D.hpp>

//追加したい機能はここに記述する
#include "../TaskSystem/TaskObject.h"
#include "../InterFace/DrawInterFace.hpp"
#include "../InterFace/MoveInterFace.hpp"
#include "../InterFace/Collider.hpp"



///<summary>
///オブジェクトクラス
///</summary>
class CharaBace : public TaskObject
{
public:
	typedef std::shared_ptr<CharaBace> SP;


	///<summary>
	///コンストラクタ
	///</summary>
	CharaBace();


	///<summary>
	///デストラクタ
	///</summary>
	virtual ~CharaBace();


	/// <summary>
	/// パラメータの初期化設定
	/// </summary>
	/// <param name="taskname">
	/// グループ名・タスク名
	/// </param>
	/// <param name="objecttype">
	/// 生成オブジェクトタイプ
	/// </param>
	/// <param name="pos">
	/// 初期座標
	/// </param>
	/// <param name="scale">
	/// 描画の大きさ
	/// </param>
	/// <param name="order">
	/// 描画の優先順位
	/// </param>
	/// <param name="hitbace">
	/// 当たり判定矩形
	/// </param>
	/// <param name="draw">
	/// 描画機能
	/// </param>
	/// <param name="move">
	/// 移動機能
	/// </param>
	/// <returns>
	/// 初期化出来る / true (falseなし)
	/// </returns>
	bool ParameterInit
	(
		const std::pair<std::string, std::string>& taskname, 
		const Point&							   pos, 
		const Point&							   scale,
		float									   order,
		bool									   hitbace,
		bool									   draw,
		bool									   move
	);


	/// <summary>
	/// オブジェクトを生成します
	/// </summary>
	/// <param name="taskname">
	/// グループ名・タスク名
	/// </param>
	/// <param name="objecttype">
	/// 生成オブジェクトタイプ
	/// </param>
	/// <param name="pos">
	/// 初期座標
	/// </param>
	/// <param name="scale">
	/// 描画の大きさ
	/// </param>
	/// <param name="order">
	/// 描画の優先順位
	/// </param>
	/// <param name="hitbace">
	/// 当たり判定機能　追加 / 追加なし(false)
	/// </param>
	/// <param name="drawinterface">
	/// 描画機能　追加 / 追加なし(false)
	/// </param>
	/// <param name="moveinterface">
	/// 移動機能　追加 / 追加なし(false)
	/// </param>
	/// <param name="flag">
	/// システムに登録する (true)/しない(false)
	/// </param>
	/// <returns>
	/// 生成したオブジェクトのスマートポインタ
	/// </returns>
	static CharaBace::SP Create
	(
		const std::pair<std::string, std::string>& taskname, 
		const Point&							   pos, 
		const Point&							   scale,
		float									   order, 
		bool								       hitbace = false,
		bool                                       drawinterface = false,
		bool									   moveinterface = false,
		bool									   flag = true
	);


	/// <summary>
	/// 座標の設定・変更をします
	/// </summary>
	/// <param name="pos">
	/// 設定する座標
	/// </param>
	void setPosition(const Point& pos);


	/// <summary>
	/// 現在の座標を返します
	/// </summary>
	/// <returns>
	/// 現在の座標
	/// </returns>
	Point getPosition()const;

//=================================================================================================

	struct EnemyFunction
	{
		
	private:
		
	};
//==================================================================================================
private:
	Point          position;		//現在位置
	Point          scale;			//大きさ
	DrawInterFace* draw;			//描画機能
	Collider*      collider;		//当たり判定機能
	MoveInterFace* move;			//移動機能
	EnemyFunction* enemyfunction;	//敵の機能

	///<summary>
	///オブジェクトの更新処理
	///</summary>
	void UpDate()override;


	///<summary>
	///描画処理
	///</summary>
	void Render()override;


	///<summary>
	///解放処理
	///</summary>
	bool Finalize()override;


	///<summary>
	///テクスチャをResourceManagerから取得して対象のオブジェクトタイプによってテクスチャを返します
	///</summary>
	void setResoruceManagerTexture()const;


	/// <summary>
	/// オブジェクトタイプによって描画方法を変化させます
	/// </summary>
	void ObjecytypeDraw();


	/// <summary>
	/// オブジェクトタイプによって当たり判定矩形を設定します
	/// </summary>
	void setObjectTypeCollider();


	/// <summary>
	/// オブジェクトタイプによって移動量を設定します
	/// </summary>
	void setObjectTypeMoveSpeed();


	/// <summary>
	/// オブジェクトタイプによって移動方法を設定します
	/// </summary>
	void ObjectTypeMove();
};