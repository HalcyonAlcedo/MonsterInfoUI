#pragma once
#include <map>
#include "MonsterBuff.h"
#include "PlayerBuff.h"

using namespace std;
using namespace loader;

namespace Base {
	//常用结构
	struct Vector3 {
		float x, y, z;
		Vector3(float x = 0, float y = 0, float z = 0) :x(x), y(y), z(z) {
		};
	};
	struct Vector2 {
		float x, y;
		Vector2(float x = 0, float y = 0) :x(x), y(y) {
		};
	};
#pragma region ModConfig
	namespace ModConfig {
		//内置参数
		bool GameDataInit = false;
		bool InitErrInfo = true;
		int InitErrCount = 0;
		vector<string> LuaFiles;
		bool ModConsole = false;
		//可设置参数
		string ModName = "MonsterInfoUI";
		string ModAuthor = "Alcedo";
		string ModVersion = "v1.0.1";
		long long ModBuild = 100002103111806;
		string Version = "421470";
	}
#pragma endregion
	//游戏基础地址
#pragma region BasicGameData
	//游戏基址数据
	namespace BasicGameData {
		void* PlayerPlot = nullptr;
		void* PlayerDataPlot = nullptr;
		void* MapPlot = nullptr;
	}
#pragma endregion
	//世界信息
#pragma region World
	namespace World {
		int MapId = 0;
	}
#pragma endregion
	//计算
#pragma region Calculation
	namespace Calculation {
		Vector3 GetVector(Vector3 p1, Vector3 p2, float l) {
			float a = (p2.x - p1.x);
			float b = (p2.y - p1.y);
			float c = (p2.z - p1.z);
			l = l * l / (a * a + b * b + c * c);
			float k = sqrt(l);
			float newx1 = k * a + p1.x;
			float newy1 = k * b + p1.y;
			float newz1 = k * c + p1.z;
			return Vector3(newx1, newy1, newz1);
		}
		Vector2 GetExtensionVector2D(Vector2 Coordinate,float r, float angle) {
			float x, y;
			x = Coordinate.x + r * cos((4 * atan(1.0) / 180 * angle));
			y = Coordinate.y + r * sin((4 * atan(1.0) / 180 * angle));
			return Vector2(x, y);
		}
		float myRander(float min, float max)
		{
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_real_distribution<float> dist(min, max);
			return dist(eng);
		}
		float DistanceBetweenTwoCoordinates(Vector3 point1, Vector3 point2) {
			float RangeDistance = sqrt((point1.x - point2.x) * (point1.x - point2.x)) + sqrt((point1.z - point2.z) * (point1.z - point2.z));
			RangeDistance = sqrt((RangeDistance * RangeDistance) + sqrt((point1.y - point2.y) * (point1.y - point2.y)));
			return RangeDistance;
		}
	}
#pragma endregion
	//图形绘制
#pragma region Draw
	namespace Draw {
#pragma region imgui
		string GameInitInfo = u8"信息显示系统初始化";
#pragma endregion
	}
#pragma endregion
	//怪物信息
#pragma region Monster
	namespace Monster {
		struct MonsterData {
			void* Plot;
			float CoordinatesX;
			float CoordinatesY;
			float CoordinatesZ;
			int Id;
			int SubId;
			MonsterData(
				void* Plot = nullptr,
				float CoordinatesX = 0,
				float CoordinatesY = 0,
				float CoordinatesZ = 0,
				int Id = 0,
				int SubId = 0) 
				:Plot(Plot), CoordinatesX(CoordinatesX), CoordinatesY(CoordinatesY), CoordinatesZ(CoordinatesZ), Id(Id), SubId(SubId){
			};
		};
		//怪物列表
		map<void*, MonsterData> Monsters;
		//怪物筛选器
		pair<int, int> Filter(255,255);
		//给怪物设置buff
		static void SetBuff(void* monster,string buff){
			MonsterBuff::MonsterBuffState monsterBuff = MonsterBuff::GetMonsterBuffState(monster,buff);
			if (monsterBuff.MaxStateValue != 0) {
				MonsterBuff::SetMonsterBuffState(monster, buff);
			}
		}//获取怪物buff状态
		static MonsterBuff::MonsterBuffState GetBuff(void* monster, string buff) {
			return MonsterBuff::GetMonsterBuffState(monster, buff);
		}
	}
#pragma endregion
	//玩家信息
#pragma region PlayerData
	namespace PlayerData {
		//当前血量
		float CurrentHealth = 0;
		//基础血量（0-150）
		float BasicHealth = 0;
		//血量上限
		float MaxHealth = 0;
		//当前耐力
		float CurrentEndurance = 0;
		//耐力上限（25-150）
		float MaxEndurance = 0;
		//最后一次击中的怪物地址
		void* AttackMonsterPlot = nullptr;
		//获取玩家Buff持续时间
		static float GetPlayerBuff(string buff) {
			void* BuffsPlot = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x7D20);
			int buffPtr = PlayerBuff::GetBuffPtr(buff);
			return *offsetPtr<float>(BuffsPlot, buffPtr);
		}
		//设置玩家Buff持续时间
		static void SetPlayerBuff(string buff, float duration) {
			void* BuffsPlot = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x7D20);
			int buffPtr = PlayerBuff::GetBuffPtr(buff);
			*offsetPtr<float>(BuffsPlot, buffPtr) = duration;
		}
		//玩家数据更新
		static void Updata() {
			BasicHealth = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x7628);
			void* StatusManagementPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x7630);
			if (StatusManagementPlot != nullptr) {
				CurrentHealth = *offsetPtr<float>(StatusManagementPlot, 0x64);
				MaxHealth = *offsetPtr<float>(StatusManagementPlot, 0x60);
				CurrentEndurance = *offsetPtr<float>(StatusManagementPlot, 0x13C);
				MaxEndurance = *offsetPtr<float>(StatusManagementPlot, 0x144);
			}
			else {
				CurrentHealth = 0;
				MaxHealth = 0;
				CurrentEndurance = 0;
				MaxEndurance = 0;
			}
			if (BasicGameData::PlayerDataPlot != nullptr) {
				AttackMonsterPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerDataPlot, 0x4298);
			}
		}
	}
#pragma endregion
	//初始化
	static bool Init() {
		if (ModConfig::GameDataInit) 
			return true;
		else
		{
			Draw::GameInitInfo += u8"\n 初始化数据指针";
			void* PlayerPlot = *(undefined**)MH::Player::PlayerBasePlot;
			BasicGameData::PlayerPlot = *offsetPtr<undefined**>((undefined(*)())PlayerPlot, 0x50);
			BasicGameData::MapPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x7D20);
			void* PlayerDataOffset1 = *offsetPtr<undefined**>((undefined(*)())PlayerPlot, 0x50);
			void* PlayerDataOffset2 = nullptr;
			if (PlayerDataOffset1 != nullptr)
				PlayerDataOffset2 = *offsetPtr<undefined**>((undefined(*)())PlayerDataOffset1, 0x4c0);
			void* PlayerDataOffset3 = nullptr;
			if (PlayerDataOffset2 != nullptr)
				PlayerDataOffset3 = *offsetPtr<undefined**>((undefined(*)())PlayerDataOffset2, 0x98);
			if (PlayerDataOffset3 != nullptr)
				BasicGameData::PlayerDataPlot = *offsetPtr<undefined**>((undefined(*)())PlayerDataOffset3, 0x48);
			Draw::GameInitInfo += u8"\n 载入汇编数据";
			if (
				BasicGameData::PlayerPlot != nullptr and
				BasicGameData::MapPlot != nullptr
				) {
				//钩入数据
				MH_Initialize();
				//怪物地址获取
				HookLambda(MH::Monster::ctor,
					[](auto monster, auto id, auto subId) {
						auto ret = original(monster, id, subId);
						Base::Monster::Monsters[monster] = Base::Monster::MonsterData(
							monster, 0, 0, 0, id, subId
						);
						return ret;
					});
				HookLambda(MH::Monster::dtor,
					[](auto monster) {
						Base::Monster::Monsters.erase(monster);
						return original(monster);
					});
				Draw::GameInitInfo += u8"\n 怪物模块加载";
				MH_ApplyQueued();
				ModConfig::GameDataInit = true;
				LOG(INFO) << ModConfig::ModName << " : Game data initialization complete!";
				LOG(INFO) << " |  Mod：" << ModConfig::ModName;
				LOG(INFO) << " |  Author：" << ModConfig::ModAuthor;
				LOG(INFO) << " |  Version：" << ModConfig::ModVersion;
				Draw::GameInitInfo += u8"\n 系统初始化完成";
				//Draw::GameInit = true;
				return true;
			}
			else {
				if (ModConfig::InitErrInfo) {
					LOG(ERR) << ModConfig::ModName << " : Game data initialization failed!";
					LOG(ERR) << "The following address failed to complete the initialization. We will try again later. If the address is still not initialized successfully, please contact the mod author for solution.";
					if (BasicGameData::PlayerPlot == nullptr)
						LOG(ERR) << " |  PlayerPlot";
					if (BasicGameData::PlayerDataPlot == nullptr)
						LOG(ERR) << " |  PlayerDataPlot";
					if (BasicGameData::MapPlot == nullptr)
						LOG(ERR) << " |  MapPlot";
					ModConfig::InitErrCount++;
					if (ModConfig::InitErrCount > 10)
						ModConfig::InitErrInfo = false;
				}
				return false;
			}
		}
	}
	//实时更新的数据
	static void RealTimeUpdate() {
		if (ModConfig::GameDataInit) {
			//实时更新地图地址信息
			BasicGameData::MapPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x7D20);
			//写入地图信息和清除数据
			if (World::MapId != *offsetPtr<int>(BasicGameData::MapPlot, 0xB88)) {
				World::MapId = *offsetPtr<int>(BasicGameData::MapPlot, 0xB88);
				//清理怪物筛选器
				Monster::Filter = pair<int, int>(255, 255);
				//更新地址信息
				void* PlayerPlot = *(undefined**)MH::Player::PlayerBasePlot;
				BasicGameData::PlayerPlot = *offsetPtr<undefined**>((undefined(*)())PlayerPlot, 0x50);
			}
			//更新玩家数据
			PlayerData::Updata();
			//更新怪物信息
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
				if (monster != nullptr) {
					Base::Monster::Monsters[monster].CoordinatesX = *offsetPtr<float>(monster, 0x160);
					Base::Monster::Monsters[monster].CoordinatesY = *offsetPtr<float>(monster, 0x164);
					Base::Monster::Monsters[monster].CoordinatesZ = *offsetPtr<float>(monster, 0x168);
				}
			}
		}
	}
}