#include "CharaBace.h"
#include "../TaskSystem/TaskSystem.h"
#include "../ResourceManager/ResourceManager.h"
#include "../InterFace/Collider.hpp"
#include "../InterFace/MoveInterFace.hpp"
#include <iostream>
#include <Windows.h>
/*コンストラクタ*/
CharaBace::CharaBace()
{
#if _DEBUG
	std::cout << "CharaBace()" << std::endl;
#endif // _DEBUG
}
/*デストラクタ*/
CharaBace::~CharaBace()
{
#if _DEBUG
	std::cout << "~CharaBace()" << std::endl;
#endif // _DEBUG
	this->Finalize();
}
/*初期化処理をします*/
bool CharaBace::ParameterInit(
	const std::pair<std::string, std::string>& taskname_, 
	ObjectType								   objecttype_, 
	const Point&							   pos, 
	const Point&							   scale_,
	float									   order_, 
	bool								       hitbace_, 
	bool							           draw_, 
	bool						               move_
)
{
	__super::setTaskName(taskname_);

	//初期座標位置の設定
	this->position = pos;
	//描画サイズを設定
	this->scale = scale_;

	//対象のタイプ設定
	this->objecttype = objecttype_;
	
	//当たり判定機能
	if (hitbace_)
	{
		this->hitbace = new Collider(Collider::ShapeHitType::Cube,this->position,this->scale);
	}

	//DrawInterFaceを生成する
	if (draw_)
	{
		this->draw = new DrawInterFace();
	}
	if (draw != nullptr)
	{
		/*対象オブジェクトによってそれぞれのテクスチャを貼り付ける*/
		this->draw->setTexture(this->getResoruceManagerTexture());
		//描画矩形の生成
		this->draw->setDrawBace(this->position, this->scale);
	}

	//移動機能をつける
	if (move_)
	{
		this->move = new MoveInterFace();
	}
	
	
	//描画優先順位の設定
	this->setDrawOrder(order_);


	return true;
}
/*更新処理*/
void CharaBace::UpDate() 
{
	
}
/*描画処理*/
void CharaBace::Render()
{
	/*アドレス値がnullptr*/
	if (!draw)
	{
		MessageBox(NULL, L"アドレス値がミスっています", L"中身がnullptrでした", MB_OK);
	}

	Rect src = this->draw->getSrcBace();
	/*描画をする*/
	{
		if (this->objecttype != ObjectType::Player)
		{
			this->draw->Draw(this->draw->getDrawBace(),this->draw->getSrcBace());
		}
		else
		{
			this->draw->PalletColorDraw(this->position , this->scale , Palette::Red);
		}
	}
}
bool CharaBace::Finalize()
{
	if (draw != nullptr)
	{
		delete this->draw;
	}
	return true;
}
/*オブジェクトの生成*/
CharaBace::SP CharaBace::Create(
	const std::pair<std::string, std::string>& taskname,
	ObjectType								   objecttype,
	const Point&							   pos,
	const Point&							   scale,
	float									   order,
	bool								       hitbace,
	bool									   drawinterface,
	bool								       moveinterface,
	bool									   flag
)
{
	CharaBace::SP to = CharaBace::SP(new CharaBace());
	if (to)
	{
		/*自分のアドレス値を渡す*/
		to->me = to;
		/*各値の初期化値を設定*/
		if (!to->ParameterInit(taskname,objecttype,pos,scale,order,hitbace,drawinterface,moveinterface))
		{
			/*初期化が成功しなければ削除*/
			to->Kill();
		}
		if (flag)
		{
			/*システムに登録*/
			taskSystem->Add(to);
		}
		return to;
	}
	return nullptr;
}
/*ResourceManagerからTextureを貼り付けします*/
Texture CharaBace::getResoruceManagerTexture()const
{
	switch (this->objecttype)
	{
		/* 背景 */
	case ObjectType::Back:
		//画像元矩形の生成
		this->draw->setDrawSrc(0,0,680,480);
		//テクスチャの貼り付け
		return rm->getTexture("インゲーム背景");
		break;
		/* UI */
	case ObjectType::UI:
		//画像元矩形の生成
		
		//テクスチャの貼り付け
		return rm->getTexture("ライフ");
		break;
		/* プレイヤ */
	case ObjectType::Player:

		break;
		/* 敵 */
	case ObjectType::Enemy:
		//画像元矩形の生成
		this->draw->setDrawSrc(0, 0, 64, 64);
		//テクスチャの貼り付け
		return rm->getTexture("ゴブリン");
		break;
		/* アイテム */
	case ObjectType::Item:
		//画像元矩形の生成

		//テクスチャの貼り付け
		return rm->getTexture("アイテム");
		break;
	default:
		break;
	}
	/*空のテクスチャ*/
	return Texture();
}
/*オブジェクトタイプがBackであるかを判定します*/
constexpr bool CharaBace::ObjectTypeCheck(const ObjectType& ObjectType_ , const ObjectType& target)const
{
	return ObjectType_ == target ? true : false;
}