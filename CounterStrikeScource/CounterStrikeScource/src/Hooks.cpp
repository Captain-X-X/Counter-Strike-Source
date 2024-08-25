#include "pch.h"
#include "Hooks.h"
#include "Hacks.h"
#include "Menu.h"
#include "CSS.h"


bool menu_open = false;
bool setup = false;
int winWidth = 0;
int winHeight = 0;
#ifdef _WIN32
//#define _DDEBUG 1
bool SEDetour::detour32(BYTE* src, BYTE* dst, const uintptr_t len)
{
	if (len < 5)
	{
#ifdef _DDEBUG
		printf("cant place detour32. Hook length is too short! (just like you)");
#endif // DEBUG
		return false;
	}

	DWORD curProtection;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);
	uintptr_t relativeAddress = dst - src - 5;
	*src = 0xE9;
	*(uintptr_t*)(src + 1) = relativeAddress;
	VirtualProtect(src, len, curProtection, &curProtection);
	return true;
}

BYTE* SEDetour::trampHook32(BYTE* src, BYTE* dst, const uintptr_t len)
{
	if (len < 5)
	{
#ifdef _DDEBUG
		printf("cant place trampHook32. Hook length is too short! (just like you)");
#endif // DEBUG
		return nullptr;
	}

	BYTE* gateway = (BYTE*)VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy_s(gateway, len, src, len);

	uintptr_t gatewayRelativeAddr = src - gateway - 5;
	*(gateway + len) = 0xE9;
	*(uintptr_t*)((uintptr_t)gateway + len + 1) = gatewayRelativeAddr;
	detour32(src, dst, len);
	return gateway;
}

SEDetour::SEDetour() 
{
};
SEDetour::SEDetour(BYTE* src, BYTE* dst, BYTE* PtrToGatewayFnPtr, uintptr_t len)
{
	this->src = src;
	this->dst = dst;
	this->len = len;
	this->PtrToGatewayFnPtr = PtrToGatewayFnPtr;
}
SEDetour::SEDetour(const char* exportName, const char* modName, BYTE* dst, BYTE* PtrToGatewayFnPtr, uintptr_t len)
{
	HMODULE hMod = GetModuleHandleA(modName);
	if (hMod)
	{
		this->src = (BYTE*)GetProcAddress(hMod, exportName);
		this->dst = dst;
		this->len = len;
		this->PtrToGatewayFnPtr = PtrToGatewayFnPtr;
	}
}

bool SEDetour::SetHook(BYTE* src, BYTE* dst, BYTE* PtrToGatewayFnPtr, uintptr_t len)
{
	this->src = src;
	this->dst = dst;
	this->len = len;
	this->PtrToGatewayFnPtr = PtrToGatewayFnPtr;
	return true;
}
void SEDetour::Enable()
{
	try
	{
		memcpy(originalBytes, src, len);
		*(uintptr_t*)PtrToGatewayFnPtr = (uintptr_t)trampHook32(src, dst, len);
		bStatus = true;
#if _DDEBUG
	printf("Detour in place. [0x%p]\n", dst);
#endif // DEBUG
	}
	catch (const std::exception&)
	{
		throw std::runtime_error("Failed to enable detour");
	}
}
void SEDetour::Disable()
{
	if (bStatus)
	{
		DWORD oldportect;
		VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &oldportect);
		memcpy(src, originalBytes, len);
		VirtualProtect(src, len, oldportect, &oldportect);
		bStatus = false;
#if _DDEBUG
	printf("Detour removed. [0x%p]\n", dst);
#endif // DEBUG
		return;
	}
#if _DDEBUG
	printf("Detour was not enabled. No detour to remove!\n");
#endif // DEBUG
}
constexpr void* DXVTableFunction(void* thisptr, size_t index)
{
	return (*static_cast<void***>(thisptr))[index];
}
std::vector<SEDetour> seDetour;
#endif // _WIN32

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
	// this will be changed when i learn how to get a windows width & height!
	winWidth = 1920;
	winHeight = 1080;

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
	/*printf("Window, WindowClass & DirectX9 Setup and ready for hook!\n");*/
}

void Destroy()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(originalWindowProcess));
	DestroyDirectX();
}

//constexpr void* VirtualFunction(void* thisptr, size_t index)
//{
//	return (*static_cast<void***>(thisptr))[index];
//}

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
		ImGui::GetIO().IniFilename = "";
		ImGui::GetIO().LogFilename = "";
		// set style
		ImGuiStyle* style = &ImGui::GetStyle();
		style->WindowTitleAlign = ImVec2(0.5, 0.5);
		style->WindowMinSize = ImVec2(200, 260);
		style->WindowBorderSize = 1;
		style->WindowPadding = ImVec2(8, 8);
		style->WindowRounding = 0.0f;
		style->FramePadding = ImVec2(4, 4);
		//style->ItemSpacing = ImVec2(12, 8);
		//style->ItemInnerSpacing = ImVec2(8, 6);
		style->IndentSpacing = 25.0f;
		style->ScrollbarSize = 15.0f;
		style->GrabMinSize = 5.0f;	
		//style->FramePadding = ImVec2(4, 4);
		//style->WindowPadding = ImVec2(4, 4);
		style->ItemSpacing = ImVec2(4, 4);
		style->ItemInnerSpacing = ImVec2(2, 2);
		style->ChildBorderSize = 1;
		style->PopupBorderSize = 1;
		style->FrameBorderSize = 1;
		style->TabBorderSize = 0;
		style->ChildRounding = 0;
		style->FrameRounding = 0;
		style->PopupRounding = 0;
		style->TabRounding = 0;
		style->ScrollbarRounding = 0;
		style->GrabRounding = 0;
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_TextDisabled] = ImVec4(1.00f, 0.12f, 0.12f, 0.39f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.78f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
		colors[ImGuiCol_Border] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.78f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(1.00f, 0.12f, 0.12f, 0.39f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(1.00f, 0.12f, 0.12f, 0.39f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.12f, 0.12f, 0.39f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.12f, 0.12f, 0.39f);
		colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(1.00f, 0.12f, 0.12f, 0.78f);
		colors[ImGuiCol_Tab] = ImVec4(1.00f, 0.12f, 0.12f, 0.39f);
		colors[ImGuiCol_TabSelected] = ImVec4(1.00f, 0.12f, 0.12f, 1.00f);
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
#ifdef _DDEBUG
        AllocConsole();
        AttachConsole(GetProcessId(GetCurrentProcess()));
        freopen_s(&console, "CONOUT$", "w", stdout);
        SetConsoleTitleA("Simple HL2: Console");
#endif // _DDEBUG
		// hook D3DX9
		try
		{
			Setup();
			seDetour.push_back(SEDetour((BYTE*)DXVTableFunction(device, DX9ES_HOOK_VTI), (BYTE*)&callback_EndScene, (BYTE*)&EndSceneOriginal, DX9ES_HOOK_LENGTH));
			seDetour[0].Enable();
			seDetour.push_back(SEDetour((BYTE*)DXVTableFunction(device, DX9RS_HOOK_VTI), (BYTE*)&Reset, (BYTE*)&ResetOriginal, DX9RS_HOOK_LENGTH));
			seDetour[1].Enable();
			DestroyDirectX();
		}
		catch (const std::exception& error)
		{
			MessageBeep(MB_ICONERROR);
			MessageBox(0, error.what(), "Error!", MB_OK | MB_ICONEXCLAMATION);
		}
		CounterStrikeSourceSE::testPrint("Simple Counter-Strike:Source Cheat Loaded!");
		return;
    }

    void DisableHooks()
    {
		for (int i = 0; i < seDetour.size(); i++)
		{
			seDetour[i].Disable();
		}
		Destroy();
		Hacks::Shutdown();
#ifdef _DDEBUG
		// close console
        FreeConsole(); // This way you can close the console without closing hl2
        std::fclose(console);
#endif // _DDEBUG
    }
}