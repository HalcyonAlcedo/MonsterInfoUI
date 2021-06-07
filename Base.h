#pragma once
#include <map>
#include "MonsterBuff.h"
#include "PlayerBuff.h"

using namespace std;
using namespace loader;

namespace Base {
	//���ýṹ
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
		//���ò���
		bool GameDataInit = false;
		bool DrawInit = false;
		bool InitErrInfo = true;
		int InitErrCount = 0;
		vector<string> LuaFiles;
		bool ModConsole = false;
		//�����ò���
		string ModName = "MonsterInfoUI";
		string ModAuthor = "Alcedo";
		string ModVersion = "v1.0.2";
		long long ModBuild = 100022106071341;
		string Version = "421471";
	}
#pragma endregion
	//��Ϸ������ַ
#pragma region BasicGameData
	//��Ϸ��ַ����
	namespace BasicGameData {
		void* PlayerPlot = nullptr;
		void* PlayerDataPlot = nullptr;
		void* MapPlot = nullptr;
	}
#pragma endregion
	//������Ϣ
#pragma region World
	namespace World {
		int MapId = 0;
	}
#pragma endregion
	//����
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
	//������Ϣ
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
		//�����б�
		map<void*, MonsterData> Monsters;
		//����ɸѡ��
		pair<int, int> Filter(255,255);
		//����������buff
		static void SetBuff(void* monster,string buff){
			MonsterBuff::MonsterBuffState monsterBuff = MonsterBuff::GetMonsterBuffState(monster,buff);
			if (monsterBuff.MaxStateValue != 0) {
				MonsterBuff::SetMonsterBuffState(monster, buff);
			}
		}//��ȡ����buff״̬
		static MonsterBuff::MonsterBuffState GetBuff(void* monster, string buff) {
			return MonsterBuff::GetMonsterBuffState(monster, buff);
		}
	}
#pragma endregion
	//�����Ϣ
#pragma region PlayerData
	namespace PlayerData {
		//��ǰѪ��
		float CurrentHealth = 0;
		//����Ѫ����0-150��
		float BasicHealth = 0;
		//Ѫ������
		float MaxHealth = 0;
		//��ǰ����
		float CurrentEndurance = 0;
		//�������ޣ�25-150��
		float MaxEndurance = 0;
		//���һ�λ��еĹ����ַ
		void* AttackMonsterPlot = nullptr;
		//��ȡ���Buff����ʱ��
		static float GetPlayerBuff(string buff) {
			void* BuffsPlot = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x7D20);
			int buffPtr = PlayerBuff::GetBuffPtr(buff);
			return *offsetPtr<float>(BuffsPlot, buffPtr);
		}
		//�������Buff����ʱ��
		static void SetPlayerBuff(string buff, float duration) {
			void* BuffsPlot = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x7D20);
			int buffPtr = PlayerBuff::GetBuffPtr(buff);
			*offsetPtr<float>(BuffsPlot, buffPtr) = duration;
		}
		//������ݸ���
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
				AttackMonsterPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerDataPlot, 0x2C8);
			}
			else {
				void* PlayerDataHandlePlot = *(undefined**)MH::Player::PlayerDataHandlePlot;
				void* PlayerDataHandleOffset1 = nullptr;
				if (PlayerDataHandlePlot != nullptr)
					PlayerDataHandleOffset1 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandlePlot, 0x48);
				void* PlayerDataHandleOffset2 = nullptr;
				if (PlayerDataHandleOffset1 != nullptr)
					PlayerDataHandleOffset2 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset1, 0x58);
				void* PlayerDataHandleOffset3 = nullptr;
				if (PlayerDataHandleOffset2 != nullptr)
					PlayerDataHandleOffset3 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset2, 0x58);
				void* PlayerDataHandleOffset4 = nullptr;
				if (PlayerDataHandleOffset3 != nullptr)
					PlayerDataHandleOffset4 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset3, 0x40);
				void* PlayerDataHandleOffset5 = nullptr;
				if (PlayerDataHandleOffset4 != nullptr)
					PlayerDataHandleOffset5 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset4, 0xD0);
				if (PlayerDataHandleOffset5 != nullptr)
					BasicGameData::PlayerDataPlot = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset5, 0x8);
			}
		}
	}
#pragma endregion
	//��ʼ��
	static bool Init() {
		if (ModConfig::GameDataInit) 
			return true;
		else
		{
			void* PlayerPlot = *(undefined**)MH::Player::PlayerBasePlot;
			BasicGameData::PlayerPlot = *offsetPtr<undefined**>((undefined(*)())PlayerPlot, 0x50);
			BasicGameData::MapPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x7D20);
			void* PlayerDataOffset1 = *offsetPtr<undefined**>((undefined(*)())PlayerPlot, 0x50);
			void* PlayerDataHandlePlot = *(undefined**)MH::Player::PlayerDataHandlePlot;
			void* PlayerDataHandleOffset1 = nullptr;
			if (PlayerDataHandlePlot != nullptr)
				PlayerDataHandleOffset1 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandlePlot, 0x48);
			void* PlayerDataHandleOffset2 = nullptr;
			if (PlayerDataHandleOffset1 != nullptr)
				PlayerDataHandleOffset2 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset1, 0x58);
			void* PlayerDataHandleOffset3 = nullptr;
			if (PlayerDataHandleOffset2 != nullptr)
				PlayerDataHandleOffset3 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset2, 0x58);
			void* PlayerDataHandleOffset4 = nullptr;
			if (PlayerDataHandleOffset3 != nullptr)
				PlayerDataHandleOffset4 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset3, 0x40);
			void* PlayerDataHandleOffset5 = nullptr;
			if (PlayerDataHandleOffset4 != nullptr)
				PlayerDataHandleOffset5 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset4, 0xD0);
			if (PlayerDataHandleOffset5 != nullptr)
				BasicGameData::PlayerDataPlot = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset5, 0x8);
			if (
				BasicGameData::PlayerPlot != nullptr and
				BasicGameData::MapPlot != nullptr
				) {
				//��������
				MH_Initialize();
				//�����ַ��ȡ
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
				MH_ApplyQueued();
				ModConfig::GameDataInit = true;
				LOG(INFO) << ModConfig::ModName << " : Game data initialization complete!";
				LOG(INFO) << " |  Mod��" << ModConfig::ModName;
				LOG(INFO) << " |  Author��" << ModConfig::ModAuthor;
				LOG(INFO) << " |  Version��" << ModConfig::ModVersion;
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
	//ʵʱ���µ�����
	static void RealTimeUpdate() {
		if (ModConfig::GameDataInit) {
			//ʵʱ���µ�ͼ��ַ��Ϣ
			BasicGameData::MapPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x7D20);
			//д���ͼ��Ϣ���������
			if (World::MapId != *offsetPtr<int>(BasicGameData::MapPlot, 0xB88)) {
				World::MapId = *offsetPtr<int>(BasicGameData::MapPlot, 0xB88);
				//�������ɸѡ��
				Monster::Filter = pair<int, int>(255, 255);
				//���µ�ַ��Ϣ
				void* PlayerPlot = *(undefined**)MH::Player::PlayerBasePlot;
				BasicGameData::PlayerPlot = *offsetPtr<undefined**>((undefined(*)())PlayerPlot, 0x50);
			}
			//�����������
			PlayerData::Updata();
			//���¹�����Ϣ
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