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
	uintptr_t findDMAaddyMem(uintptr_t ptr, std::vector<unsigned int> offsets);
	// utils:helpful
	std::string getExePath(); //<-- this get the path of the current exe. works for .exe's and DLL's. fucking amazing ayy? I cant link where i got this function but it was on stackoverflow.
}