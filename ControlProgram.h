#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include "imgui.h"  
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <dxgi.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include "kiero.h"
#include "Component.h"
#include <implot.h>
#include "IconsFontAwesome5.h"
#pragma comment ( lib, "D3D11.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace ControlProgram {
	bool initConsole = false;
	bool init = false;
	typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
	typedef uintptr_t PTR;
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	Present oPresent;
	Present oResize;
	HWND window = NULL;
	WNDPROC oWndProc;
	ID3D11Device* pDevice = NULL;
	ID3D11DeviceContext* pContext = NULL;
	ID3D11RenderTargetView* mainRenderTargetView;
	HMODULE hMod;

	static map<void*, bool> MonstersState;

	bool GameInit = false;
	void InitImGui()
	{
		ImGui::CreateContext();
		ImPlot::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		auto fonts = ImGui::GetIO().Fonts;
		fonts->AddFontFromFileTTF("c:/windows/fonts/simhei.ttf", 13.0f, NULL, fonts->GetGlyphRangesChineseFull());
		static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
		fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_FAS, 16.0f, &icons_config, icons_ranges);
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(pDevice, pContext);
	}
	HRESULT __stdcall hkResize(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		mainRenderTargetView->Release();
		mainRenderTargetView = nullptr;
		Base::ModConfig::DrawInit = false;
		Base::ModConfig::GameDataInit = false;
		return oResize(pSwapChain, SyncInterval, Flags);
	}
	HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		if (!init)
		{
			if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
			{
				pDevice->GetImmediateContext(&pContext);
				DXGI_SWAP_CHAIN_DESC sd;
				pSwapChain->GetDesc(&sd);
				window = sd.OutputWindow;
				ID3D11Texture2D* pBackBuffer;
				pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
				pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
				pBackBuffer->Release();
				oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
				InitImGui();
				init = true;
			}

			else
				return oPresent(pSwapChain, SyncInterval, Flags);
		}

		if (!Base::ModConfig::DrawInit)
			return oPresent(pSwapChain, SyncInterval, Flags);
		else if (mainRenderTargetView == nullptr) {
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
		if(Base::Monster::Monsters.empty())
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (GameInit) {
#pragma region Monster
			ImGui::SetNextWindowBgAlpha(0.10f);
			ImGui::SetNextWindowPos(ImVec2(
				ImGui::GetMainViewport()->Pos.x + ImGui::GetMainViewport()->Size.x * 0.8f,
				ImGui::GetMainViewport()->Pos.y + ImGui::GetMainViewport()->Size.y * 0.4f
			), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
			//ImGui::SetNextWindowSize(ImVec2(350, 680), ImGuiCond_Always);
			ImGui::Begin("Monster", NULL, window_flags);
			vector<int> ExcludeMonster = {2,3,5,6,8,40,41,42,43,44,45,46,47,48,49,50,52,53,54,55,56,57,58,59,60,82,83,84,85,86,98};
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
					if (monster != nullptr) {
						if (std::find(ExcludeMonster.begin(), ExcludeMonster.end(), monsterData.Id) != ExcludeMonster.end())
							continue;
						//初始化Buff信息
						map<string, MonsterBuff::MonsterBuffState> DeBuff;
						for (string debuff : vector<string>{ "Ridedowna","Dizziness","Paralysis","Sleep","Poisoning","Flicker","FlickerG","Traphole","Stasistrap"}) {
							DeBuff[debuff] = MonsterBuff::GetMonsterBuffState(monster, debuff);
						}
						//初始化生命信息
						void* healthMgr = *offsetPtr<void*>(monster, 0x7670);
						float health = *offsetPtr<float>(healthMgr, 0x64);
						float maxHealth = *offsetPtr<float>(healthMgr, 0x60);
						//初始化状态选项
						if (MonstersState.count(monster) == 0)
							MonstersState[monster] = false;
						ImGui::Text(ICON_FA_DRAGON);
						ImGui::SameLine();
						ImGui::Text(Component::GetMonsterName(monsterData.Id).c_str());
						ImGui::SameLine();
						ostringstream ptr;
						ptr << monsterData.Plot;
						string ptrstr = ptr.str();
						ImGui::Checkbox((u8"状态  " + ptrstr).c_str(), &MonstersState[monster]);
						ImGui::Separator();
						char Health[32];
						sprintf_s(Health, "%d/%d", (int)health, (int)maxHealth);
						ImGui::SetNextItemWidth(300);
						ImGui::ProgressBar((health / maxHealth), ImVec2(0.0f, 0.0f), Health);

						if (MonstersState[monster] or Base::PlayerData::AttackMonsterPlot == monster) {
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
							const char* labels[] = { u8"倒",u8"晕",u8"麻",u8"睡",u8"毒",u8"闪",u8"G闪",u8"落穴",u8"麻穴" };
							const double positions[] = { 0,1,2,3,4,5,6,7,8 };
							ImPlot::SetNextPlotLimits(0, 30, -0.5, 10, ImGuiCond_Always);
							ImPlot::SetNextPlotTicksY(positions, 9, labels);
							ImGui::SetNextItemWidth(100);
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
#pragma endregion

		}
		ImGui::Render();
		pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		return oPresent(pSwapChain, SyncInterval, Flags);
	}

	DWORD WINAPI MainThread(LPVOID lpReserved)
	{
		bool init_hook = false;
		do
		{
			if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
			{
				kiero::bind(8, (void**)&oPresent, hkPresent);
				kiero::bind(13, (void**)&oResize, hkResize);
				init_hook = true;
			}
		} while (!init_hook);
		return TRUE;
	}

	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;

		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
	}

	static void InitConsole() {
		if (initConsole)
			return;
		else
			initConsole = true;
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
	}
}