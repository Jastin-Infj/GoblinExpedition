#include "Player.h"
#include <iostream>
#include "../TaskSystem/TaskSystem.h"
#include "UI.h"

/*コンストラクタ*/
Player::Player()
{
#ifdef _DEBUG
	std::cout << "Player()" << std::endl;
#endif // _DEBUG
}
/*デストラクタ*/
Player::~Player()
{
	this->Finalize();
#ifdef _DEBUG
	std::cout << this->getTaskname().second << "~Player()" << std::endl;
#endif // _DEBUG
}
/*パラメータの初期化設定*/
bool Player::Init_Parameter(const TASKNAME& taskname_ , const Vec2& position_, const Point& scale_ ,const int& life_  ,  const float& order_)
{
	/*タスク名を設定*/
	__super::setTaskName(taskname_);
	/*描画優先順位を設定*/
	__super::setDrawOrder(this->order = order_);


	this->position = position_;
	this->scale = scale_;
	this->life = life_;

	this->LifeUICreate();

	//追加の初期化項目
	this->collider = Collider::Addcomponent(Collider::ShapeHitType::Cube, Vec2(this->position.x - this->scale.x, 0), Point(8, Window::Size().y));
	this->mouse_colider = Collider::Addcomponent(Collider::ShapeHitType::Cube, Vec2(this->mouse_cursor_position), Point(MOUSE_SCALE_W, MOUSE_SCALE_H));
	this->draw = DrawInterFace::Addcomponent(RectF(this->position,this->scale));


	return true;
}
/*解放処理*/
bool Player::Finalize()
{
	if (this->mouse_colider)
	{
		delete this->mouse_colider;
	}
	return true;
}
/*更新処理*/
void Player::Update()
{
	this->mouse_cursor_position = this->Mouse_Pos();
	/*当たり判定の更新*/
	this->mouse_colider->setHitBace(this->mouse_cursor_position, Point(MOUSE_SCALE_W, MOUSE_SCALE_H));

	//無双アイテムの使用
	auto musouitems = taskSystem->GetTasks_TaskName<UI>("無双アイテム");
	auto musouitems_it = musouitems->rbegin();

	if (musouitems)
	{
		for (auto it = musouitems->begin(); it != musouitems->end(); ++it)
		{
			if ((*it)->Hit(this->mouse_colider->getHitBace()))
			{
				if ((*it)->MouseLclicked())
				{
					if (this->mouseclickcount == 0)
					{
						(*musouitems_it)->Receive_Player();
					}
					this->mouseclickcount++;
				}
				else
				{
					mouseclickcount = 0;
				}
			}
		}
	}
}
/*描画をします*/
void Player::Render()
{
	this->draw->PaletteColorDraw(this->collider->getHitBace(),Palette::Red);
	this->draw->PaletteColorDraw(this->draw->getDrawBace(), Palette::White);
}
/*当たり判定を返します*/
RectF Player::getHitBace()const
{
	return this->collider->getHitBace();
}
/*Playerの体力値を返します*/
int Player::getLife()const
{
	return this->life;
}
/*Playerの体力値分を生成します*/
void Player::LifeUICreate()
{
	{
		rm->setTexture("プレイヤライフ", Texture(L"./data/image/heart.png"));
		for (int i = 0; i < this->life; ++i)
		{
			auto player_life = UI::Create(TASKNAME("UI", "プレイヤライフ"), UI::ObjectType::PlayerLife, Vec2(Window::Size().x - 64 - i * 64, 0), Point(64, 48));
		}
	}
}
/*Playerの体力値を変更・設定します*/
void Player::setLife(int life_)
{
	this->life = life_;
	if (this->isLifeZero())
	{
		this->life = this->LifeMin();
	}
	else if(this->isLifeMax())
	{
		this->life = this->LifeMax();
	}
}
/*ライフ値が0以下であるかを判定します*/
constexpr bool Player::isLifeZero()const
{
	return this->life < PLAYER_LIFE_MIN ? true : false;
}
/*ライフ値が上限に達しているかを判定します*/
constexpr bool Player::isLifeMax()const
{
	return this->life >= PLAYER_LIFE_MAX ? true : false;
}
/*ライフの最小値を返します*/
const int Player::LifeMin()
{
	return PLAYER_LIFE_MIN;
}
/*ライフの上限値を返します*/
const int Player::LifeMax()
{
	return PLAYER_LIFE_MAX;
}
/*ライフ値を減少させます*/
void Player::LifeDecrement()
{
	this->life -= PLAYER_LIFE_DECREMENT;
}
/*Enemyに接触したあとの処理*/
void Player::Receive_Enemy()
{
	if (this->isLifeZero())
	{
		//ゲームオーバー処理へ移行する
		this->Kill();
	}
	this->LifeDecrement();

	/*UIの消去も行う*/
	auto playerlifeui = taskSystem->GetTasks_TaskName<UI>("プレイヤライフ");
	auto it = playerlifeui->rbegin();
	if (playerlifeui)
	{
		(*it)->Kill();
	}
}
/*マウス座標を毎時更新します*/
Vec2 Player::Mouse_Pos()const
{
	return Mouse::Pos();
}
/*マウス座標を返します*/
Vec2 Player::getMousePos()const
{
	return this->mouse_cursor_position;
}
/*マウスと当たり判定を行います*/
bool Player::MouseHit(const RectF& target)const
{
	return this->mouse_colider->Hit(target);
}
/*オブジェクトを生成します*/
TaskObject::SP Player::Create(const TASKNAME& taskname, const Vec2& position, const Point& scale,const int& life_ ,const float& order, bool flag)
{
	Player::SP create = Player::SP(new Player());
	if (create)
	{
		/*ウィークポインタを持たせておく*/
		create->me = create;
		if (!create->Init_Parameter(taskname, position, scale,life_ ,order))
		{
			/*初期化が出来ない場合は消去する*/
			create->Kill();
		}
		if (flag)
		{
			taskSystem->Add(create);
		}
		return create;
	}
	return nullptr;
}