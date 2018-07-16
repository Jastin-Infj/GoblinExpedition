#pragma once
#include <Siv3D.hpp>

//追加したい機能はここに記述する
#include "../TaskSystem/TaskObject.h"
#include "../InterFace/DrawInterFace.hpp"
#include "../InterFace/ObjectType.h"

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


	///<summary>
	///<para>初期化処理</para>
	///<para>グループ名・タスク名 , 対象オブジェクト , 初期座標位置 , 描画サイズ , 描画優先順位 </para>
	///<returns>初期化　成功/失敗 true : false</returns>
	///</summary>
	bool Init(std::pair<std::string, std::string>& taskname, Type type, Point& pos, Point& scale,float order);


	///<summary>
	///<para>オブジェクトの生成をします</para>
	///<para>グループ名・タスク名 , 描画する対象,初期座標位置 ,描画するサイズ ,(タスクシステムに登録するか true : false) </para>
	///</summary>
	static CharaBace::SP Create(std::pair<std::string, std::string>& taskname, Type type, Point pos, Point scale, float order, bool flag = true);


private:
	DrawInterFace* draw;		//描画機能
	Type           type;		//扱っている対象
	Point          position;	//現在位置
	Point          scale;		//大きさ

	///<summary>
	///更新処理
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
	///<returns>テクスチャのアドレス値</returns>
	Texture getResoruceManagerTexture()const;

//=================================================================================================
};