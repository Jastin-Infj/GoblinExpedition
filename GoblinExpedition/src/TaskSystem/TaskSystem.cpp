#include "TaskSystem.h"
#include <iostream>
#include <string>

/*コンストラクタ*/
TaskSystem::TaskSystem()
{
	std::cout << "TaskSystem" << std::endl;
}
/*デストラクタ*/
TaskSystem::~TaskSystem()
{
	this->TaskObjectDelete();
	std::cout << "~TaskSystem" << std::endl;
}
/*タスクシステムの更新処理*/
void TaskSystem::UpDate()
{
	this->T_UpDate();
	this->T_Render();
	if (this->AddObjectCheck() || this->CheckKillTask())
	{
		/*登録予定のタスクを登録する*/
		this->TaskApplication();
		/*削除予定のタスクを削除する*/
		this->T_Destory();
	}
}
/*オブジェクトをシステムに仮登録します*/
void TaskSystem::Add(const TaskObject::SP& addobject)
{
	std::pair<std::pair<std::string, std::string>, TaskObject::SP> object;
	object.first = addobject->getTaskname();
	object.second = addobject;
	this->addobjects.push_back(object);
}
/*登録予定のオブジェクトを登録します*/
void TaskSystem::TaskApplication()
{
	for (auto it = this->addobjects.begin(); it != this->addobjects.end(); ++it)
	{
		std::pair<std::pair<std::string, std::string>, TaskObject::SP> addobject;
		addobject = (*it);

		/*次回はここから処理*/
		if (addobject.second->getNextTask())
		{
			this->taskobjects.push_back(addobject);
		}
	}
	/*登録予定したオブジェクトデータを全て消去する*/
	addobjects.clear();
}
/*登録されているオブジェクトがあるかを判定します*/
bool TaskSystem::AddObjectCheck()const
{
	return this->addobjects.size() > 0;
}
/*登録オブジェクトに消去するオブジェクトがないかを判定します*/
bool TaskSystem::CheckKillTask()const
{
	for (int i = 0; i < this->addobjects.size(); ++i)
	{
		if (this->taskobjects[i].second->getKillCounter() > 0)
		{
			return true;
		}
	}
	return false;
}
/*登録しているオブジェクトのタスク名を返します*/
void TaskSystem::TasknameOutput()const
{
	for (auto it = this->taskobjects.begin(); it != this->taskobjects.end(); ++it)
	{
		/*消去されていない場合*/
		if ((*it).second->getKillCounter() == 0 && !(*it).second->getisPause())
		{
			std::cout << (*it).second->getTaskname().second << std::endl;
		}
	}
}
/*登録しているオブジェクトの更新処理を行います*/
void TaskSystem::T_UpDate()
{
	for (auto it = this->taskobjects.begin(); it != this->taskobjects.end(); ++it)
	{
		/*消去されていない場合*/
		if ((*it).second->getKillCounter() == 0 && !(*it).second->getisPause())
		{
			(*it).second->UpDate();
		}
	}
}
/*登録しているオブジェクトの描画処理を行います*/
void TaskSystem::T_Render()
{
	for (auto it = this->taskobjects.begin(); it != this->taskobjects.end(); ++it)
	{
		/*消去されていない場合*/
		if ((*it).second->getKillCounter() == 0 && !(*it).second->getisPause())
		{
			(*it).second->Render();
		}
	}
}
/*登録しているオブジェクトの消去できるかをチェックします*/
void TaskSystem::T_Destory()
{
	auto it = this->taskobjects.begin();
	while(it != this->taskobjects.end())
	{
		if ((*it).second)
		{
			if ((*it).second->getKillCounter() > 0)
			{
				this->taskobjects.erase(it);
				/*次回予定のタスクを追加します*/
				this->TaskApplication();			
				it = this->taskobjects.begin();
			}
			else
			{
				++it;
			}
		}
		else
		{
			++it;
		}
	}
}
/*登録しているオブジェクトの全消去を行います*/
void TaskSystem::TaskObjectDelete()
{
	{
		auto it = this->taskobjects.begin();
		while (it != this->taskobjects.end())
		{
			this->taskobjects.erase(it);
			it = this->taskobjects.begin();
		}
	}
	
	{
		auto it = this->addobjects.begin();
		while (it != this->addobjects.end())
		{
			this->addobjects.erase(it);
			it = this->taskobjects.begin();
		}
	}
}