#include "ESP.h"
#include "Draw.h"
extern int winWidth;
extern int winHeight;
extern bool menu_open;
namespace ESP
{
	bool bESP = false;
	bool bCrosshair;
	//m_Vector3 tColour=m_Vector3(255, 0, 0);
	//m_Vector3 ctColour = m_Vector3(0, 0, 255);

	void ESP(IDirect3DDevice9* pDevice)
	{
		//if (menu_open)
		//{
		//	DX9Draw::drawRect(0, 0, 100, 100, D3DCOLOR_ARGB(255, (int)tColour.x, (int)tColour.y, (int)tColour.z), pDevice);
		//	DX9Draw::drawRect(100, 0, 100, 100, D3DCOLOR_ARGB(255, (int)ctColour.x, (int)ctColour.y, (int)ctColour.z), pDevice);
		//}
		if (bCrosshair)
		{
			if (!menu_open)
			{
				DX9Draw::drawRect(winWidth / 2, (winHeight / 2) - 10, 2.0f, 20, D3DCOLOR_ARGB(255, 255, 0, 255), pDevice); // left - right
				DX9Draw::drawRect((winWidth / 2) - 10, winHeight / 2, 20, 2.0f, D3DCOLOR_ARGB(255, 255, 0, 255), pDevice); // top - bottom
			}
		}
	}
}