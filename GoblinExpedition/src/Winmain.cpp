# include <Siv3D.hpp>

/*メモリリーク検知をする*/
#if (_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include <iostream>
#include <string>

#include "TaskSystem\TaskObject.h"
#include "TaskSystem\TaskSystem.h"
#include "Task\SceceTask.h"
#include "ResourceManager/ResourceManager.h"

TaskSystem* taskSystem;
ResourceManager* rm;


void Main()
{
	/*メモリリークの検知*/
#if(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/*コンソール画面を立ち上げる*/
	s3d::Console::Open();
#endif

	taskSystem = new TaskSystem();
	rm = new ResourceManager();

	Window::SetBaseSize(640, 480);

	/*初期時にタスクを生成します*/
	TaskStartCreate();
	/*ライブラリによる初期化を行います*/
	Init();

	/*ウィンドウを表示させる*/
	while (System::Update())
	{
		taskSystem->Update();
	}

#if(_DEBUG)
	/*コンソール画面を閉じる*/
	s3d::Console::Close();
#endif
	delete taskSystem;
	delete rm;
	taskSystem = nullptr;
	rm = nullptr;

	/*ウィンドウを閉じる*/
	System::Exit();
}
