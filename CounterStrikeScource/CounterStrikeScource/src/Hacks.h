#pragma once
#include "AImbot.h"
#include "ESP.h"
namespace Hacks
{
	extern bool bBHop;
	void Initilize();
	void Update();
	void Draw(IDirect3DDevice9* pDevice);
	void Shutdown();
}
