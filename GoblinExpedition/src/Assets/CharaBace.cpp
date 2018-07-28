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
	const Point&							   pos,
	const Point&							   scale_,
	float									   order_,
	bool							           draw_,
	bool								       collider_,
	bool						               move_
)
{
	__super::setTaskName(taskname_);

	//初期座標位置の設定
	this->position = pos;
	//描画サイズを設定
	this->scale = scale_;

	//移動機能をつける
	if (move_)
	{
		this->move = new MoveInterFace();
		this->setObjectTypeMoveSpeed();
	}
	else
	{
		this->move = nullptr;
	}

	//描画優先順位の設定
	this->setDrawOrder(order_);


	return true;
}
/*更新処理*/
void CharaBace::UpDate()
{
	/*移動出来るオブジェクトは移動モーションします*/
	if (this->move != nullptr)
	{
		this->ObjectTypeMove();
	}
}
/*描画処理*/
void CharaBace::Render()
{
	/*アドレス値がnullptr*/
	if (!draw)
	{
		MessageBox(NULL, L"アドレス値がミスっています", L"中身がnullptrでした", MB_OK);
	}
	/*描画をする*/
	{
		Rect src = this->draw->getSrcBace();
		this->ObjecytypeDraw();
	}
}
bool CharaBace::Finalize()
{
	if (this->enemyfunction != nullptr)
	{
		delete this->enemyfunction;
		this->enemyfunction = nullptr;
	}
	if (this->collider != nullptr)
	{
		delete this->collider;
		this->collider = nullptr;
	}
	if (this->draw != nullptr)
	{
		delete this->draw;
		this->draw = nullptr;
	}
	if (this->move != nullptr)
	{
		delete this->move;
		this->move = nullptr;
	}
	return true;
}
/*オブジェクトの生成*/
CharaBace::SP CharaBace::Create(
	const std::pair<std::string, std::string>& taskname,
	const Point&							   pos,
	const Point&							   scale,
	float									   order,
	bool								       collider,
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
		if (!to->ParameterInit(taskname, objecttype, pos, scale, order, collider, drawinterface, moveinterface))
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
void CharaBace::setResoruceManagerTexture()const
{
	switch (this->objecttype)
	{
		/* 背景 */
	case ObjectType::Back:
		//画像元矩形の生成
		break;
		/* UI */
	case ObjectType::UI:
		//画像元矩形の生成
		if (this->isTasknameSecond("プレイヤライフ"))
		{
			
		}
		break;
		/* プレイヤ */
	case ObjectType::Player:

		break;
		/* 敵 */
	case ObjectType::Enemy:
		//画像元矩形の生成
		
		break;
		/* アイテム */
	case ObjectType::Item:
		//画像元矩形の生成

		//テクスチャの貼り付け
		this->draw->setTexture(rm->getTexture("アイテム"));
		break;
	default:
		break;
	}
}
/*オブジェクトタイプによって描画方法を変化させます*/
void CharaBace::ObjecytypeDraw()
{
	switch (this->objecttype)
	{
	case ObjectType::Player:
		this->draw->PaletteColorDraw(this->draw->getDrawBace(), Palette::Red);
		//当たり判定矩形描画
		this->draw->PaletteColorDraw(this->collider->getHitBace(), Palette::White);
		break;
	case ObjectType::Enemy:
		if (this->enemyfunction->getleftrightinversionflag())
		{
			this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace(),true);
		}
		else
		{
			this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
		}
		break;
	default:
		this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
		break;
	}
}
/*当たり判定矩形を各自設定します*/
void CharaBace::setObjectTypeCollider()
{
	switch (this->objecttype)
	{
	case ObjectType::Player:
		
		break;
	case ObjectType::Enemy:
		
		break;
	default:
		break;
	}
}
/*オブジェクトタイプによって移動量の設定を行います*/
void CharaBace::setObjectTypeMoveSpeed()
{
	switch (this->objecttype)
	{
	case ObjectType::Enemy:
		if (this->enemyfunction->getleftrightinversionflag())
		{
			this->move->setMovespeed(Point(-3,0));
		}
		else
		{
			this->move->setMovespeed(Point(3, 0));
		}
		break;
	default:
		break;
	}
}
/*オブジェクトタイプによって移動方法を設定します*/
void CharaBace::ObjectTypeMove()
{
	switch (this->objecttype)
	{
	case ObjectType::Enemy:
		//等速直線運動で動く
		this->move->UniformLinearMotion(this->position);
		//矩形を再設定
		if (this->draw != nullptr)
		{
			this->draw->setDrawBace(this->position, this->scale);
		}
		if (this->collider != nullptr)
		{
			this->collider->setHitBace(this->position, this->scale);
		}

		//マウス当たり判定処理
		if (this->collider->MouseLeftPressed())
		{
			//敵を倒す
			this->Kill();
		}

		if (this->enemyfunction->getleftrightinversionflag() && this->position.x <= -this->scale.x)
		{
			std::cout << "マップ外" << std::endl;
			this->Kill();
		}
		else
		{
			std::cout << Window::GetPos().x << "   " << this->position.x << std::endl;
		}
		break;
	default:
		break;
	}
}
/*オブジェクトタイプがtargetであるかを判定します*/
constexpr bool CharaBace::ObjectTypeCheck(const ObjectType& ObjectType_, const ObjectType& target)const
{
	return ObjectType_ == target ? true : false;
}
/*座標を設定・変更します*/
void CharaBace::setPosition(const Point& pos)
{
	this->position = pos;
}
/*現在の座標を返します*/
Point CharaBace::getPosition()const
{
	return this->position;
}
/*オブジェクトタイプを返します*/
ObjectType CharaBace::getObjectType()const
{
	return this->objecttype;
}


//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★



//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★



//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★

