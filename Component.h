#pragma once
#include <io.h>

using namespace std;
using namespace loader;

namespace Component {
	/*
		��ȡ��������
	*/
#pragma region GetMonsterName
	static string GetMonsterName(int id) {
		switch (id)
		{
		case 0:
			return u8"�U���";
		case 1:
			return u8"����";
		case 2:
			return u8"��ʳ��";
		case 3:
			return u8"�ײ���";
		case 4:
			return u8"��ɽ��";
		case 5:
			return u8"���i";
		case 6:
			return u8"ҧ�~";
		case 7:
			return u8"���ײ���";
		case 8:
			return u8"��ͻ����";
		case 9:
			return u8"�ƻ���";
		case 10:
			return u8"�ѻ���";
		case 11:
			return u8"�n����";
		case 12:
			return u8"����";
		case 13:
			return u8"�ڽ���";
		case 14:
			return u8"����";
		case 15:
			return u8"ؐϣĦ˹";
		case 16:
			return u8"���";
		case 17:
			return u8"������";
		case 18:
			return u8"������";
		case 19:
			return u8"������";
		case 20:
			return u8"�ֱ���";
		case 21:
			return u8"��ɰ��";
		case 22:
			return u8"���m��";
		case 23:
			return u8"¹�׾�";
		case 24:
			return u8"�����B";
		case 25:
			return u8"��M��";
		case 26:
			return u8"ڤ����";
		case 27:
			return u8"ɦ�B";
		case 28:
			return u8"ѣ�B";
		case 29:
			return u8"���~��";
		case 30:
			return u8"�w����";
		case 31:
			return u8"������";
		case 32:
			return u8"�LƯ��";
		case 33:
			return u8"�������";
		case 34:
			return u8"�Kצ��";
		case 35:
			return u8"���m��";
		case 36:
			return u8"������";
		case 37:
			return u8"���\��";
		case 38:
			return u8"�k�x��";
		case 39:
			return u8"���[��";
		case 40:
			return u8"������";
		case 41:
			return u8"���`¹";
		case 42:
			return u8"���`¹";
		case 43:
			return u8"�޼��x";
		case 44:
			return u8"�޷�";
		case 45:
			return u8"������";
		case 46:
			return u8"��ͻ����";
		case 47:
			return u8"������";
		case 48:
			return u8"؈����";
		case 49:
			return u8"������";
		case 50:
			return u8"�����";
		case 51:
			return u8"�Ŵ�¹�׾�";
		case 52:
			return u8"ͻ����";
		case 53:
			return u8"�����";
		case 54:
			return u8"ɢ������";
		case 55:
			return u8"����ɢ������";
		case 56:
			return u8"������";
		case 57:
			return u8"������";
		case 58:
			return u8"�ƻ���������";
		case 59:
			return u8"��ͻ��";
		case 60:
			return u8"�S��������";
		case 61:
			return u8"�Z��";
		case 62:
			return u8"Ѹ��";
		case 63:
			return u8"������";
		case 64:
			return u8"��ŭ�ֱ���";
		case 65:
			return u8"����";
		case 66:
			return u8"����";
		case 67:
			return u8"�����";
		case 68:
			return u8"�����";
		case 69:
			return u8"ˮ���B";
		case 70:
			return u8"������M��";
		case 71:
			return u8"�w����";
		case 72:
			return u8"������";
		case 73:
			return u8"˪���LƯ��";
		case 74:
			return u8"��צ��";
		case 75:
			return u8"�F�Ό�����";
		case 76:
			return u8"�tɏ���[��";
		case 77:
			return u8"���~��";
		case 78:
			return u8"��ţ��";
		case 79:
			return u8"������";
		case 80:
			return u8"�鲨��";
		case 81:
			return u8"��ػ�����";
		case 82:
			return u8"����";
		case 83:
			return u8"ѩ¹";
		case 84:
			return u8"������";
		case 85:
			return u8"������";
		case 86:
			return u8"�F�p��";
		case 87:
			return u8"�ͺ���";
		case 88:
			return u8"�����";
		case 89:
			return u8"�y����";
		case 90:
			return u8"�����B";
		case 91:
			return u8"��{��";
		case 92:
			return u8"������{��";
		case 93:
			return u8"���Z��";
		case 94:
			return u8"������";
		case 95:
			return u8"�z����";
		case 96:
			return u8"�ͱ�����";
		case 97:
			return u8"ڤ����";
		case 98:
			return u8"Unavailable";
		case 99:
			return u8"��ۺ����B";
		case 100:
			return u8"˪�б�����";
		case 101:
			return u8"����";
		default:
			return u8"δ֪����";
		}
	}
}

