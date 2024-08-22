/*
	this is a simple class for assaultcube
	  AssaultCube Version 1.2.0.2
	created by: captain_x-X#2181
	https://github.com/Captain-X-X
*/
#include "pch.h"
#include "Memory.h"
namespace Memory
{
	// utils:memory
	void patchMem(BYTE* dst, BYTE* src, unsigned int size)
	{
		DWORD oldportect;
		VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldportect);
		memcpy(dst, src, size);
		VirtualProtect(dst, size, oldportect, &oldportect);
	}

	void nopMem(BYTE* dst, unsigned int size)
	{
		DWORD oldportect;
		VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldportect);
		memset(dst, 0x90, size);
		VirtualProtect(dst, size, oldportect, &oldportect);
	}

	uintptr_t findDMAaddyMem(uintptr_t ptr, std::vector<unsigned int> offsets)
	{
		uintptr_t addr = ptr;
		for (unsigned int i = 0; i < offsets.size(); ++i)
		{
			addr = *(uintptr_t*)addr;
			addr += offsets[i];
		}
		return addr;
	}

	// hooking
	bool detour32(BYTE* src, BYTE* dst, const uintptr_t len)
	{
		if (len < 5)
		{
			std::cout << "[*] Hooking error: hook length is too small for function!" << std::endl;
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

	BYTE* trampHook32(BYTE* src, BYTE* dst, const uintptr_t len)
	{
		if (len < 5)
		{
			std::cout << "[*] TrampHook32 error: hook length is too small for function!" << std::endl;
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

	// utils:helpful
	std::string getExePath()
	{
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		if (pos == std::string::npos) { return ""; }
		else { return std::string(buffer).substr(0, pos); }
	}
}