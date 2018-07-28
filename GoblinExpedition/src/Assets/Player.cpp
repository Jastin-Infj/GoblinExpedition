#include "Player.h"
#include <iostream>

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
	this->draw = DrawInterFace::Addcomponent(RectF(this->position,this->scale));
	return true;
}
/*解放処理*/
bool Player::Finalize()
{
	return true;
}
/*更新処理*/
void Player::UpDate()
{
	
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
	if (this->isLifeZero())
	{
		this->life = this->LifeMin();
	}
	this->life = life_;
}
/*ライフ値が0以下であるかを判定します*/
constexpr bool Player::isLifeZero()const
{
	return this->life <= 0 ? true : false;
}
/*ライフの最小値を返します*/
const int Player::LifeMin()
{
	return PLAYER_LIFE_MIN;
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