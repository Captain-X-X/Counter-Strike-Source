#include "pch.h"
#include "CSS_offsets.h"

DWORD ClientPrintAddress = (DWORD)GetProcAddress((HMODULE)Tier0DLL, "Msg");
DWORD ClientJump = ClientDLL + 0x4F5D24; // [<client.dll>+4F5D24]
DWORD ClientAir = ClientDLL + 0x4A4078; // [<client.dll>+4A4078]
DWORD ClientDuck = ClientDLL + 0x4F5D60; // client.dll+4F5D60
DWORD ClientName = ClientDLL + 0x623A71; // engine.dll+623A71
DWORD ClientSpectatingName = ClientDLL + 0x4D4DA0; // client.dll+4D4DA0
DWORD ClientShoot = ClientDLL + 0x4F5D30; // [<client.dll>+4F5D30]
DWORD ClientLocalEntPtr = ClientDLL + 0x4C88E8; // [<client.dll>+4C88E8]
DWORD ClientEntList = ClientDLL + 0x4D5AE0; // [<client.dll>+4D5AE0]
DWORD ClientLocalEntity = ClientDLL + 0x4E5B14; // [<client.dll>+004E5B14]
DWORD ClientViewAngles = EngineDLL + 0xA806C; // [<engine.dll>+C16D0]
DWORD ServerNumberOfPlayers = ServerDLL + 0x4F2150; // [<server.dll>+4F2150]

DWORD EngineWindowWidth = EngineDLL + 0x3C3254; // engine.dll+3C3254 
DWORD EngineWindowHeight = EngineDLL + 0x3C3258; // engine.dll+3C3258

// reversed engine/client/tier0.dll function type defs
_csPrintf csPrint = (_csPrintf)(ClientPrintAddress);