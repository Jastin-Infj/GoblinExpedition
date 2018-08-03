#include <iostream>
#include <string>
#include "TaskObject.h"

/*コンストラクタ*/
KillTaskSystem::KillTaskSystem()
{
	this->killcount = 0;
}
KillTaskSystem::~KillTaskSystem(){}
/*消滅をさせることを依頼します*/
void KillTaskSystem::KillCount()
{
	this->killcount++;
}
/*消滅させるかどうかを判定します*/
bool KillTaskSystem::KillCheck()
{
	return this->killcount > 0 ? true : false;
}
/*キルカウンターを返します*/
int  KillTaskSystem::getKillcount()const
{
	return this->killcount;
}

/*コンストラクタ*/
TaskObject::TaskObject()
{
	this->setNextTask(true);
	this->setPause(false);

	std::cout << "TaskObject()" << std::endl;
}
/*デストラクタ*/
TaskObject::~TaskObject()
{
	std::cout << this->getTaskname().second <<"~TaskObject()" << std::endl;
}
/*タスク名返します*/
std::pair<std::string,std::string> TaskObject::getTaskname()const
{
	return this->taskname;
}
/*更新処理を行います*/
void TaskObject::Update()
{
	std::cout << this->taskname.second << "update()" << std::endl;
}
/*描画処理を行います*/
void TaskObject::Render()
{
	std::cout << this->taskname.second << "render()" << std::endl;
}
/*解放処理を行います*/
bool TaskObject::Finalize()
{
	std::cout << this->taskname.second << "finalize()" << std::endl;
	return true;
}
/*オブジェクトを消去します*/
void TaskObject::Kill()
{
	this->KillCount();
}
/*killのカウンタを返します*/
int  TaskObject::getKillCounter()const
{
	return this->getKillcount();
}
/*次回のタスクが生成できるかを返します*/
bool TaskObject::getNextTask()const
{
	return this->NextTask;
}
/*グループ名・タスク名をセットします */
void TaskObject::setTaskName(const std::pair<std::string, std::string>& taskname_)
{
	this->taskname = taskname_;
}
/*次回生成出来るフラグを設定します*/
void TaskObject::setNextTask(const bool flag)
{
	this->NextTask = flag;
}
/*ポーズ設定を行います*/
void TaskObject::setPause(const bool flag)
{
	this->isPause = flag;
}
/*ポーズフラグを返します*/
bool TaskObject::getisPause()const
{
	return this->isPause;
}
/*描画優先順位を設定します*/
void TaskObject::setDrawOrder(float order_)
{
	this->order = order_;
}
/*描画優先順位を返します*/
const float TaskObject::getDrawOrder()const
{
	return this->order;
}
/*オブジェクト生成時にタスク名を設定します*/
bool TaskObject::CreatedObjectInit(const std::pair<std::string, std::string>& taskname_)
{
	//空白の名前がある場合
	if (taskname_.first == "" || taskname_.second == "")
	{
		return false;
	}
	this->setTaskName(taskname_);
	this->setDrawOrder(1.0f);
	return true;
}
/*タスク名が検索ワードと一致しているかを返します*/
bool TaskObject::isTasknameSecond(const std::string& taskname_)const
{
	return this->taskname.second == taskname_ ? true : false;
}