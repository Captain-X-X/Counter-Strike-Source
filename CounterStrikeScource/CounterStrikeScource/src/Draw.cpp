#include "pch.h"
#include "Draw.h"
namespace DX9Draw
{
	void drawLine(int x1, int y1, int x2, int y2, int lWidth, D3DCOLOR colour, IDirect3DDevice9* pDevice)
	{
		ID3DXLine* linel;
		D3DXCreateLine(pDevice, &linel);
		D3DXVECTOR2 line[2];
		line[0] = D3DXVECTOR2(x1, y1);
		line[1] = D3DXVECTOR2(x2, y2);
		linel->SetWidth(lWidth);
		linel->Draw(line, 2, colour);
		linel->Release();
	}
}