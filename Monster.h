#pragma once

namespace MonsterView {
	static map<void*, bool> MonstersState;
	static void Window() {
		//���ô�����ʽ
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
		//�й���ʱ����ʾ��͸������
		if (Base::Monster::Monsters.empty())
			window_flags |= ImGuiWindowFlags_NoBackground;
		//���ô���͸����
		ImGui::SetNextWindowBgAlpha(0.10f);
		//���ô���λ��
		ImGui::SetNextWindowPos(ImVec2(
			ImGui::GetMainViewport()->Pos.x + ImGui::GetMainViewport()->Size.x * 0.8f,
			ImGui::GetMainViewport()->Pos.y + ImGui::GetMainViewport()->Size.y * 0.4f
		), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		//��������
		ImGui::Begin("Monster", NULL, window_flags);
		//���ù���ɸѡ
		vector<int> ExcludeMonster = { 2,3,5,6,8,40,41,42,43,44,45,46,47,48,49,50,52,53,54,55,56,57,58,59,60,82,83,84,85,86,98 };
		//�������й���
		for (auto [monster, monsterData] : Base::Monster::Monsters) {
			//ȷ�����ﻹ����
			if (monster != nullptr) {
				//�ų���ɸѡ�еĹ���
				if (std::find(ExcludeMonster.begin(), ExcludeMonster.end(), monsterData.Id) != ExcludeMonster.end())
					continue;

				//��ʼ��Buff��Ϣ
				map<string, MonsterBuff::MonsterBuffState> DeBuff;
				for (string debuff : vector<string>{ "Ridedowna","Dizziness","Paralysis","Sleep","Poisoning","Flicker","FlickerG","Traphole","Stasistrap" }) {
					DeBuff[debuff] = MonsterBuff::GetMonsterBuffState(monster, debuff);
				}
				//��ʼ��������Ϣ
				void* healthMgr = *offsetPtr<void*>(monster, 0x7670);
				float health = *offsetPtr<float>(healthMgr, 0x64);
				float maxHealth = *offsetPtr<float>(healthMgr, 0x60);
				//��ʼ��״̬ѡ��
				if (MonstersState.count(monster) == 0)
					MonstersState[monster] = false;

				//��ʼ���ƴ�������
				ImGui::Text(ICON_FA_DRAGON);//����ͼ��
				ImGui::SameLine();//�ϲ���ͬһ��
				ImGui::Text(Component::GetMonsterName(monsterData.Id).c_str());//���������
				ImGui::SameLine();
				//�������ַת�����ַ���
				ostringstream ptr;
				ptr << monsterData.Plot;
				string ptrstr = ptr.str();
				//�Ƿ���ʾ����״̬��ѡ���
				ImGui::Checkbox((u8"״̬  " + ptrstr).c_str(), &MonstersState[monster]);
				ImGui::Separator();//�ָ���
				char Health[32];//����ֵ�ַ�������
				sprintf_s(Health, "%d/%d", (int)health, (int)maxHealth);//��ʽ������ֵ��ʾ
				ImGui::SetNextItemWidth(300);//��������ֵ�������Ŀ��
				ImGui::ProgressBar((health / maxHealth), ImVec2(0.0f, 0.0f), Health);//��������ֵ������
				//��ǰ����������һ�α������Ĺ�������ù���״̬��ʾ���������ʾ����״̬��
				if (MonstersState[monster] or Base::PlayerData::AttackMonsterPlot == monster) {
					//��ȡ����״̬����ֵ������
					float StateValue[] = {
					(DeBuff["Ridedowna"].StateValue / DeBuff["Ridedowna"].MaxStateValue) * 30,
					(DeBuff["Dizziness"].StateValue / DeBuff["Dizziness"].MaxStateValue) * 30,
					(DeBuff["Paralysis"].StateValue / DeBuff["Paralysis"].MaxStateValue) * 30,
					(DeBuff["Sleep"].StateValue / DeBuff["Sleep"].MaxStateValue) * 30,
					(DeBuff["Poisoning"].StateValue / DeBuff["Poisoning"].MaxStateValue) * 30,
					(DeBuff["Flicker"].StateValue / DeBuff["Flicker"].MaxStateValue) * 30,
					(DeBuff["FlickerG"].StateValue / DeBuff["FlickerG"].MaxStateValue) * 30,
					(DeBuff["Traphole"].StateValue / DeBuff["Traphole"].MaxStateValue) * 30,
					(DeBuff["Stasistrap"].StateValue / DeBuff["Stasistrap"].MaxStateValue) * 30
					};
					//��ȡ����״̬�ָ�ֵ������
					float RecoveryValue[] = {
						DeBuff["Ridedowna"].RecoveryValue <= 0 ? 0 : DeBuff["Ridedowna"].MaxRecoveryValue - DeBuff["Ridedowna"].RecoveryValue,
						DeBuff["Dizziness"].RecoveryValue <= 0 ? 0 : DeBuff["Dizziness"].MaxRecoveryValue - DeBuff["Dizziness"].RecoveryValue,
						DeBuff["Paralysis"].RecoveryValue <= 0 ? 0 : DeBuff["Paralysis"].MaxRecoveryValue - DeBuff["Paralysis"].RecoveryValue,
						DeBuff["Sleep"].RecoveryValue <= 0 ? 0 : DeBuff["Sleep"].MaxRecoveryValue - DeBuff["Sleep"].RecoveryValue,
						DeBuff["Poisoning"].RecoveryValue <= 0 ? 0 : DeBuff["Poisoning"].MaxRecoveryValue - DeBuff["Poisoning"].RecoveryValue,
						DeBuff["Flicker"].RecoveryValue <= 0 ? 0 : DeBuff["Flicker"].MaxRecoveryValue - DeBuff["Flicker"].RecoveryValue,
						DeBuff["FlickerG"].RecoveryValue <= 0 ? 0 : DeBuff["FlickerG"].MaxRecoveryValue - DeBuff["FlickerG"].RecoveryValue,
						DeBuff["Traphole"].RecoveryValue <= 0 ? 0 : DeBuff["Traphole"].MaxRecoveryValue - DeBuff["Traphole"].RecoveryValue,
						DeBuff["Stasistrap"].RecoveryValue <= 0 ? 0 : DeBuff["Stasistrap"].MaxRecoveryValue - DeBuff["Stasistrap"].RecoveryValue
					};
					const char* labels[] = { u8"��",u8"��",u8"��",u8"˯",u8"��",u8"��",u8"G��",u8"��Ѩ",u8"��Ѩ" };//����״̬��
					const double positions[] = { 0,1,2,3,4,5,6,7,8 };//������
					ImPlot::SetNextPlotLimits(0, 30, -0.5, 10, ImGuiCond_Always);//����״̬��
					ImPlot::SetNextPlotTicksY(positions, 9, labels);//�����У��˴���һ������ͼ�У�
					ImGui::SetNextItemWidth(100);//����״̬����
					//����״̬��ʾ��
					if (ImPlot::BeginPlot((Component::GetMonsterName(monsterData.Id) + u8"״̬").c_str(), "", "", ImVec2(-1, 0), 0, 0, ImPlotAxisFlags_Invert))
					{
						ImPlot::SetLegendLocation(ImPlotLocation_SouthWest, ImPlotOrientation_Horizontal);
						ImPlot::PlotBarsH(u8"����ֵ", StateValue, 9, 0.2, -0.2);
						ImPlot::PlotBarsH(u8"����ʱ��", RecoveryValue, 9, 0.2, 0);
						ImPlot::EndPlot();
					}
				}
			}
			ImGui::Separator();
		}
		ImGui::End();
	}
}