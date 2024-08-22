#pragma once
#include "CSS_offsets.h"
namespace CounterStrikeSourceSE
{
	ent* getLocalEnt();
	ent* getLocalEntServer();

	bool isEntValid(ent* eEnt);
	bool isOnTeam(ent* eEnt);
	bool worldToScreen(m_Vector3 position, m_Vector2& screen, float vMatrix[16], int wWidth, int wHeight);

	void dumpEntitys();
}