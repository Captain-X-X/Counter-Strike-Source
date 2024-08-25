#include "pch.h"
#include "Hacks.h"
#include "CSS.h"
#include "Draw.h"
extern bool menu_open;
eList* elist = nullptr;
ent* localEnt = nullptr;
viewAngles* vAngles = nullptr;
namespace Hacks
{
	bool bBHop = false;
	void Initilize()
	{
	}

	void Update()
	{
		if (!ClientLocalEntity)
			return;
		if ((eList*)(ClientEntList) == nullptr)
		{
			return;
		}
		elist = CounterStrikeSourceSE::getEntityList();
		localEnt = elist->clients[0].entPtr;
		vAngles = CounterStrikeSourceSE::getViewAngles();

		Aimbot::doAimbot();

		if (bBHop)
		{
			if (GetAsyncKeyState(VK_SPACE))
			{
				if (*(int*)ClientAir == 0)
				{
					*(int*)ClientJump = 5;
					Sleep(10);
					*(int*)ClientJump = 4;
				}
			}
		}
	}

	void Draw(IDirect3DDevice9* pDevice/* we take the D3D9 device for rendering esp.. if ever i find that stoopid entlist*/)
	{
		ESP::ESP(pDevice); // soon this will draw esp: boxes, snap lines, bones, information about the player. also this draws the crosshar.
	}

	void Shutdown()
	{
		CounterStrikeSourceSE::testPrint("Unloading cheat/hacks class vars & pointers!");
		menu_open = false;
		ESP::bCrosshair = false;
		Sleep(900); // 
	}
}