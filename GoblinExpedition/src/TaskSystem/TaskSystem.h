#pragma once

/// <summary>
/// @file  TaskSystem.h
/// @brief オブジェクトの生成削除を簡潔に行えるシステム
/// </summary>


#include <iostream>
#include <vector>
#include <memory>

#include "TaskObject.h"


/// <summary>
/// 
/// </summary>
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


	///<summary>
	///タスクシステムの更新処理
	///</summary>
	void Update();


	/// <summary>
	/// オブジェクトをタスクシステムに登録します
	/// </summary>
	/// <param name="createobject">
	/// @param [name] 登録したいオブジェクト
	/// </param>
	void Add(const TaskObject::SP& createobject);


	///<summary>
	///描画順位を設定します
	///</summary>
	void setOrder();


	///<summary>
	///登録しているオブジェクトのタスク名を表示します
	///</summary>
	void TasknameOutput()const;


	///<summary>
	///登録されているオブジェクトを全部消去を行います
	///</summary>
	void TaskObjectDelete();


	/// <summary>
	/// タスク名・グループ名を検索して、オブジェクト単体を取得します
	/// </summary>
	/// <param name="taskname_">
	/// @param[name]検索ワード
	/// </param>
	/// <returns>
	/// 検索ワードと一致したスマートポインタ
	/// </returns>
	template <class T>
	std::shared_ptr<T> GetTask(const std::pair<std::string, std::string>& taskname_)
	{
		for (auto it = this->taskobjects.begin(); it != this->taskobjects.end(); ++it)
		{
			if ((*it).second != nullptr)
			{
				if ((*it).second->getTaskname() == taskname_)
				{
					std::weak_ptr<T> temp = std::static_pointer_cast<T>((*it).second);
					return temp.lock();
				}
			}
		}
		return nullptr;
	}


	/// <summary>
	/// グループ名を検索して、オブジェクト単体を取得します
	/// </summary>
	/// <param name="groupname_">
	/// 検索するグループ名
	/// </param>
	/// <returns>
	/// グループ名が一致したスマートポインタ
	/// </returns>
	template <class T>
	std::shared_ptr<T> GetTask_GroupName(const std::string& groupname_)
	{
		for (auto it = this->taskobjects.begin(); it != this->taskobjects.end(); ++it)
		{
			if ((*it).second != nullptr)
			{
				if ((*it).second->getTaskname().first == groupname_)
				{
					std::weak_ptr<T> temp = std::static_pointer_cast<T>((*it).second);
					return temp.lock();
				}
			}
		}
		return nullptr;
	}


	/// <summary>
	/// タスク名を検索して、オブジェクト単体を取得します
	/// </summary>
	/// <param name="taskname_">
	/// 検索するタスク名
	/// </param>
	/// <returns>
	/// 一致したオブジェクトのスマートポインタ
	/// </returns>
	template <class T>
	std::shared_ptr<T> GetTask_TaskName(const std::string& taskname_)
	{
		for (auto it = this->taskobjects.begin(); it != this->taskobjects.end(); ++it)
		{
			if ((*it).second != nullptr)
			{
				if ((*it).second->getTaskname().second == taskname_)
				{
					std::weak_ptr<T> temp = std::static_pointer_cast<T>((*it).second);
					return temp.lock();
				}
			}
		}
		return nullptr;
	}


	/// <summary>
	///タスク名・グループ名を検索して、オブジェクト複数を取得します
	/// </summary>
	/// <param name="taskname_">
	/// 検索したい（グループ名・タスク名）
	/// </param>
	/// <returns>
	/// 一致したオブジェクト全体
	/// </returns>
	template<class T>
	std::shared_ptr<std::vector<std::shared_ptr<T>>> GetTasks(const std::pair<std::string, std::string>& taskname_)
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
		std::weak_ptr<std::vector<std::shared_ptr<T>>> temp = searchObjects;
		return temp.lock();
	}


	/// <summary>
	/// グループ名を検索して、オブジェクト複数を取得します
	/// </summary>
	/// <param name="groupname_">
	/// 検索したいグループ名
	/// </param>
	/// <returns>
	/// 一致したオブジェクト全体
	/// </returns>
	template<class T>
	std::shared_ptr<std::vector<std::shared_ptr<T>>> GetTasks_GroupName(const std::string& groupname_)
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
		std::weak_ptr<std::vector<std::shared_ptr<T>>> temp = searchObjects;
		return temp.lock();
	}


	/// <summary>
	/// タスク名を検索して、オブジェクト複数を取得します
	/// </summary>
	/// <param name="taskname_">
	/// 検索したいタスク名
	/// </param>
	/// <returns>
	/// 一致したオブジェクト全体
	/// </returns>
	template<class T>
	std::shared_ptr<std::vector<std::shared_ptr<T>>> GetTasks_TaskName(const std::string& taskname_)
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
		std::weak_ptr<std::vector<std::shared_ptr<T>>> temp = searchObjects;
		return temp.lock();
	}

	/// <summary>
	/// アプリケーションを閉じます
	/// </summary>
	void Application_Exit()const;

private:
	///<summary>
	///登録しているオブジェクト
	///</summary>
	std::vector<std::pair<std::pair<std::string, std::string>, TaskObject::SP>> taskobjects;


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
	void TaskApplication();


	///<summary>
	///登録されているオブジェクトの更新処理を行います
	///</summary>
	void T_UpDate();


	///<summary>
	///登録されているオブジェクトの描画処理を行います
	///</summary>
	void T_Render();


	///<summary>
	///登録されているオブジェクトの消去を行います
	///</summary>
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
extern TaskSystem* taskSystem;		//タスクシステムにアクセス用変数