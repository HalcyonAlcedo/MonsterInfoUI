#pragma once
using namespace std;
namespace PlayerBuff {
	static int GetBuffPtr(std::string buff) {
		//����
			//�ѡ�����ǿ��
		if (buff == "Whistle Self Improvement") {
			return 0x38;
		}
		//�ѡ�������UP��
		if (buff == "Whistle Attack Up") {
			return 0x40;
		}
		//�ѡ�����UP��
		if (buff == "Whistle Health Up") {
			return 0x48;
		}
		//�ѡ��������ļ����
		if (buff == "Whistle Stamina Use Reduced") {
			return 0x50;
		}
		//�ѡ���ѹ��Ч
		if (buff == "Whistle All Wind Pressure Negated") {
			return 0x58;
		}
		//�ѡ�������UP��
		if (buff == "Whistle Defense Up") {
			return 0x60;
		}
		//�ѡ�����������ļ����
		if (buff == "Whistle Tool Use Drain Reduced") {
			return 0x68;
		}
		//�ѡ������ظ��ٶ�UP��
		if (buff == "Whistle Recovery Up") {
			return 0x84;
		}
		//�ѡ�����������
		if (buff == "Whistle Earplugs") {
			return 0x8c;
		}
		//�ѡ��������ļӻ�
		if (buff == "Whistle Divine Protection") {
			return 0x90;
		}
		//�ѡ�����׷����ǿ��
		if (buff == "Whistle Scoutfly Power Up") {
			return 0x94;
		}
		//�ѡ������˺���Ч
		if (buff == "Whistle Envir. Damage Negated") {
			return 0x98;
		}
		//�ѡ�������Ч
		if (buff == "Whistle Stun Negated") {
			return 0x9c;
		}
		//�ѡ������Ч
		if (buff == "Whistle Paralysis Negated") {
			return 0xa0;
		}
		//�ѡ�����Ч
		if (buff == "Whistle Tremors Negated") {
			return 0xa4;
		}
		//�ѡ���Ӧ��ɳˮ����ѩ
		if (buff == "Whistle Much/Water/Deep Snow Res") {
			return 0xa8;
		}
		//�ѡ������Է���UP��
		if (buff == "Whistle Fire Res Up") {
			return 0xb0;
		}
		//�ѡ�ˮ���Է���UP��
		if (buff == "Whistle Water Res Up") {
			return 0xb8;
		}
		//�ѡ������Է���UP��
		if (buff == "Whistle Thunder Res Up") {
			return 0xc0;
		}
		//�ѡ������Է���UP��
		if (buff == "Whistle Ice Res Up") {
			return 0xc8;
		}
		//�ѡ������Է���UP��
		if (buff == "Whistle Dragon Res Up") {
			return 0xd0;
		}
		//�ѡ����Թ���������
		if (buff == "Whistle Elemental Attack Boost") {
			return 0xd4;
		}
		//�ѡ�ȫ�����쳣״̬��Ч
		if (buff == "Whistle Blight Negated") {
			return 0xd8;
		}
		//�ѡ�������Ч
		if (buff == "Whistle Knockbacks Negated") {
			return 0xe4;
		}
		//�ѡ�ȫ���Է���ǿ��
		if (buff == "Whistle Blight Resistance Up") {
			return 0xec;
		}
		//�ѡ�����������
		if (buff == "Whistle Affinity Up") {
			return 0xf0;
		}
		//�ѡ�ȫ״̬�쳣��Ч
		if (buff == "Whistle All Ailments Negated") {
			return 0xf4;
		}
		//�ѡ��쳣����������
		if (buff == "Whistle Abnormal Status Atk. Increase") {
			return 0xfc;
		}
		//�ѡ��������ֵUP��ظ�
		if (buff == "Whistle Max Stamina Up / Recovery") {
			return 0x10c;
		}
		//�ѡ��������ֵUP��ظ�
		if (buff == "Whistle Extended Health Recovery") {
			return 0x110;
		}
		//�ѡ��ٶ���ر�����UP
		if (buff == "Whistle Speed Boost / Evade Window Up") {
			return 0x114;
		}
		//�ѡ�����Ч������
		if (buff == "Whistle Elemental Effectiveness") {
			return 0x118;
		}
		//è
		//è������
		if (buff == "Palico Resuscitate") {
			return 0x11c;
		}
		//è��������UP��
		if (buff == "Palico Attack Up") {
			return 0x124;
		}
		//è��������UP��
		if (buff == "Palico Defense Up") {
			return 0x12c;
		}
		//è������������
		if (buff == "Palico Affinity Up") {
			return 0x130;
		}
		//è���ָ��ٶ�UP
		if (buff == "Palico Recovery Up") {
			return 0x134;
		}
		//è������UP
		if (buff == "Palico Health Up") {
			return 0x138;
		}
		//è���������ļ���
		if (buff == "Palico Stamina Up") {
			return 0x13c;
		}
		//è���������ӻ�
		if (buff == "Palico Divine Protection") {
			return 0x144;
		}
		//è��������Ч
		if (buff == "Palico Stun Negated") {
			return 0x14c;
		}
		//è�������Ч
		if (buff == "Palico Thunder Negated") {
			return 0x150;
		}
		//è������
		if (buff == "Palico Seismic") {
			return 0x154;
		}
		//è����������
		if (buff == "Palico Hearing Protection") {
			return 0x158;
		}
		//��debuff
		//�������쳣
		if (buff == "Fire Blight") {
			return 0x5ec;
		}
		//�������쳣
		if (buff == "Thunder Blight") {
			return 0x5f0;
		}
		//ˮ�����쳣
		if (buff == "Water Blight") {
			return 0x5f4;
		}
		//�������쳣
		if (buff == "Ice Blight") {
			return 0x5f8;
		}
		//�������쳣
		if (buff == "Dragon Blight") {
			return 0x5fc;
		}
		//˺���˺�
		if (buff == "Bleed") {
			return 0x600;
		}
		//�����˺�
		if (buff == "Effuvial") {
			return 0x608;
		}
		//�ж�
		if (buff == "Poison") {
			return 0x5dc;
		}
		//�Ͷ�
		if (buff == "High Poison") {
			return 0x5e0;
		}
		//������
		if (buff == "Blastscourge") {
			return 0x62c;
		}
		//�����½�
		if (buff == "Defense Down") {
			return 0x60c;
		}
		//���������½�
		if (buff == "Whistle Down") {
			return 0x614;
		}
		//��ֹʹ����Ʒ
		if (buff == "Prohibited Articles") {
			return 0x61c;
		}
		//���������쳣
		if (buff == "blasting Blight") {
			return 0x620;
		}
		//��buff
		//˺�ѻָ�
		if (buff == "Bleed Recovery") {
			return 0x604;
		}
		//ǿ��ҩ
		if (buff == "Dash Juice") {
			return 0x690;
		}
		//�����׳�
		if (buff == "Wiggle Litch") {
			return 0x694;
		}
		//������
		if (buff == "Recovery Up") {
			return 0x698;
		}
		//��������
		if (buff == "Might Seed") {
			return 0x6A0;
		}
		//��������
		if (buff == "Adamant Seed") {
			return 0x6B0;
		}
		//���˷۳�
		if (buff == "Demon Powder") {
			return 0x6C4;
		}
		//Ӳ���۳�
		if (buff == "Hardshell Powder") {
			return 0x6C8;
		}
		//������+12
		if (buff == "Attack +12") {
			return 0x6CC;
		}
		//������+30
		if (buff == "Defense +30") {
			return 0x6d0;
		}
		//����
		if (buff == "Cool Drink") {
			return 0x6EC;
		}
		//����
		if (buff == "Hot Drink") {
			return 0x6F0;
		}
		//��Ȫ��HP�ظ�
		if (buff == "Hot Springs: HP Regen") {
			return 0x6F8;
		}
		//��Ȫ����������
		if (buff == "Hot Springs: Cold Res") {
			return 0x6FC;
		}
		//���Ͳݣ�����������
		if (buff == "Thawpuff: Ice Res") {
			return 0x71C;
		}
		//��¹���������up
		if (buff == "Powercone") {
			return 0x718;
		}
		//���
		if (buff == "Encouraging") {
			return 0x754;
		}
		//����
		if (buff == "Surrender") {
			return 0x764;
		}
		//����ǿ��
		if (buff == "Slip By Strengthening") {
			return 0x770;
		}
		//��������
		if (buff == "Attacks On The Defensive") {
			return 0x79C;
		}
		//ת��Ϊ��
		if (buff == "Turn Calamity Into Blessing") {
			return 0x7A0;
		}
		//��ս��
		if (buff == "Challenger") {
			return 0x748;
		}
		//Թ��
		if (buff == "Resentment") {
			return 0x74C;
		}
		//è����Ϣ��
		if (buff == "Cat Rest") {
			return 0x7C8;
		}
		//ѩ��ͷ
		if (buff == "Snowman Head") {
			return 0x704;
		}
		//ѩ��ͷ����ʱ��*
		if (buff == "Snowman Head Duration") {
			return 0x708;
		}
		return 0x0;
	}
}