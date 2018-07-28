#include "Enemy.h"
#include <iostream>
/*コンストラクタ*/
Enemy::Enemy()
{
#ifdef _DEBUG
	std::cout << "Enemy()" << std::endl;
#endif // _DEBUG
}
/*デストラクタ*/
Enemy::~Enemy()
{
	this->Finalize();
#ifdef _DEBUG
	std::cout << this->getTaskname().second << "~Enemy()" << std::endl;
#endif // _DEBUG
}
/*パラメータの初期化設定*/
bool Enemy::Init_Parameter(const TASKNAME& taskname_, const ObjectType& objecttype_, const Vec2& position_, const Point& scale_, const float& order_)
{
	/*タスク名を設定*/
	__super::setTaskName(taskname_);
	/*描画優先順位を設定*/
	__super::setDrawOrder(this->order = order_);

	this->position = position_;
	this->scale = scale_;
	this->objecttype = objecttype_;

	//追加の初期化項目
	void(Enemy::*Func[2])() = { &Enemy::Goburin_Parameter , nullptr};
	(this->*Func[(int)this->objecttype])();
	this->setleftrightinversionflag(false);

	return true;
}
/*解放処理*/
bool Enemy::Finalize()
{
	return true;
}
/*更新処理*/
void Enemy::UpDate()
{
	if (this->getleftrightinversionflag())
	{
		this->move->setMovespeed(Point(-3, 0));
		this->collider->setHitBace(this->position, this->scale);
	}
	else
	{
		this->move->setMovespeed(Point(3, 0));
		this->collider->setHitBace(this->position, this->scale);
	}
	this->move->UniformLinearMotion(this->position);
	
	/*反転判定を行います*/
	this->LeftRightInversion();
	if (this->OutsideMap() && this->getleftrightinversionflag())
	{
		this->Kill();
	}
}
/*描画をします*/
void Enemy::Render()
{
	this->draw->setDrawBace(this->position, this->scale);
	this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace());
}
/*Player当たり判定矩形と接触判定を行います*/
bool Enemy::onHitbaceExit(const RectF& target)const
{
	return this->collider->Hit(target);
}
/*左右反転フラグを返します*/
bool Enemy::getleftrightinversionflag()const
{
	return this->leftrightinversionflag;
}
/*左右反転フラグを設定します*/
void Enemy::setleftrightinversionflag(bool flag)
{
	this->leftrightinversionflag = flag;
}
/*左右反転フラグをチェンジします*/
void Enemy::changeleftrightinversionflag()
{
	this->leftrightinversionflag = !this->leftrightinversionflag;
}
/*左右反転判定をします*/
void Enemy::LeftRightInversion()
{
	Player::WP player = taskSystem->GetTask_TaskName<Player>("自キャラ");
	if (!player.expired())
	{
		Player::SP temp = player.lock();
		if (this->onHitbaceExit(temp->getHitBace()))
		{
			/*反転フラグをtrueにする*/
			this->setleftrightinversionflag(true);
		}
	}
	else
	{
		return;
	}
}
/*マップ外にいるかを判定します*/
bool Enemy::OutsideMap()
{
	return this->position.x <= -this->scale.x ? true : false;
}
/*敵を生成します*/
TaskObject::SP Enemy::Create(const TASKNAME& taskname_, const ObjectType& objecttype_, const Vec2& position_, const Point& scale_, const float& order_, const bool flag)
{
	Enemy::SP enemy = Enemy::SP(new Enemy());
	if (enemy)
	{
		enemy->me = enemy;
		if (!enemy->Init_Parameter(taskname_, objecttype_, position_, scale_, order_))
		{
			enemy->Kill();
		}
		if (flag)
		{
			taskSystem->Add(enemy);
		}
		return enemy;
	}
	return nullptr;
}

//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★

/*ゴブリンの設定を行います*/
void Enemy::Goburin_Parameter()
{
	//テクスチャの貼り付け
	this->draw = DrawInterFace::Addcomponent(RectF(this->position, this->scale), Rect(0, 0, 64, 64));
	this->draw->setTexture(rm->getTexture("ゴブリン"));

	//当たり判定の設定
	this->collider = Collider::Addcomponent(Collider::ShapeHitType::Cube, this->position, this->scale);

	//初期移動量の設定
	this->move = MoveInterFace::Addcomponent(Point(3, 0));
}

//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
