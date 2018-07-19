#include "CharaBace.h"
#include "../TaskSystem/TaskSystem.h"
#include "../ResourceManager/ResourceManager.h"
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
bool CharaBace::Init(const std::pair<std::string, std::string>& taskname_, Type type_, Point& pos, Point& scale_,float order)
{
	__super::setTaskName(taskname_);

	//対象のタイプ設定
	this->type = type_;
	
	//DrawInterFaceを生成する
	this->draw = new DrawInterFace();
	/*対象オブジェクトによってそれぞれのテクスチャを貼り付ける*/
	this->draw->setTexture(this->getResoruceManagerTexture());


	//初期座標位置の設定
	this->position = pos;
	//描画サイズを設定
	this->scale = scale_;
	//描画矩形の生成
	this->draw->setDrawBace(this->position, this->scale);
	//描画優先順位の設定
	this->setDrawOrder(order);



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
		this->draw->Draw(this->draw->getDrawBace(),this->draw->getSrcBace());
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
CharaBace::SP CharaBace::Create(const std::pair<std::string, std::string>& taskname, Type type, Point pos, Point scale, float order, bool flag)
{
	CharaBace::SP to = CharaBace::SP(new CharaBace());
	if (to)
	{
		/*自分のアドレス値を渡す*/
		to->me = to;
		/*各値の初期化値を設定*/
		if (!to->Init(taskname,type,pos,scale,order))
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
	switch (this->type)
	{
		/* 背景 */
	case Type::Back:
		//画像元矩形の生成
		this->draw->setDrawSrc(0,0,680,480);
		//テクスチャの貼り付け
		return rm->getTexture("インゲーム背景");
		break;
		/* UI */
	case Type::UI:
		//画像元矩形の生成
		
		//テクスチャの貼り付け
		return rm->getTexture("ライフ");
		break;
		/* プレイヤ */
	case Type::Player:
		//画像元矩形の生成

		//テクスチャの貼り付け
		return rm->getTexture("プレイヤ");
		break;
		/* 敵 */
	case Type::Enemy:
		//画像元矩形の生成
		this->draw->setDrawSrc(0, 0, 64, 64);
		//テクスチャの貼り付け
		return rm->getTexture("ゴブリン");
		break;
		/* アイテム */
	case Type::Item:
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
constexpr bool CharaBace::TypeCheck(const Type& type_ , const Type& target)const
{
	return type_ == target ? true : false;
}