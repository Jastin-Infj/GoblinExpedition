#pragma once
#include <Siv3D.hpp>
#include <vector>


//class Texture {};
//class Sound {};


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


	/// <summary>
	/// 描画優先度を設定します
	/// </summary>
	/// <param name="order_">
	/// 描画優先順位
	/// </param>
	void setDrawOrder(float order_);


	///<summary>
	///描画の優先度を返します
	///</summary>
	const float getDrawOrder()const;

	
	/// <summary>
	/// 描画IDを設定します
	/// </summary>
	/// <param name="resource_id">
	/// ResourceID
	/// </param>
	void setDrawOrderID(int& resource_id);


	///<summary>
	///描画IDを返します
	///</summary>
	///<returns>
	///描画ID 
	///</returns>
	int getDrawOrderID()const;


private:
	float order;	//描画順の優先度
	int   id;		//タスク描画ID
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

	
	/// <summary>
	/// テクスチャをシステムに登録します
	/// </summary>
	/// <param name="texturename">
	/// テクスチャ名
	/// </param>
	/// <param name="texture">
	/// 登録するテクスチャ
	/// </param>
	void setTexture(const std::string& texturename ,const Texture& texture);


	///<summary>
	///サウンドをシステムに登録します
	///</summary>
	/// <param name="soundname">
	/// サウンド名
	/// </param>
	/// <param name="sound">
	/// 登録するサウンド
	/// </param>
	void setSound(const std::string& soundname, const Sound& sound);


	///<summary>
	///登録してあるテクスチャから指定のテクスチャを取得します
	///</summary>
	/// <param name="texturename">
	/// 検索ワード
	/// </param>
	/// <returns>
	/// テクスチャ名と一致したテクスチャ
	/// </returns>
	Texture getTexture(const std::string& texturename)const;


	///<summary>
	///登録してあるサウンドから指定のサウンドを取得します
	///</summary>
	/// <param name="soundname">
	/// 検索ワード
	/// </param>
	///<returns>
	///サウンド名と一致したサウンドのポインタ
	///</returns>
	Sound getSound(const std::string& soundname)const;


	///<summary>
	///登録してあるテクスチャ・サウンドを全削除します
	///</summary>
	void DeleteResource();


	///<summary>
	///登録してあるテクスチャを全て削除をします
	///</summary>
	void DeleteTextrue();


	///<summary>
	///登録してあるサウンドを全て削除をします
	///</summary>
	void DeleteSound();

private:
	///<summary>
	///登録しているテクスチャ
	///</summary>
	std::vector<std::pair<std::string, Texture>> textures;


	///<summary>
	///登録されているサウンド
	///</summary>
	std::vector<std::pair<std::string, Sound>>   sounds;
};
extern ResourceManager* rm;		//ResourceManagerにアクセス用変数