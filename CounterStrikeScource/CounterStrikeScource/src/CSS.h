/*

	this was created by captain_xx on Discord & https://github.com/Captain-X-X on GitHub
		all my code is uploaded there under the 'Unlicense license' wich is as described:
		"
			This is free and unencumbered software released into the public domain.

			Anyone is free to copy, modify, publish, use, compile, sell, or
			distribute this software, either in source code form or as a compiled
			binary, for any purpose, commercial or non-commercial, and by any
			means.

			In jurisdictions that recognize copyright laws, the author or authors
			of this software dedicate any and all copyright interest in the
			software to the public domain. We make this dedication for the benefit
			of the public at large and to the detriment of our heirs and
			successors. We intend this dedication to be an overt act of
			relinquishment in perpetuity of all present and future rights to this
			software under copyright law.

			THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
			EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
			MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
			IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
			OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
			ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
			OTHER DEALINGS IN THE SOFTWARE.

			For more information, please refer to <https://unlicense.org>
		"
	enjoy skids and children.. nya :3

	al of these functions were coded by me for the purpose of an easy cheat sdk.
		if you find bugs or have an optimization idea you would like to add, just added it yourself and tell me on GitHub:
			https://github.com/Captain-X-X

	this will be updated and changed, not often or as often as not. if i can be bothered too.. I will. if not? youre out of luck i suppose :3

*/

#pragma once
#include "CSS_offsets.h"
namespace CounterStrikeSourceSE
{
	ent* getLocalEnt();
	ent* getLocalEntServer();
	eList* getEntityList();
	viewAngles* getViewAngles();
	int getNumberOfPlayersAlive();

	void testPrint(const char* text, ...);

	bool isEntValid(ent* eEnt);
	bool isOnTeam(ent* eEnt);
	bool worldToScreen(m_Vector3 position, m_Vector2& screen, float vMatrix[16], int wWidth, int wHeight);

	void dumpEntitys(); // this is for testing the entity list.

	float get3DDistance(m_Vector3 position, m_Vector3 position_ent);
}