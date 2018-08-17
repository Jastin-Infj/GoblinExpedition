#include "Enemy.h"
#include "Score.h"
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

	this->se_frametime = ENEMY_SE_INITCOUNT;
	auto enemys = taskSystem->GetTasks_TaskName<Enemy>("ゴブリン");
	if (enemys)
	{
		this->se_frametimeMax = (int)enemys->size() * ENEMY_SE_INTERVAL;
	}
	else
	{
		this->se_frametimeMax = ENEMY_SE_INITCOUNT;
	}

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
		this->collider->sethitbace(this->position, this->scale);
	}
	else
	{
		this->move->setMovespeed(Point(ENEMY_MOVE_SPEED_X, 0));
		this->collider->sethitbace(this->position, this->scale);
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
	double opa = this->opaque;
	opa *= OPAQUE_DECREASERATE;
	//例外処理 割合計算で計算したほうが高い場合
	if (opa >= this->opaque)
	{
		this->opaque = OPAQUE_MIN;
	}
	else
	{
		this->opaque = (int)opa;
	}
	if (this->isOpaque_Zero())
	{
		this->opaque = OPAQUE_MIN;
	}
}
/*不透明度を0以下であるかを判定します*/
bool Enemy::isOpaque_Zero()const
{
	return this->opaque == OPAQUE_MIN ? true : false;
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
	auto player = taskSystem->GetTask_TaskName<Player>("自キャラ");
	if (player)
	{
		if (this->onHitbaceExit(player->getRecthitbace()) && !this->getleftrightinversionflag() && !this->isOpaque_Zero())
		{
			/*反転フラグをtrueにする*/
			this->setleftrightinversionflag(true);
			player->Receive_Enemy();
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
	return this->collider->gethitbaceRect();
}
/*スコアを返します*/
const int Enemy::getScore()
{
	return ENEMY_SCORE;
}
/*数字の桁数を計算します*/
const size_t Enemy::Digit(const int& score_)
{
	std::string str = std::to_string(score_);
	return str.size();
}
/*マウスと敵の当たり判定を行います*/
void Enemy::Mouse_Hit()
{
	auto player = taskSystem->GetTask_TaskName<Player>("自キャラ");
	if(player)
	{
		//マウス処理
		if (player->MouseHit_toEnemy(this->getRecthitbace()))
		{
			this->SE_Play();
			this->mouse_hitflag = true;
		}
		/*左クリックが押された後の処理*/
		if (this->mouse_hitflag && !this->isOpaque_Zero())
		{
			this->Opaque_Decrement();
		}
		if (this->isOpaque_Zero() && !this->getleftrightinversionflag() && !this->musouitemkill)
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
				//スコアの生成
				this->KillScoreCreate();
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
void Enemy::SE_Play_frame()
{
	if (!this->se_play)
	{
		this->se_frametime++;
		if (this->se_frametime >= this->se_frametimeMax)
		{
			this->se.play();
			this->se_play = true;
		}
		std::cout << this->se_frametime << std::endl;
	}
}
/*自身が倒された際にスコアを表示するUIを生成します*/
void Enemy::KillScoreCreate()
{
	size_t scoresize = this->Digit(this->getScore());
	for (size_t i = 0; i < scoresize; ++i)
	{
		auto scorecreate = Score::Create(TASKNAME("EffectUI", "スコアエフェクト"), Score::ObjectType::KillEnemy, Vec2(this->position.x + (64 * i), this->position.y - this->scale.y), Point(64, 48), (int)i + 1, this->getScore());
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
	this->collider = Collider::Addcomponent(Collider::ShapeT::RectF,this->position, this->scale);

	//初期移動量の設定
	this->move = MoveInterFace::Addcomponent(Point(ENEMY_MOVE_SPEED_X, ENEMY_MOVE_SPEED_Y));
}

//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
