#include "pch.h"
#include "AImbot.h"
#include "CSS.h"
using namespace CounterStrikeSourceSE;
extern viewAngles* vAngles;
extern eList* elist;
extern ent* localEnt;
ent* target = nullptr;
m_Vector3 aimAngles;
//float aimSmoother = 0.0f;
bool bShot = false; // this id for the triggerbot hack
namespace Aimbot // this is jank as fuck, need to be improved soon as!!
{
	bool bAimbot = false;
	bool bAutoShoot = false;

	void doAimbot()
	{
		localEnt = elist->clients[0].entPtr;
		target = nullptr;
		if (bAutoShoot)
		{
			int cId;
			cId = elist->clients[0].entPtr->crosshairId;
			if (cId == 0) // this fix was easy as fuck man...
				return;

			int tId = elist->clients[0].entPtr->teamNumber;
			if (elist->clients[0].entPtr->crosshairId != 0)
			{
				if (CounterStrikeSourceSE::isEntValid(elist->clients[cId - 1].entPtr))
				{
					if (elist->clients[cId - 1].entPtr->teamNumber != tId)
					{
						Sleep(10);
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
					if (cId == 0)
						*(int*)(ClientShoot) = 4;
				}
				else
				{
					bShot = true;
					cId = 0;
					return;
				}
			}
		}
		if (bAimbot)
		{
			if (GetAsyncKeyState(VK_SHIFT))
			{
				float oDist = FLT_MAX;
				float nDist = 0;
				target = nullptr;
				for (int i = 0; i < MaxEntsInList; i++)
				{
					if (isEntValid(elist->clients[i].entPtr))
					{
						if (!isOnTeam(elist->clients[i].entPtr))
						{
							if (elist->clients[i].entPtr->health < 2)
								continue;

							nDist = get3DDistance(elist->clients[0].entPtr->position, elist->clients[i].entPtr->position);
							if (nDist < oDist)
							{
								oDist = nDist;
								target = elist->clients[i].entPtr;
							}
						}
					}
				}
				if (target != nullptr)
				{
					vAngles->viewAngles = maths.calcAngles(getLocalEntServer()->position, target->position);
				}
			}
		}
	}
}