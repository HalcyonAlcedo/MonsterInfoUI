#pragma once
using namespace std;
using namespace loader;

namespace MonsterBuff {
	struct MonsterBuffState {
		float StateValue = 0;
		float MaxStateValue = 0;
		float RecoveryValue = 0;
		float MaxRecoveryValue = 0;
		MonsterBuffState(float StateValue = 0, float MaxStateValue = 0, float RecoveryValue = 0, float MaxRecoveryValue = 0)
			:StateValue(StateValue), MaxStateValue(MaxStateValue), RecoveryValue(RecoveryValue), MaxRecoveryValue(MaxRecoveryValue){
		};
	};
	namespace BuffPtr {
		//���ˣ�������ͼ��
		static int Retrea = 0x1BD00;
		//����
		static int Covet = 0x1BCF8;
		//ѣ��
		static int Dizziness = 0x1BC78;
		//���
		static int Paralysis = 0x1BC50;
		//˯��
		static int Sleep = 0x1BC58;
		//����
		static int Anesthesia = 0x1BC70;
		//�ж�
		static int Poisoning = 0x1bc48;
		//���
		static int Ride = 0x1bc68;
		//��˵���
		static int Ridedowna = 0x1bc98;
		//����
		static int Reducebreath = 0x1bc70;
		//����
		static int Explode = 0x1bc60;
		//����
		static int Flicker = 0x1bc88;
		//����G
		static int FlickerG = 0x1bc90;
		//����
		static int Smoke = 0x1bcd8;
		//���
		static int Foreignodor = 0x1bca0;
		//��Ѩ
		static int Traphole = 0x1bcb8;
		//�������
		static int Stasistrap = 0x1bcb0;
	}
	static MonsterBuffState GetMonsterBuffState(void* monster,string buff) {
		if (monster != nullptr) {
			if (buff == "Retrea") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Retrea);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178),*offsetPtr<float>(buffPtr, 0x188),*offsetPtr<float>(buffPtr, 0x1b8),*offsetPtr<float>(buffPtr, 0x15c));}
			}
			if (buff == "Covet") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Covet);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
			if (buff == "Dizziness") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Dizziness);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
			if (buff == "Paralysis") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Paralysis);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
			if (buff == "Sleep") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Sleep);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
			if (buff == "Anesthesia") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Anesthesia);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
			if (buff == "Poisoning") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Poisoning);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
			if (buff == "Ride") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Ride);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
			if (buff == "Ridedowna") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Ridedowna);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
			if (buff == "Reducebreath") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Reducebreath);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
			if (buff == "Explode") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Explode);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
			if (buff == "Flicker") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Flicker);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
			if (buff == "FlickerG") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::FlickerG);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
			if (buff == "Smoke") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Smoke);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
			if (buff == "Foreignodor") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Foreignodor);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
			if (buff == "Traphole") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Traphole);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
			if (buff == "Stasistrap") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Stasistrap);
				if (buffPtr != nullptr) { return MonsterBuffState(*offsetPtr<float>(buffPtr, 0x178), *offsetPtr<float>(buffPtr, 0x188), *offsetPtr<float>(buffPtr, 0x1b8), *offsetPtr<float>(buffPtr, 0x15c)); }
			}
		}
		return MonsterBuffState();
	}
	static void SetMonsterBuffState(void* monster, string buff) {
		if (monster != nullptr) {
			if (buff == "Retrea") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Retrea);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "Covet") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Covet);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "Dizziness") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Dizziness);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "Paralysis") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Paralysis);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "Sleep") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Sleep);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "Anesthesia") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Anesthesia);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "Poisoning") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Poisoning);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "Ride") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Ride);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "Ridedowna") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Ridedowna);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "Reducebreath") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Reducebreath);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "Explode") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Explode);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "Flicker") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Flicker);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "FlickerG") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::FlickerG);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "Smoke") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Smoke);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "Foreignodor") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Foreignodor);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "Traphole") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Traphole);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
			if (buff == "Stasistrap") {
				void* buffPtr = *offsetPtr<void*>(monster, BuffPtr::Stasistrap);
				if (buffPtr != nullptr) { *offsetPtr<float>(buffPtr, 0x178) = *offsetPtr<float>(buffPtr, 0x188); }
			}
		}
	}
}