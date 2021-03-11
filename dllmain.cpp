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

#include "Base.h"
#include "ControlProgram.h"
using namespace loader;

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
			ControlProgram::InitConsole();
			if (Base::Init()) {
				Base::RealTimeUpdate();
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
		DisableThreadLibraryCalls(hModule);
		ControlProgram::hMod = hModule;
		return Load();
	}
	return TRUE;
}

