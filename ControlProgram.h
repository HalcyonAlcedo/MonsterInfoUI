#pragma once
#include <cstdio>

#include <dxgi.h>
#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"
#include <implot.h>
#include "IconsFontAwesome5.h"
#include <d3d12.h>
#include <dxgi1_4.h>

#include "kiero.h"
#include "dxhook/inputhooks.h"

namespace ControlProgram {
	//ImGui����
	typedef long(__fastcall* PresentD3D12) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	typedef void(__fastcall* DrawInstancedD3D12)(ID3D12GraphicsCommandList* dCommandList, UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation);
	typedef void(__fastcall* DrawIndexedInstancedD3D12)(ID3D12GraphicsCommandList* dCommandList, UINT IndexCount, UINT InstanceCount, UINT StartIndex, INT BaseVertex);
	ID3D12Device* d3d12Device = nullptr;
	ID3D12DescriptorHeap* d3d12DescriptorHeapBackBuffers = nullptr;
	ID3D12DescriptorHeap* d3d12DescriptorHeapImGuiRender = nullptr;
	ID3D12GraphicsCommandList* d3d12CommandList = nullptr;
	ID3D12Fence* d3d12Fence = nullptr;
	UINT64 d3d12FenceValue = 0;
	ID3D12CommandQueue* d3d12CommandQueue = nullptr;
	PresentD3D12 oPresentD3D12;
	DrawInstancedD3D12 oDrawInstancedD3D12;
	DrawIndexedInstancedD3D12 oDrawIndexedInstancedD3D12;
	void(*oExecuteCommandListsD3D12)(ID3D12CommandQueue*, UINT, ID3D12CommandList*);
	HRESULT(*oSignalD3D12)(ID3D12CommandQueue*, ID3D12Fence*, UINT64);
	struct __declspec(uuid("189819f1-1db6-4b57-be54-1821339b85f7")) ID3D12Device;
	struct FrameContext {
		ID3D12CommandAllocator* commandAllocator = nullptr;
		ID3D12Resource* main_render_target_resource = nullptr;
		D3D12_CPU_DESCRIPTOR_HANDLE main_render_target_descriptor;
	};
	uint32_t buffersCounts = -1;
	FrameContext* frameContext;
	bool shutdown = false;
	bool isOpen = true;

	//��������
	static map<void*, bool> MonstersState;
	static void ImGuiWindow()
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
		if (Base::Monster::Monsters.empty())
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (isOpen) {
#pragma region Monster
			ImGui::SetNextWindowBgAlpha(0.10f);
			ImGui::SetNextWindowPos(ImVec2(
				ImGui::GetMainViewport()->Pos.x + ImGui::GetMainViewport()->Size.x * 0.8f,
				ImGui::GetMainViewport()->Pos.y + ImGui::GetMainViewport()->Size.y * 0.4f
			), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
			//ImGui::SetNextWindowSize(ImVec2(350, 680), ImGuiCond_Always);
			ImGui::Begin("Monster", NULL, window_flags);
			vector<int> ExcludeMonster = { 2,3,5,6,8,40,41,42,43,44,45,46,47,48,49,50,52,53,54,55,56,57,58,59,60,82,83,84,85,86,98 };
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
				if (monster != nullptr) {
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
					ImGui::Text(ICON_FA_DRAGON);
					ImGui::SameLine();
					ImGui::Text(Component::GetMonsterName(monsterData.Id).c_str());
					ImGui::SameLine();
					ostringstream ptr;
					ptr << monsterData.Plot;
					string ptrstr = ptr.str();
					ImGui::Checkbox((u8"״̬  " + ptrstr).c_str(), &MonstersState[monster]);
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
						const char* labels[] = { u8"��",u8"��",u8"��",u8"˯",u8"��",u8"��",u8"G��",u8"��Ѩ",u8"��Ѩ" };
						const double positions[] = { 0,1,2,3,4,5,6,7,8 };
						ImPlot::SetNextPlotLimits(0, 30, -0.5, 10, ImGuiCond_Always);
						ImPlot::SetNextPlotTicksY(positions, 9, labels);
						ImGui::SetNextItemWidth(100);
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
#pragma endregion
		}
	}

	//������
	static long __fastcall hookPresentD3D12(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags) {
		static bool init = false;

		if (GetAsyncKeyState(globals::openMenuKey) & 0x1) {
			isOpen ? isOpen = false : isOpen = true;
		}

		if (!init) {
			if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&d3d12Device))) {
				ImGui::CreateContext();
				ImPlot::CreateContext();

				unsigned char* pixels;
				int width, height;
				ImGuiIO& io = ImGui::GetIO(); (void)io;
				ImGui::StyleColorsDark();
				io.Fonts->AddFontDefault();
				io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
				io.Fonts->AddFontFromFileTTF("c:/windows/fonts/simhei.ttf", 13.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
				static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
				ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
				io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_FAS, 16.0f, &icons_config, icons_ranges);
				io.IniFilename = NULL;

				CreateEvent(nullptr, false, false, nullptr);

				DXGI_SWAP_CHAIN_DESC sdesc;
				pSwapChain->GetDesc(&sdesc);
				sdesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
				sdesc.OutputWindow = globals::mainWindow;
				sdesc.Windowed = ((GetWindowLongPtr(globals::mainWindow, GWL_STYLE) & WS_POPUP) != 0) ? false : true;

				buffersCounts = sdesc.BufferCount;
				frameContext = new FrameContext[buffersCounts];

				D3D12_DESCRIPTOR_HEAP_DESC descriptorImGuiRender = {};
				descriptorImGuiRender.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
				descriptorImGuiRender.NumDescriptors = buffersCounts;
				descriptorImGuiRender.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

				if (d3d12Device->CreateDescriptorHeap(&descriptorImGuiRender, IID_PPV_ARGS(&d3d12DescriptorHeapImGuiRender)) != S_OK)
					return false;

				ID3D12CommandAllocator* allocator;
				if (d3d12Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator)) != S_OK)
					return false;

				for (size_t i = 0; i < buffersCounts; i++) {
					frameContext[i].commandAllocator = allocator;
				}

				if (d3d12Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator, NULL, IID_PPV_ARGS(&d3d12CommandList)) != S_OK ||
					d3d12CommandList->Close() != S_OK)
					return false;

				D3D12_DESCRIPTOR_HEAP_DESC descriptorBackBuffers;
				descriptorBackBuffers.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
				descriptorBackBuffers.NumDescriptors = buffersCounts;
				descriptorBackBuffers.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
				descriptorBackBuffers.NodeMask = 1;

				if (d3d12Device->CreateDescriptorHeap(&descriptorBackBuffers, IID_PPV_ARGS(&d3d12DescriptorHeapBackBuffers)) != S_OK)
					return false;

				const auto rtvDescriptorSize = d3d12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
				D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = d3d12DescriptorHeapBackBuffers->GetCPUDescriptorHandleForHeapStart();

				for (size_t i = 0; i < buffersCounts; i++) {
					ID3D12Resource* pBackBuffer = nullptr;

					frameContext[i].main_render_target_descriptor = rtvHandle;
					pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
					d3d12Device->CreateRenderTargetView(pBackBuffer, nullptr, rtvHandle);
					frameContext[i].main_render_target_resource = pBackBuffer;
					rtvHandle.ptr += rtvDescriptorSize;
				}

				ImGui_ImplWin32_Init(globals::mainWindow);
				ImGui_ImplDX12_Init(d3d12Device, buffersCounts,
					DXGI_FORMAT_R8G8B8A8_UNORM, d3d12DescriptorHeapImGuiRender,
					d3d12DescriptorHeapImGuiRender->GetCPUDescriptorHandleForHeapStart(),
					d3d12DescriptorHeapImGuiRender->GetGPUDescriptorHandleForHeapStart());

				ImGui_ImplDX12_CreateDeviceObjects();

				inputhook::Init(globals::mainWindow);
			}
			init = true;
		}

		if (shutdown == false) {
			if (d3d12CommandQueue == nullptr)
				return oPresentD3D12(pSwapChain, SyncInterval, Flags);

			ImGui_ImplDX12_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			ImGuiWindow();

			FrameContext& currentFrameContext = frameContext[pSwapChain->GetCurrentBackBufferIndex()];
			currentFrameContext.commandAllocator->Reset();

			D3D12_RESOURCE_BARRIER barrier;
			barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
			barrier.Transition.pResource = currentFrameContext.main_render_target_resource;
			barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
			barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
			barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

			d3d12CommandList->Reset(currentFrameContext.commandAllocator, nullptr);
			d3d12CommandList->ResourceBarrier(1, &barrier);
			d3d12CommandList->OMSetRenderTargets(1, &currentFrameContext.main_render_target_descriptor, FALSE, nullptr);
			d3d12CommandList->SetDescriptorHeaps(1, &d3d12DescriptorHeapImGuiRender);

			ImGui::Render();
			ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), d3d12CommandList);

			barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
			barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

			d3d12CommandList->ResourceBarrier(1, &barrier);
			d3d12CommandList->Close();

			d3d12CommandQueue->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList* const*>(&d3d12CommandList));
		}

		return oPresentD3D12(pSwapChain, SyncInterval, Flags);
	}
	static void __fastcall hookkDrawInstancedD3D12(ID3D12GraphicsCommandList* dCommandList, UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation) {
		return oDrawInstancedD3D12(dCommandList, VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
	}
	static void __fastcall hookDrawIndexedInstancedD3D12(ID3D12GraphicsCommandList* dCommandList, UINT IndexCount, UINT InstanceCount, UINT StartIndex, INT BaseVertex) {
		return oDrawIndexedInstancedD3D12(dCommandList, IndexCount, InstanceCount, StartIndex, BaseVertex);
	}
	static void hookExecuteCommandListsD3D12(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists) {
		if (!d3d12CommandQueue)
			d3d12CommandQueue = queue;

		oExecuteCommandListsD3D12(queue, NumCommandLists, ppCommandLists);
	}
	static HRESULT hookSignalD3D12(ID3D12CommandQueue* queue, ID3D12Fence* fence, UINT64 value) {
		if (d3d12CommandQueue != nullptr && queue == d3d12CommandQueue) {
			d3d12Fence = fence;
			d3d12FenceValue = value;
		}

		return oSignalD3D12(queue, fence, value);
	}
	static void release() {
		shutdown = true;
		d3d12Device->Release();
		d3d12DescriptorHeapBackBuffers->Release();
		d3d12DescriptorHeapImGuiRender->Release();
		d3d12CommandList->Release();
		d3d12Fence->Release();
		d3d12CommandQueue->Release();
	}
	//��ʼ��
	static void Init() {
		if (kiero::init(kiero::RenderType::D3D12) == kiero::Status::Success) {
			kiero::bind(54, (void**)&oExecuteCommandListsD3D12, hookExecuteCommandListsD3D12);
			kiero::bind(58, (void**)&oSignalD3D12, hookSignalD3D12);
			kiero::bind(140, (void**)&oPresentD3D12, hookPresentD3D12);
			kiero::bind(84, (void**)&oDrawInstancedD3D12, hookkDrawInstancedD3D12);
			kiero::bind(85, (void**)&oDrawIndexedInstancedD3D12, hookDrawIndexedInstancedD3D12);

			do {
				Sleep(100);
			} while (!(GetAsyncKeyState(globals::uninjectKey) & 0x1));

			release();

			kiero::shutdown();

			inputhook::Remove(globals::mainWindow);

			Beep(220, 100);

			FreeLibraryAndExitThread(globals::mainModule, 0);
		}
	}
}