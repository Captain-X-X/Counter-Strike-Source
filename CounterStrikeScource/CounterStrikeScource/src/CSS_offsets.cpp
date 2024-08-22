#include "pch.h"
#include "CSS_offsets.h"

DWORD ClientJump = ClientDLL + 0x4F5D24; // [<client.dll>+4F5D24]
DWORD ClientAir = ClientDLL + 0x4A4078; // [<client.dll>+4A4078]
DWORD ClientShoot = ClientDLL + 0x4F5D30; // [<client.dll>+4F5D30]
DWORD ClientLocalEntPtr = ClientDLL + 0x4C88E8; // [<client.dll>+4C88E8]
DWORD ClientEntList = ClientDLL + 0x4D5AE0; // [<client.dll>+4D5AE0]
DWORD ClientViewAngles = ClientDLL + 0x0C16D0; // [<engine.dll>+C16D0]
DWORD EngineNumberOfPlayers = EngineDLL + 0x4F2150; // [<client.dll>+4F2150]  <-- this is not working now, going to fix soon.