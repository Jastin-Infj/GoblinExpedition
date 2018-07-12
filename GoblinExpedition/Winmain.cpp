﻿# include <Siv3D.hpp>

/*メモリリーク検知をする*/
#if (_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include <iostream>
#include <string>

#include "src\TaskSystem\TaskObject.h"
#include "src\TaskSystem\TaskSystem.h"
#include "src\Task\SceceTask.h"

TaskSystem* taskSystem;



void Main()
{
	/*メモリリークの検知*/
#if(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/*コンソール画面を立ち上げる*/
	s3d::Console::Open();
#endif

	taskSystem = new TaskSystem();

	/*初期時にタスクを生成します*/
	TaskStartCreate();
	/*ライブラリによる初期化を行います*/
	Init();

	/*ウィンドウを表示させる*/
	while (System::Update())
	{
		taskSystem->UpDate();
	}

#if(_DEBUG)
	/*コンソール画面を閉じる*/
	s3d::Console::Close();
#endif

	delete taskSystem;
	taskSystem = nullptr;

	/*ウィンドウを閉じる*/
	System::Exit();
}
