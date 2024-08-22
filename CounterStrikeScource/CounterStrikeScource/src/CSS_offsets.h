#pragma once
#include "pch.h"

/*  reclass redefinitions for local project types*/
#define int32_t int
#define vec3 m_Vector3
#define vec2 m_Vector2
#define Vector3 m_Vector3
#define Vector2 m_Vector2
#define Matrix4x4 float

/* base handles/addresses */
#define GameBase  (uintptr_t)GetModuleHandle(NULL)
#define ServerDLL (uintptr_t)GetModuleHandle("server.dll")
#define EngineDLL (uintptr_t)GetModuleHandle("engine.dll")
#define ClientDLL (uintptr_t)GetModuleHandle("client.dll")

/* game/engine/server addresses for classes and functions */
extern DWORD ClientJump; // [<client.dll>+4F5D24]
extern DWORD ClientAir; // [<client.dll>+4A4078]
extern DWORD ClientShoot; // [<client.dll>+4F5D30]
extern DWORD ClientLocalEntPtr; // [<client.dll>+4C88E8]
extern DWORD ClientEntList; // [<client.dll>+4D5AE0]
extern DWORD ClientViewAngles; // [<engine.dll>+C16D0]
extern DWORD EngineNumberOfPlayers; // [<client.dll>+4F2150]  <-- this is not working now, going to fix soon.

/* just engine things */
#define MaxEntsInList 64 // this is for ent list scanning, all addresses i have found so far only have world ents + ourself...
#define LocalPlayerOffsetInEntList 0
#define TeamT 2
#define TeamCT 3

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

class ent
{
public:
	char pad_0000[24]; //0x0000
	int32_t N00002717; //0x0018
	char pad_001C[4]; //0x001C
	int32_t N00002719; //0x0020
	char pad_0024[4]; //0x0024
	int32_t N0000271B; //0x0028
	char pad_002C[104]; //0x002C
	int32_t health; //0x0094
	char pad_0098[4]; //0x0098
	int32_t teamNumber; //0x009C
	char pad_00A0[216]; //0x00A0
	int32_t N00002B93; //0x0178
	char pad_017C[228]; //0x017C
	Vector3 position1; //0x0260
	Vector2 viewAngles; //0x026C
	char pad_0274[4]; //0x0274
	Vector3 position2; //0x0278
	char pad_0284[12]; //0x0284
	Vector3 positionOrigin; //0x0290
	char pad_029C[4692]; //0x029C
	int32_t crosshairId; //0x14F0
}; //Size: 0x14F4

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

class viewAngles
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