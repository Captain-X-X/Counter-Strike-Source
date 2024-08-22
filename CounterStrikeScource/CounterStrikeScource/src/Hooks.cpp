#include "pch.h"
#include "Hooks.h"
#include "Hacks.h"
#include "Menu.h"

bool menu_open = false;
bool setup = false;
int winWidth = 0;
int winHeight = 0;

HWND window = nullptr;
WNDCLASSEX windowClass = {};
WNDPROC originalWindowProcess = nullptr;
LPDIRECT3DDEVICE9 device = nullptr;
LPDIRECT3D9 d3d9 = nullptr;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		menu_open = !menu_open;
		Hacks::Initilize(); // i do tis so we dont have to initilize every frame, only when the menu reopens. because the values I use for ammo and stuff are invalid when a new part of thr map loads. 
	}

	if (menu_open && ImGui_ImplWin32_WndProcHandler(window, msg, wParam, lParam))
	{
		return 1L;
	}
	return CallWindowProc(originalWindowProcess, window, msg, wParam, lParam);
}

void DestroyDirectX()
{
	if (device)
	{
		device->Release();
		device = NULL;
	}
	if (d3d9)
	{
		d3d9->Release();
		d3d9 = NULL;
	}
}
void Setup()
{
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.hIcon = NULL;
	windowClass.hCursor = NULL;
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = "HackClass1";
	windowClass.hIconSm = NULL;
	if (!RegisterClassEx(&windowClass))
	{
		throw std::runtime_error("Failed to create window class.");
	}

	// create win32 window for getting D3D device
	window = CreateWindow(windowClass.lpszClassName, "hack wnd", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, 0, 0, windowClass.hInstance, 0);
	if (!window)
	{
		throw std::runtime_error("Failed to create window.");
	}

	// get window size
	RECT winRect;
	GetWindowRect(window, &winRect);
	winWidth = winRect.right - winRect.left;
	winHeight = winRect.bottom - winRect.top;

	// get handle to d3d9.dll in hl2
	const auto handle = GetModuleHandle("d3d9.dll");
	if (!handle)
		throw std::runtime_error("Failed to get D3D9 handle.");
	// setup a template like function for getting a functions address
	using CreateFn = LPDIRECT3D9(__stdcall*)(UINT);
	const auto create = reinterpret_cast<CreateFn>(GetProcAddress(handle, "Direct3DCreate9"));
	if (!create)
		throw std::runtime_error("Failed to get D3D9 function 'Direct3DCreate9'.");

	d3d9 = create(D3D_SDK_VERSION);
	if (!d3d9)
		throw std::runtime_error("Failed to setup D3D9.");
	// setting up D3D9
	D3DPRESENT_PARAMETERS d3dparams = { };
	d3dparams.BackBufferWidth = 0;
	d3dparams.BackBufferHeight = 0;
	d3dparams.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dparams.BackBufferCount = 0;
	d3dparams.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dparams.MultiSampleQuality = NULL;
	d3dparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dparams.hDeviceWindow = window;
	d3dparams.Windowed = 1;
	d3dparams.EnableAutoDepthStencil = 0;
	d3dparams.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
	d3dparams.Flags = NULL;
	d3dparams.FullScreen_RefreshRateInHz = 0;
	d3dparams.PresentationInterval = 0;
	if (d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, window, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &d3dparams, &device) < 0)
	{
		throw std::runtime_error("Failed to setup dx9.");
	}
	// cleanup then D3D9 can be hooked!
	if (window)
	{
		DestroyWindow(window);
		UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
	}
	printf("Window, WindowClass & DirectX9 Setup and ready for hook!\n");
}

void Destroy()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(originalWindowProcess));
	DestroyDirectX();
}

constexpr void* VirtualFunction(void* thisptr, size_t index)
{
	return (*static_cast<void***>(thisptr))[index];
}
using EndSceneFn = long(__thiscall*)(void*, IDirect3DDevice9*);
EndSceneFn EndSceneOriginal = nullptr;
long __stdcall callback_EndScene(IDirect3DDevice9* pDevice)
{
	//static const auto returnAddress = _ReturnAddress();
	//const auto result = EndSceneOriginal(device, device);
	//if (_ReturnAddress() == returnAddress)
	//{
	//	return result;
	//}

	if (!setup)
	{
		auto params = D3DDEVICE_CREATION_PARAMETERS{};
		pDevice->GetCreationParameters(&params);
		window = params.hFocusWindow;
		originalWindowProcess = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
		ImGui::CreateContext();
		// set style
		ImGuiStyle* style = &ImGui::GetStyle();
		style->WindowTitleAlign = ImVec2(0.5, 0.5);
		style->WindowMinSize = ImVec2(200, 260);
		style->WindowBorderSize = 0;
		style->WindowPadding = ImVec2(15, 15);
		style->WindowRounding = 0.0f;
		style->FramePadding = ImVec2(5, 5);
		style->FrameRounding = 4.0f;
		style->ItemSpacing = ImVec2(12, 8);
		style->ItemInnerSpacing = ImVec2(8, 6);
		style->IndentSpacing = 25.0f;
		style->ScrollbarSize = 15.0f;
		style->ScrollbarRounding = 9.0f;
		style->GrabMinSize = 5.0f;	style->GrabRounding = 3.0f;
		style->FrameBorderSize = 0.50f;
		style->FramePadding = ImVec2(4, 4);
		style->WindowPadding = ImVec2(4, 4);
		style->ItemSpacing = ImVec2(4, 4);
		style->ItemInnerSpacing = ImVec2(4, 4);
		style->WindowBorderSize = 0;
		style->ChildBorderSize = 1;
		style->PopupBorderSize = 1;
		style->FrameBorderSize = 1;
		style->TabBorderSize = 0;
		style->WindowRounding = 0;
		style->ChildRounding = 0;
		style->FrameRounding = 0;
		style->PopupRounding = 0;
		style->ScrollbarRounding = 0;
		style->GrabRounding = 0;
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.90f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.41f, 0.00f, 0.80f, 1.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.41f, 0.00f, 0.80f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.41f, 0.00f, 0.80f, 0.20f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.00f, 0.80f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.00f, 0.80f, 0.39f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.41f, 0.00f, 0.80f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.41f, 0.00f, 0.80f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.41f, 0.00f, 0.80f, 0.39f);
		colors[ImGuiCol_Button] = ImVec4(0.00f, 0.00f, 0.00f, 0.40f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.41f, 0.00f, 0.80f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.41f, 0.00f, 0.80f, 0.39f);
		colors[ImGuiCol_Header] = ImVec4(0.41f, 0.00f, 0.80f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.41f, 0.00f, 0.80f, 0.50f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.41f, 0.00f, 0.80f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.41f, 0.00f, 0.80f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.00f, 0.80f, 0.39f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.41f, 0.00f, 0.80f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.41f, 0.00f, 0.80f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.41f, 0.00f, 0.80f, 0.39f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.41f, 0.00f, 0.80f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.41f, 0.00f, 0.80f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.34f, 0.34f, 0.34f, 0.97f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX9_Init(pDevice);
		setup = true;
	}
	if (menu_open)
	{
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		Menuc::RenderImGuiMenu(menu_open);

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
	Hacks::Draw(pDevice);
	return EndSceneOriginal(pDevice, pDevice);;
}

using ResetFn = HRESULT(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
ResetFn ResetOriginal = nullptr;
HRESULT __stdcall Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* params)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	const auto result = ResetOriginal(pDevice, pDevice, params);
	ImGui_ImplDX9_CreateDeviceObjects();
	return result;
}
FILE* console; //  i hate this being here
namespace SEHooks
{
    void InitilizeHooks()
    {
        AllocConsole();
        AttachConsole(GetProcessId(GetCurrentProcess()));
        freopen_s(&console, "CONOUT$", "w", stdout);
        SetConsoleTitleA("Simple HL2: Console");
		// hook D3DX9
		try
		{
			Setup();
			if (MH_Initialize())
			{
				throw std::runtime_error("Unable to initilize minhook!");
			}
			if (MH_CreateHook(VirtualFunction(device, 42), &callback_EndScene, reinterpret_cast<void**>(&EndSceneOriginal)))
			{
				throw std::runtime_error("Unable to hook EndScene()!");
			}
			if (MH_CreateHook(VirtualFunction(device, 16), &Reset, reinterpret_cast<void**>(&ResetOriginal)))
			{
				throw std::runtime_error("Unable to hook Reset()!");
			}
			if (MH_EnableHook(MH_ALL_HOOKS))
			{
				throw std::runtime_error("Unable to enable hooks!");
			}
			DestroyDirectX();
		}
		catch (const std::exception& error)
		{
			MessageBeep(MB_ICONERROR);
			MessageBox(0, error.what(), "Error!", MB_OK | MB_ICONEXCLAMATION);
			//goto UNLOAD;
		}

		printf("MinHook Initilized!\n");
		return;
    }

    void DisableHooks()
    {
        printf("Unhooking & exiting thread!\n");
        std::fclose(console);

		menu_open = false; // for some reason, if you eject when the menu is open it will crash the game. i hate this.
		Destroy();
		Hacks::Shutdown();

		// unhook D3Dx9
		MH_DisableHook(MH_ALL_HOOKS);
		MH_RemoveHook(MH_ALL_HOOKS);
		MH_Uninitialize();

		// close console
        FreeConsole(); // This way you can close the console without closing hl2
    }
}