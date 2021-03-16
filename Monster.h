#pragma once

namespace MonsterView {
	static map<void*, bool> MonstersState;
	static void Window() {
		//设置窗口样式
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
		//有怪物时再显示半透明窗口
		if (Base::Monster::Monsters.empty())
			window_flags |= ImGuiWindowFlags_NoBackground;
		//设置窗口透明度
		ImGui::SetNextWindowBgAlpha(0.10f);
		//设置窗口位置
		ImGui::SetNextWindowPos(ImVec2(
			ImGui::GetMainViewport()->Pos.x + ImGui::GetMainViewport()->Size.x * 0.8f,
			ImGui::GetMainViewport()->Pos.y + ImGui::GetMainViewport()->Size.y * 0.4f
		), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		//创建窗口
		ImGui::Begin("Monster", NULL, window_flags);
		//设置怪物筛选
		vector<int> ExcludeMonster = { 2,3,5,6,8,40,41,42,43,44,45,46,47,48,49,50,52,53,54,55,56,57,58,59,60,82,83,84,85,86,98 };
		//遍历所有怪物
		for (auto [monster, monsterData] : Base::Monster::Monsters) {
			//确保怪物还存在
			if (monster != nullptr) {
				//排除掉筛选中的怪物
				if (std::find(ExcludeMonster.begin(), ExcludeMonster.end(), monsterData.Id) != ExcludeMonster.end())
					continue;

				//初始化Buff信息
				map<string, MonsterBuff::MonsterBuffState> DeBuff;
				for (string debuff : vector<string>{ "Ridedowna","Dizziness","Paralysis","Sleep","Poisoning","Flicker","FlickerG","Traphole","Stasistrap" }) {
					DeBuff[debuff] = MonsterBuff::GetMonsterBuffState(monster, debuff);
				}
				//初始化生命信息
				void* healthMgr = *offsetPtr<void*>(monster, 0x7670);
				float health = *offsetPtr<float>(healthMgr, 0x64);
				float maxHealth = *offsetPtr<float>(healthMgr, 0x60);
				//初始化状态选项
				if (MonstersState.count(monster) == 0)
					MonstersState[monster] = false;

				//开始绘制窗口内容
				ImGui::Text(ICON_FA_DRAGON);//龙的图标
				ImGui::SameLine();//合并到同一行
				ImGui::Text(Component::GetMonsterName(monsterData.Id).c_str());//怪物的名字
				ImGui::SameLine();
				//将怪物地址转换成字符串
				ostringstream ptr;
				ptr << monsterData.Plot;
				string ptrstr = ptr.str();
				//是否显示怪物状态的选项框
				ImGui::Checkbox((u8"状态  " + ptrstr).c_str(), &MonstersState[monster]);
				ImGui::Separator();//分割线
				char Health[32];//生命值字符串缓存
				sprintf_s(Health, "%d/%d", (int)health, (int)maxHealth);//格式化生命值显示
				ImGui::SetNextItemWidth(300);//设置生命值进度条的宽度
				ImGui::ProgressBar((health / maxHealth), ImVec2(0.0f, 0.0f), Health);//绘制生命值进度条
				//当前怪物等于最近一次被攻击的怪物或启用怪物状态显示的情况下显示怪物状态框
				if (MonstersState[monster] or Base::PlayerData::AttackMonsterPlot == monster) {
					//获取怪物状态积攒值的数据
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
					//获取怪物状态恢复值的数据
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
					const char* labels[] = { u8"倒",u8"晕",u8"麻",u8"睡",u8"毒",u8"闪",u8"G闪",u8"落穴",u8"麻穴" };//设置状态名
					const double positions[] = { 0,1,2,3,4,5,6,7,8 };//设置行
					ImPlot::SetNextPlotLimits(0, 30, -0.5, 10, ImGuiCond_Always);//绘制状态名
					ImPlot::SetNextPlotTicksY(positions, 9, labels);//绘制行（此处多一行留给图列）
					ImGui::SetNextItemWidth(100);//设置状态框宽度
					//绘制状态显示框
					if (ImPlot::BeginPlot((Component::GetMonsterName(monsterData.Id) + u8"状态").c_str(), "", "", ImVec2(-1, 0), 0, 0, ImPlotAxisFlags_Invert))
					{
						ImPlot::SetLegendLocation(ImPlotLocation_SouthWest, ImPlotOrientation_Horizontal);
						ImPlot::PlotBarsH(u8"积累值", StateValue, 9, 0.2, -0.2);
						ImPlot::PlotBarsH(u8"持续时间", RecoveryValue, 9, 0.2, 0);
						ImPlot::EndPlot();
					}
				}
			}
			ImGui::Separator();
		}
		ImGui::End();
	}
}