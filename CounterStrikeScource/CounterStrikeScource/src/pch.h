#ifndef PCH_H
#define PCH_H
// add headers that you want to pre-compile here
#include "framework.h"
// system
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <thread>
#include <stdexcept>
// lib
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
// extern libs
#include <MinHook/include/MinHook.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx9.h>
// local project
#include "Vector.h"
#endif //PCH_H