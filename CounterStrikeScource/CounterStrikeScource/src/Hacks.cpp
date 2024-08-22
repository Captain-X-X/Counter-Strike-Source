#include "pch.h"
#include "Hacks.h"
#include "CSS.h"
#include "Draw.h"
extern int winWidth;
extern int winHeight;
extern bool menu_open;

bool bShot = false;
namespace Hacks
{
	bool bBHop = false;
	bool bTriggerbot = false;
	void Initilize()
	{
	}

	void Update()
	{
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

		if (bTriggerbot) // maybe dont make your triggerbot like this... its killing me facking fps
		{
			eList* elist = *(eList**)(ClientEntList);
			if (CounterStrikeSourceSE::getLocalEntServer()->crosshairId == 0)
				return;

			int cId;
			cId = elist->clients[0].entPtr->crosshairId;
			int tId = elist->clients[0].entPtr->teamNumber;
			if (CounterStrikeSourceSE::isEntValid(elist->clients[cId - 1].entPtr))
			{
				if (elist->clients[cId - 1].entPtr->teamNumber != tId)
				{
					if (!bShot)
					{
						*(int*)(ClientShoot) = 5;
						bShot = true;
					}
					else
					{
						*(int*)(ClientShoot) = 4;
						bShot = false;
					}
				}
			}
			else
				return;
		}
	}

	void Draw(IDirect3DDevice9* pDevice/* we take the D3D9 device for rendering esp.. if ever i find that stoopid entlist*/)
	{

	}

	void Shutdown()
	{
		menu_open = false;
	}
}