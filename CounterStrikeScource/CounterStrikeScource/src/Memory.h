/*
	this is a simple class for assaultcube
	  AssaultCube Version 1.2.0.2
	created by: captain_x-X#2181
	https://github.com/Captain-X-X
*/
#pragma once
#include "pch.h"

namespace Memory
{
	// memory:modification  
	void patchMem(BYTE* dst, BYTE* src, unsigned int size);
	void nopMem(BYTE* dst, unsigned int size);
	uintptr_t findDMAaddyMem(uintptr_t ptr, std::vector<unsigned int > offsets);

	// memory:hooking
	bool detour32(BYTE* src, BYTE* dst, const uintptr_t len);
	BYTE* trampHook32(BYTE* src, BYTE* dst, const uintptr_t len);

	// utils:helpful
	std::string getExePath();
}