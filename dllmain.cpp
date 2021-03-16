// dllmain.cpp
#include <fstream>
#include <queue>
#include <functional>

#include <random>
#include <iostream>
#include <cmath>

#include <windows.h>

#include "minhook/MinHook.h"
#include "json/json.hpp"
#include "loader.h"
#include "ghidra_export.h"
#include "util.h"
#include <thread>

#include "dxhook/globals.h"
#include "Base.h"
#include "ControlProgram.h"

using namespace loader;
//初始化Dx钩子
unsigned long __stdcall MainThread()
{
	ControlProgram::Init();
	return 0;
}
__declspec(dllexport) extern bool Load()
{
	//游戏版本检查
	if (std::string(GameVersion) != Base::ModConfig::Version) {
		LOG(WARN) << Base::ModConfig::ModName << " : Wrong version";
		return false;
	}

	//初始化钩子
	MH_Initialize();
	HookLambda(MH::World::MapClockLocal,
		[](auto clock, auto clock2) {
			auto ret = original(clock, clock2);
			//初始化系统数据
			if (Base::Init()) {
				Base::RealTimeUpdate();
			}
			//初始化图形
			if (!Base::Draw::GameInit) {
				Base::Draw::GameInit = true;
				globals::mainWindow = (HWND)FindWindow("MT FRAMEWORK", NULL);
				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, globals::mainModule, 0, 0);
			}
			return ret;
		});
	//应用钩子
	MH_ApplyQueued();
	return true;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		globals::mainModule = hModule;
		return Load();
	}
	return TRUE;
}

