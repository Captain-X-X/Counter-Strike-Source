#pragma once
#include "Vector.h"
#include <d3dx9.h>
namespace ESP
{
	extern bool bESP;
	extern bool bCrosshair;
	extern m_Vector3 tColour;
	extern m_Vector3 ctColour;

	void ESP(IDirect3DDevice9* pDevice);
}
