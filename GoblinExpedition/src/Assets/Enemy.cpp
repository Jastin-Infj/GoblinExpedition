#include "Enemy.h"
#include <iostream>
#include "../Task/Task_Game.h"
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
	this->opaque = OPAQUE_INIT;
	this->mouse_hitflag = false;
	this->musouitemkill = false;
	this->se = rm->getSound("敵消滅SE");
	this->se_play = false;
	this->se_frametime = SE_INITCOUNT;
	//追加の初期化項目
	void(Enemy::*Func[OBJECT_TYPESIZE])() = { &Enemy::Goburin_Parameter , nullptr};
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
void Enemy::Update()
{
	if (this->getleftrightinversionflag())
	{
		this->move->setMovespeed(Point(-ENEMY_MOVE_SPEED_X, 0));
		this->collider->setHitBace(this->position, this->scale);
	}
	else
	{
		this->move->setMovespeed(Point(ENEMY_MOVE_SPEED_X, 0));
		this->collider->setHitBace(this->position, this->scale);
	}
	this->move->UniformLinearMotion(this->position);
	
	/*反転判定を行います*/
	this->LeftRightInversion();
	/*マウス判定を行います*/
	this->Mouse_Hit();
	/*マップ外判定を行います*/
	if (this->OutsideMap() && this->getleftrightinversionflag())
	{
		this->Kill();
	}
}
/*描画をします*/
void Enemy::Render()
{
	/*描画矩形の更新*/
	this->draw->setDrawBace(this->position, this->scale);

	if (this->getleftrightinversionflag())
	{
		this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace(),Color(255,255,255, (uint32)this->opaque) ,true);
	}
	else
	{
		this->draw->TextureDraw(this->draw->getDrawBace(), this->draw->getSrcBace(),Color(255,255,255,(uint32)this->opaque));
	}
}
/*不透明を割合計算で透過させます*/
void Enemy::Opaque_Decrement()
{
	if (this->isOpaque_Zero())
	{
		return;
	}
	this->opaque *= OPAQUE_DECREASERATE;
	if (this->opaque <= OPAQUE_MIN)
	{
		this->opaque = OPAQUE_MIN;
	}
	std::cout << this->opaque << std::endl;
}
/*不透明度を0であるかを判定します*/
bool Enemy::isOpaque_Zero()const
{
	return (int)this->opaque == OPAQUE_MIN ? true : false;
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
		if (this->onHitbaceExit(temp->getHitBace()) && !this->getleftrightinversionflag() && !this->isOpaque_Zero())
		{
			/*反転フラグをtrueにする*/
			this->setleftrightinversionflag(true);
			temp->Receive_Enemy();
		}
	}
}
/*マップ外にいるかを判定します*/
bool Enemy::OutsideMap()
{
	return this->position.x <= -this->scale.x ? true : false;
}
/*当たり判定矩形を返します*/
RectF Enemy::getHitBace()const
{
	return this->collider->getHitBace();
}
/*スコアを返します*/
const int Enemy::getScore()
{
	return ENEMY_SCORE;
}
/*マウスと敵の当たり判定を行います*/
void Enemy::Mouse_Hit()
{
	Player::WP player = taskSystem->GetTask_TaskName<Player>("自キャラ");
	if (!player.expired())
	{
		auto temp = player.lock();
		//マウス処理
		if (temp->MouseHit(this->collider->getHitBace()))
		{
			if (this->collider->MouseLeftPressed())
			{
				this->SE_Play();
				this->mouse_hitflag = true;
			}	
		}
		/*左クリックが押された後の処理*/
		if (this->mouse_hitflag && !this->isOpaque_Zero())
		{
			this->Opaque_Decrement();
		}
		else if (this->isOpaque_Zero() && !this->getleftrightinversionflag() && !this->musouitemkill)
		{
			auto game = taskSystem->GetTask_TaskName<Game>("インゲーム");
			if (game)
			{
				//スコアを加算する
				game->ScoreAddition(ENEMY_SCORE);
				//撃破数を加算する
				game->Enemy_DestroyingCount_Add(ENEMY_DESTROYINGSCORE);
				//撃破アイテムの生成
				game->MusouItem_Create();
				this->Kill();
			}
		}
	}
}
/*無双アイテムフラグを設定・変更します*/
void Enemy::setMusouitemkill(const bool flag)
{
	this->musouitemkill = flag;
}
/*無双アイテムフラグを返します*/
bool Enemy::getMusouitemkill()const
{
	return this->musouitemkill;
}
/*消滅SEを流します*/
void Enemy::SE_Play()
{
	if (!this->se_play)
	{
		this->se_play = true;
		this->se.play();
	}
}
/*消滅SEを流します*/
void Enemy::SE_Play(const int& frametime)
{
	if (!this->se_play)
	{
		this->se_play = true;
		this->se_frametime++;
		if (this->se_frametime >= frametime)
		{
			this->SE_Play();
		}
	}
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
	this->move = MoveInterFace::Addcomponent(Point(ENEMY_MOVE_SPEED_X, ENEMY_MOVE_SPEED_Y));
}

//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
