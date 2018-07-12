#pragma once

#include <vector>

class Textrue {};
class Sound {};


///<summary>
///描画順を設定するクラス
///</summary>
class DrawOrder
{
public:
	///<summary>
	///コンストラクタ
	///</summary>
	DrawOrder();


	///<summary>
	///デストラクタ
	///</summary>
	~DrawOrder();


	///<summary>
	///<para>描画優先度を設定します</para>
	///<para>0.0f ～ デフォルト(1.0f)</para>
	///</summary>
	void setDrawOrder(float&);


	///<summary>
	///描画の優先度を返します
	///<summary>
	float getDrawOrder()const;


private:
	///<summary>
	///描画順の優先度 範囲: 0.0 ～ 1.0
	///</summary>
	float order;
};


///<summary>
///リソースを管理するクラス
///</summary>
class ResourceManager
{
public:
	///<summary>
	///コンストラクタ
	///</summary>
	ResourceManager();


	///<summary>
	///デストラクタ
	///<summary>
	~ResourceManager();


	///<summary>
	///テクスチャをシステムに登録します
	///</summary>
	void setTextrue(const std::string& ,Textrue*);


	///<summary>
	///サウンドをシステムに登録します
	///</summary>
	void setSound(const std::string&, Sound*);


	///<summary>
	///登録してあるテクスチャから指定のテクスチャを取得します (string: テクスチャ名)
	///</summary>
	///<returns>
	///テクスチャ名と一致したテクスチャのポインタ
	///</returns>
	Textrue* getTextrue(const std::string&)const;


	///<summary>
	///登録してあるサウンドから指定のサウンドを取得します (string: サウンド名)
	///</summary>
	///<returns>
	///サウンド名と一致したサウンドのポインタ
	///</returns>
	Sound* getSound(const std::string&)const;


	///<summary>
	///登録してあるテクスチャ・サウンドを全削除します
	///</summary>
	void DeleteResource();


private:
	///<summary>
	///登録しているテクスチャ
	///</summary>
	std::vector<std::pair<std::string, Textrue*>> textrues;


	///<summary>
	///登録されているサウンド
	///</summary>
	std::vector<std::pair<std::string, Sound*>>   sounds;
};
