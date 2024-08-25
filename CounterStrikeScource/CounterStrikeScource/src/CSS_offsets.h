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

	anything described with ' [<DLLName.dll>+000000] ' has been reversed with ReClass
	and anything described with ' engine.dll+000000 ' has been reversed with CheatEngine

*/


#pragma once
#include "pch.h"

/*  reclass redefinitions for local project types*/
#define int32_t int
#define vec3 m_Vector3
#define vec2 m_Vector2
#define Vector3 m_Vector3
#define Vector2 m_Vector2
#define Vector4 m_Vector4
#define Matrix4x4 float

/* base handles/addresses */
#define GameBase  (uintptr_t)GetModuleHandle(NULL)
#define ServerDLL (uintptr_t)GetModuleHandle("server.dll")
#define EngineDLL (uintptr_t)GetModuleHandle("engine.dll")
#define ClientDLL (uintptr_t)GetModuleHandle("client.dll")
#define Tier0DLL  (uintptr_t)GetModuleHandle("tier0.dll")

/* game/engine/server addresses for classes and functions */
extern DWORD ClientJump; // [<client.dll>+4F5D24]
extern DWORD ClientAir; // [<client.dll>+4A4078]
extern DWORD ClientShoot; // [<client.dll>+4F5D30]
extern DWORD ClientLocalEntPtr; // [<client.dll>+4C88E8]
extern DWORD ClientEntList; // [<client.dll>+4D5AE0]
extern DWORD ClientLocalEntity; // [<client.dll>+004E5B14]
extern DWORD ClientViewAngles; // [<engine.dll>+C16D0]
extern DWORD ServerNumberOfPlayers; // [<server.dll>+4F2150].
extern DWORD ClientPrintAddress; // <-- tier0.dll
extern DWORD EngineWindowWidth; // engine.dll+3C3254
extern DWORD EngineWindowHeight; // engine.dll+3C3258

// reversed engine/client/tier0.dll function type defs
typedef void(__cdecl* _csPrintf)(char* Format, ...);
extern _csPrintf csPrint;

/* just engine things */
#define MaxEntsInList 64 // this is for ent list scanning, all addresses i have found so far only have world ents + ourself...
#define LocalPlayerOffsetInEntList 0
#define TeamT 2
#define TeamCT 3

#define Movement_Still 0
#define Movement_Forward 8
#define Movement_Backward 16
#define Movement_Left 512
#define Movement_Right 1024

/* reversed classes & structs from reclass/cheat engine */
class localEnt // [<client.dll>+4C88E8]
{
public:
	char pad_0000[148]; //0x0000
	int32_t health; //0x0094
	char pad_0098[4]; //0x0098
	int32_t teamNum; //0x009C
	char pad_00A0[448]; //0x00A0
	m_Vector3 N000000E7; //0x0260
	m_Vector2 N000000E8; //0x026C read only
	char pad_0274[4]; //0x0274
	m_Vector3 N000000EA; //0x0278
	char pad_0284[4]; //0x0284
	float N000000EC; //0x0288
	char pad_028C[4]; //0x028C
	m_Vector3 N000000EE; //0x0290
	char pad_029C[64]; //0x029C
	m_Vector2 N000000FF; //0x02DC read only
	char pad_02E4[52]; //0x02E4
	Matrix4x4 N0000010D; //0x0318
}; //Size: 0x0358

// Created with ReClass.NET 1.2 by KN4CK3R

class clientInfo
{
public:
	class ent* entPtr; //0x0000
	int32_t N000026DC; //0x0004
	class clientInfo* bLink; //0x0008
	class clientInfo* fLink; //0x000C
}; //Size: 0x0010

//class ent
//{
//public:
//	char pad_0000[24]; //0x0000
//	int32_t N00002717; //0x0018
//	char pad_001C[4]; //0x001C
//	int32_t N00002719; //0x0020
//	char pad_0024[4]; //0x0024
//	int32_t N0000271B; //0x0028
//	char pad_002C[104]; //0x002C
//	int32_t health; //0x0094
//	char pad_0098[4]; //0x0098
//	int32_t teamNumber; //0x009C
//	char pad_00A0[216]; //0x00A0
//	int32_t N00002B93; //0x0178
//	char pad_017C[228]; //0x017C
//	Vector3 position1; //0x0260
//	Vector2 viewAngles; //0x026C
//	char pad_0274[4]; //0x0274
//	Vector3 position2; //0x0278
//	char pad_0284[12]; //0x0284
//	Vector3 positionOrigin; //0x0290
//	char pad_029C[4692]; //0x029C
//	int32_t crosshairId; //0x14F0
//}; //Size: 0x14F4

class ent
{
public:
	void* N00002711; //0x0000
	void* N00002712; //0x0004
	void* N00002713; //0x0008
	void* N00002714; //0x000C
	char pad_0010[4]; //0x0010
	void* N00002716; //0x0014
	int32_t N00002717; //0x0018
	char pad_001C[4]; //0x001C
	int32_t N00002719; //0x0020
	void* N0000271A; //0x0024
	int32_t N0000271B; //0x0028
	float N0000597A; //0x002C
	char pad_0030[36]; //0x0030
	int32_t N00002836; //0x0054
	char pad_0058[12]; //0x0058
	Vector4 N0000283A; //0x0064
	char pad_0074[16]; //0x0074
	int32_t N0000283F; //0x0084
	char pad_0088[4]; //0x0088
	int32_t maxHealth; //0x008C
	char pad_0090[4]; //0x0090
	int32_t health; //0x0094
	char pad_0098[4]; //0x0098
	int32_t teamNumber; //0x009C
	char pad_00A0[20]; //0x00A0
	int32_t N00002B5F; //0x00B4
	char pad_00B8[8]; //0x00B8
	int32_t N00002B62; //0x00C0
	char pad_00C4[4]; //0x00C4
	int32_t N00002B64; //0x00C8
	char pad_00CC[36]; //0x00CC
	float heaight; //0x00F0
	Vector3 volocity; //0x00F4
	char pad_0100[12]; //0x0100
	int32_t N00002B73; //0x010C
	char pad_0110[12]; //0x0110
	int32_t N00002B77; //0x011C
	char pad_0120[16]; //0x0120
	Vector3 N00002B7C; //0x0130
	char pad_013C[152]; //0x013C
	float crouchHeight; //0x01D4
	char pad_01D8[136]; //0x01D8
	Vector3 position; //0x0260
	Vector3 viewAngles1; //0x026C
	Vector3 N00002BC6; //0x0278
	char pad_0284[12]; //0x0284
	Vector3 position2; //0x0290
	char pad_029C[108]; //0x029C
	float N00005FAD; //0x0308
	float N00005FAE; //0x030C
	float N00005FAF; //0x0310
	float N00005FB0; //0x0314
	float N00005FB1; //0x0318
	float N00005FB2; //0x031C
	float N00005FB3; //0x0320
	float N00005FB4; //0x0324
	float N00005FB5; //0x0328
	char pad_032C[4]; //0x032C
	float N00005FB7; //0x0330
	float N00005FB8; //0x0334
	float N00005FB9; //0x0338
	float N00005FBA; //0x033C
	float N00005FBB; //0x0340
	float N00005FBC; //0x0344
	float N00005FBD; //0x0348
	char pad_034C[4]; //0x034C
	int32_t heights; //0x0350
	int32_t N00005FC0; //0x0354
	void* N00005FC1; //0x0358
	void* N00005FC2; //0x035C
	void* N00005FC3; //0x0360
	void* N00005FC4; //0x0364
	void* vMatrix; //0x0368
	void* N000063B5; //0x036C
	void* N000063B6; //0x0370
	void* N000063B7; //0x0374
	void* N000063B8; //0x0378
	void* N000063B9; //0x037C
	void* N000063BA; //0x0380
	void* N000063BB; //0x0384
	void* N000063BC; //0x0388
	void* N000063BD; //0x038C
	void* N000063BE; //0x0390
	void* N000063BF; //0x0394
	void* N000063C0; //0x0398
	void* N000063C1; //0x039C
	void* N000063C2; //0x03A0
	void* N000063C3; //0x03A4
	void* N000063C4; //0x03A8
	void* N00005FC6; //0x03AC
	void* N00005FC7; //0x03B0
	void* N00005FC8; //0x03B4
	void* N00005FC9; //0x03B8
	void* N00000673; //0x03BC
	void* N00000674; //0x03C0
	void* N00000675; //0x03C4
	void* N00000676; //0x03C8
	void* N00000677; //0x03CC
	void* N00000678; //0x03D0
	void* N00000679; //0x03D4
	void* N0000067A; //0x03D8
	void* N0000067B; //0x03DC
	void* N0000067C; //0x03E0
	void* N0000067D; //0x03E4
	void* N0000067E; //0x03E8
	void* N0000067F; //0x03EC
	void* N00000680; //0x03F0
	void* N00000681; //0x03F4
	void* N00000682; //0x03F8
	void* N00000683; //0x03FC
	void* N00000684; //0x0400
	void* N00000685; //0x0404
	void* N00000686; //0x0408
	void* N00000687; //0x040C
	void* N00000688; //0x0410
	void* N00000689; //0x0414
	void* N0000068A; //0x0418
	void* N0000068B; //0x041C
	void* N0000068C; //0x0420
	void* N0000068D; //0x0424
	void* N0000068E; //0x0428
	void* N0000068F; //0x042C
	void* N00000690; //0x0430
	void* N00000691; //0x0434
	void* N00000692; //0x0438
	void* N00000693; //0x043C
	void* N00000694; //0x0440
	void* N00000695; //0x0444
	void* N00000696; //0x0448
	void* N00000697; //0x044C
	void* N00000698; //0x0450
	void* N00000699; //0x0454
	void* N0000069A; //0x0458
	void* N0000069B; //0x045C
	void* N0000069C; //0x0460
	void* N0000069D; //0x0464
	void* N0000069E; //0x0468
	void* N0000069F; //0x046C
	void* N000006A0; //0x0470
	void* N000006A1; //0x0474
	void* N000006A2; //0x0478
	void* N000006A3; //0x047C
	void* N000006A4; //0x0480
	void* N000006A5; //0x0484
	void* N000006A6; //0x0488
	void* N000006A7; //0x048C
	void* N000006A8; //0x0490
	void* N000006A9; //0x0494
	void* N000006AA; //0x0498
	void* N000006AB; //0x049C
	void* N000006AC; //0x04A0
	void* N000006AD; //0x04A4
	void* N000006AE; //0x04A8
	void* N000006AF; //0x04AC
	void* N000006B0; //0x04B0
	void* N000006B1; //0x04B4
	void* N000006B2; //0x04B8
	void* N000006B3; //0x04BC
	void* N000006B4; //0x04C0
	int32_t N000006B5; //0x04C4
	char pad_04C8[32]; //0x04C8
	int32_t N000006BE; //0x04E8
	char pad_04EC[68]; //0x04EC
	int32_t N000006D0; //0x0530
	char pad_0534[4]; //0x0534
	int32_t N000006D2; //0x0538
	char pad_053C[472]; //0x053C
	int32_t N00000749; //0x0714
	char pad_0718[120]; //0x0718
	int32_t N00000768; //0x0790
	int32_t N00000769; //0x0794
	int32_t N0000076A; //0x0798
	int32_t N0000076B; //0x079C
	char pad_07A0[32]; //0x07A0
	int32_t N00000774; //0x07C0
	char pad_07C4[80]; //0x07C4
	int32_t N00000789; //0x0814
	char pad_0818[4]; //0x0818
	int32_t N0000078B; //0x081C
	char pad_0820[20]; //0x0820
	int32_t N00000791; //0x0834
	char pad_0838[4]; //0x0838
	int32_t N00000793; //0x083C
	char pad_0840[20]; //0x0840
	int32_t N00000799; //0x0854
	char pad_0858[4]; //0x0858
	int32_t N0000079B; //0x085C
	char pad_0860[20]; //0x0860
	int32_t N000007A1; //0x0874
	char pad_0878[4]; //0x0878
	int32_t N000007A3; //0x087C
	char pad_0880[128]; //0x0880
	float N000007C4; //0x0900
	int32_t N000007C5; //0x0904
	char pad_0908[424]; //0x0908
	float N00000830; //0x0AB0
	int32_t N00000831; //0x0AB4
	char pad_0AB8[140]; //0x0AB8
	int32_t N00000855; //0x0B44
	char pad_0B48[132]; //0x0B48
	int32_t N00000877; //0x0BCC
	char pad_0BD0[112]; //0x0BD0
	int32_t N00000890; //0x0C40
	char pad_0C44[64]; //0x0C44
	int32_t N000008A1; //0x0C84
	char pad_0C88[276]; //0x0C88
	int32_t N000008E7; //0x0D9C
	char pad_0DA0[20]; //0x0DA0
	int32_t N000008ED; //0x0DB4
	char pad_0DB8[12]; //0x0DB8
	int32_t N000008F1; //0x0DC4
	char pad_0DC8[12]; //0x0DC8
	int32_t N000008F5; //0x0DD4
	char pad_0DD8[72]; //0x0DD8
	int32_t isCrouching; //0x0E20 if>0 you are crouching
	char pad_0E24[20]; //0x0E24
	int32_t movementState; //0x0E38
	char pad_0E3C[56]; //0x0E3C
	int32_t N0000091C; //0x0E74
	char pad_0E78[8]; //0x0E78
	int32_t N0000091F; //0x0E80
	char pad_0E84[4]; //0x0E84
	int32_t N00000921; //0x0E88
	char pad_0E8C[36]; //0x0E8C
	int32_t N0000092B; //0x0EB0
	int32_t N0000092C; //0x0EB4
	char pad_0EB8[4]; //0x0EB8
	int32_t N0000092E; //0x0EBC
	char pad_0EC0[4]; //0x0EC0
	int32_t N00000930; //0x0EC4
	char pad_0EC8[8]; //0x0EC8
	int32_t N00000933; //0x0ED0
	char pad_0ED4[20]; //0x0ED4
	int32_t N00000939; //0x0EE8
	char pad_0EEC[8]; //0x0EEC
	int32_t N0000093C; //0x0EF4
	char pad_0EF8[28]; //0x0EF8
	int32_t N00000944; //0x0F14
	char pad_0F18[4]; //0x0F18
	int32_t N00000946; //0x0F1C
	char pad_0F20[12]; //0x0F20
	int32_t N0000094A; //0x0F2C
	char pad_0F30[12]; //0x0F30
	int32_t N0000094E; //0x0F3C
	char pad_0F40[140]; //0x0F40
	int32_t N00000972; //0x0FCC
	char pad_0FD0[8]; //0x0FD0
	int32_t N00000975; //0x0FD8
	char pad_0FDC[48]; //0x0FDC
	int32_t N00000982; //0x100C
	char pad_1010[8]; //0x1010
	int32_t N00000985; //0x1018
	char pad_101C[264]; //0x101C
	float height; //0x1124
	char pad_1128[868]; //0x1128
	int32_t money; //0x148C
	int32_t hasArmor; //0x1490
	int32_t skinId; //0x1494
	int32_t armor; //0x1498
	Vector3 N000012C5; //0x149C
	char pad_14A8[72]; //0x14A8
	int32_t crosshairId; //0x14F0
	char pad_14F4[12]; //0x14F4
}; //Size: 0x1500

class eList
{
public:
	class clientInfo clients[64]; //0x0000
}; //Size: 0x0400

class eListAddr
{
public:
	char pad_0000[2112]; //0x0000
}; //Size: 0x0840

class fviewAngles
{
public:
	Vector2 N00005978; //0x0000
	char pad_0008[132]; //0x0008
	int32_t screenX; //0x008C
	int32_t vpX; //0x0090
	int32_t vpY; //0x0094
	int32_t N00005BE6; //0x0098
	int32_t screenY; //0x009C
	char pad_00A0[20]; //0x00A0
	float fov; //0x00B4
	char pad_00B8[836]; //0x00B8
	float ffov; //0x03FC
	char pad_0400[4]; //0x0400
	Matrix4x4 vMatrix1; //0x0404
	char pad_0444[96]; //0x0444
}; //Size: 0x04A4

class viewAngles
{
public:
	char pad_0000[92]; //0x0000
	Vector3 viewAngles; //0x005C
	char pad_0068[1232]; //0x0068
}; //Size: 0x0538

class gameWindow // this was made for the ease of use of this little cheat sdk.
{
public:
	int* winWidth = *(int**)(EngineWindowWidth);
	int* winHeight = *(int**)(EngineWindowHeight);
};