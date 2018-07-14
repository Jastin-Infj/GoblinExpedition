#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "TaskObject.h"

///<summary>
///
///</summary>
///<returns>
///
///</returns>

class TaskSystem
{
public:
	typedef std::shared_ptr<TaskSystem> SP;


	///<summary>
	///コンストラクタ
	///</summary>
	TaskSystem();

	
	///<summary>
	///デストラクタ
	///</summary>
	~TaskSystem();

	
	///タスクシステムの更新処理
	///</summary>
	///<returns>
	///なし
	///</returns>
	void UpDate();


	///<summary>
	///オブジェクトをシステムに仮登録します
	///</summary>
	///<returns>
	///なし
	///</returns>
	void Add(const TaskObject::SP&);


	///<summary>
	///描画順位を設定します
	///</summary>
	void setOrder();


	///<summary>
	///登録しているオブジェクトのタスク名を表示します
	///</summary>
	///<returns>
	///なし
	///</returns>
	void TasknameOutput()const;


	///<summary>
	///登録されているオブジェクトを全部消去を行います
	///</summary>
	///<returns>
	///なし
	///</returns>
	void TaskObjectDelete();
	

	///<summary>
	///タスク名・グループ名を検索して、オブジェクト単体を取得します
	///</summary>
	template <class T>
	std::shared_ptr<T> GetTask(std::pair<std::string, std::string>& taskname_)
	{
		for (auto it = this->taskobjects.begin(); it != this->taskobjects.end(); ++it)
		{
			if ((*it).second != nullptr)
			{
				if ((*it).second->getTaskname() == taskname_)
				{
					return std::static_pointer_cast<T>((*it).second);
				}
			}
		}
		return nullptr;
	}


	///<summary>
	///グループ名を検索して、オブジェクト単体を取得します
	///</summary>
	template <class T>
	std::shared_ptr<T> GetTask_GroupName(std::string& groupname_)
	{
		for (auto it = this->taskobjects.begin(); it != this->taskobjects.end(); ++it)
		{
			if ((*it).second != nullptr)
			{
				if ((*it).second->getTaskname().first == groupname_)
				{
					return std::static_pointer_cast<T>((*it).second);
				}
			}
		}
		return nullptr;
	}



	///<summary>
	///タスク名を検索して、オブジェクト単体を取得します
	///</summary>
	template <class T>
	std::shared_ptr<T> GetTask_TaskName(std::string& taskname_)
	{
		for (auto it = this->taskobjects.begin(); it != this->taskobjects.end(); ++it)
		{
			if ((*it).second != nullptr)
			{
				if ((*it).second->getTaskname().second == taskname_)
				{
					return std::static_pointer_cast<T>((*it).second);
				}
			}
		}
		return nullptr;
	}


	///<summary>
	///タスク名・グループ名を検索して、オブジェクト複数を取得します
	///</summary>
	template<class T>
	std::shared_ptr<std::vector<std::shared_ptr<T>>> GetTasks(std::pair<std::string, std::string>& taskname_)
	{
		std::shared_ptr<std::vector<std::shared_ptr<T>>> searchObjects = std::shared_ptr<std::vector<std::shared_ptr<T>>>(new std::vector<std::shared_ptr<T>>());
		for (auto it = this->taskobjects.begin(); it != this->taskobjects.end(); ++it)
		{
			if ((*it).second != nullptr)
			{
				if ((*it).second->getTaskname() == taskname_)
				{
					searchObjects->push_back(std::static_pointer_cast<T>((*it).second));
				}
			}
		}
		return searchObjects;
	}


	///<summary>
	///グループ名を検索して、オブジェクト複数を取得します
	///</summary>
	template<class T>
	std::shared_ptr<std::vector<std::shared_ptr<T>>> GetTasks_GroupName(std::string& groupname_)
	{
		std::shared_ptr<std::vector<std::shared_ptr<T>>> searchObjects = std::shared_ptr<std::vector<std::shared_ptr<T>>>(new std::vector<std::shared_ptr<T>>());
		for (auto it = this->taskobjects.begin(); it != this->taskobjects.end(); ++it)
		{
			if ((*it).second != nullptr)
			{
				if ((*it).second->getTaskname().first == groupname_)
				{
					searchObjects->push_back(std::static_pointer_cast<T>((*it).second));
				}
			}
		}
		return searchObjects;
	}

	///<summary>
	///タスク名を検索して、オブジェクト複数を取得します
	///</summary>
	template<class T>
	std::shared_ptr<std::vector<std::shared_ptr<T>>> GetTasks_TaskName(std::string& taskname_)
	{
		std::shared_ptr<std::vector<std::shared_ptr<T>>> searchObjects = std::shared_ptr<std::vector<std::shared_ptr<T>>>(new std::vector<std::shared_ptr<T>>());
		for (auto it = this->taskobjects.begin(); it != this->taskobjects.end(); ++it)
		{
			if ((*it).second != nullptr)
			{
				if ((*it).second->getTaskname().second == taskname_)
				{
					searchObjects->push_back(std::static_pointer_cast<T>((*it).second));
				}
			}
		}
		return searchObjects;
	}


private:
	///<summary>
	///登録しているオブジェクト
	///</summary>
	std::vector<std::pair<std::pair<std::string,std::string>,TaskObject::SP>> taskobjects;


	///<summary>
	///登録予定のオブジェクト
	///</summary>
	std::vector<std::pair<std::pair<std::string, std::string>, TaskObject::SP>> addobjects;


	///<summary>
	///描画順優先順位
	///</summary>
	std::vector<DrawOrder> orders;


	///<summary>
	///登録予定のオブジェクトを登録します
	///<summary>
	///<returns>
	///なし
	///</returns>
	void TaskApplication();


	///<summary>
	///登録されているオブジェクトの更新処理を行います
	///</summary>
	///<returns>
	///なし
	///</returns>
	void T_UpDate();


	///<summary>
	///登録されているオブジェクトの描画処理を行います
	///</summary>
	///<returns>
	///なし
	///</returns>
	void T_Render();


	///<summary>
	///登録されているオブジェクトの消去を行います
	///</summary>
	///<returns>
	///なし
	///</returns>
	void T_Destory();


	///<summary>
	///登録予定のオブジェクトが存在するかを判定します
	///</summary>
	///<returns>
	///存在する true 存在しない false
	///</returns>
	bool AddObjectCheck()const;

	
	///<summary>
	///登録オブジェクトから消去予定のオブジェクトがないかを判定します
	///</summary>
	///<returns>
	///存在する true 存在しない false
	///</returns>
	bool CheckKillTask()const;


};
extern TaskSystem* taskSystem;