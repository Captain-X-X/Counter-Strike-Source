#include "pch.h"
#include "Draw.h"
namespace DX9Draw
{
	void drawLine(float x1, float y1, float x2, float y2, float lWidth, D3DCOLOR colour, IDirect3DDevice9* pDevice)
	{
		ID3DXLine* linel;
		D3DXCreateLine(pDevice, &linel);
		D3DXVECTOR2 line[2];
		line[0] = D3DXVECTOR2(x1, y1);
		line[1] = D3DXVECTOR2(x2, y2);
		linel->SetWidth(lWidth); // set the width of the lise to be drawn
		linel->Draw(line, 2, colour); // draw our verts
		linel->Release(); // cleanup
	}
	void drawRect(float x, float y, float w, float h, D3DCOLOR colour, IDirect3DDevice9* pDevice)
	{
		// setup dxdraw
		ID3DXLine* linel;
		D3DXCreateLine(pDevice, &linel);

		// create D3D9 vertices
		D3DXVECTOR2 vertices[2];
		vertices[0] = D3DXVECTOR2(x + w / 2, y);
		vertices[1] = D3DXVECTOR2(x + w / 2, y + h);

		// start the rasterisation
		linel->SetWidth(w); // set the width of the lise to be drawn
		linel->Draw(vertices, 2, colour); // draw our verts
		linel->Release(); // cleanup
	}
}