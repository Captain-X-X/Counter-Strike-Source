// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Hooks.h"
#include "Hacks.h"
// you should know what this is
BOOL WINAPI HookStart(HMODULE HookModule)
{
    // Initilize our cheats
    SEHooks::InitilizeHooks();
    while (!GetAsyncKeyState(VK_END) & 1)
    {
        Hacks::Update();
    }
    // Clean up on exit
    SEHooks::DisableHooks();

    // exit thread
    FreeLibraryAndExitThread(HookModule, 0);
    return TRUE;
}

// if you dont know what this is... wtf you doin' looking at my code??
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HookStart, hModule, 0, nullptr);
    }
    return TRUE;
}