#pragma once
#ifdef _WIN32

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

	this was made so i dont have to use MinHook or Detour32 by MS.

*/

// presets for common functions that are hooked
#define OGL_HOOK_LENGTH 5
#define DX9ES_HOOK_LENGTH 7 // D3D9 EndScene() hook length
#define DX9RS_HOOK_LENGTH 5 // D3D9 Reset() hook length
#define DX9ES_HOOK_VTI 42 // D3D9 EndScene() VTable function index
#define DX9RS_HOOK_VTI 16 // D3D9 Reset() VTable function index
#define DX11P_HOOK_LENGTH 7
#define DX11P_HOOK_VTI 8
class SEDetour
{
private:
    bool bStatus{ false };
    BYTE* src{ nullptr };
    BYTE* dst{ nullptr };
    BYTE* PtrToGatewayFnPtr{ nullptr };
    uintptr_t len{ 0 };
    BYTE originalBytes[10]{ 0 };
    // functions
    bool detour32(BYTE* src, BYTE* dst, const uintptr_t len);
    BYTE* trampHook32(BYTE* src, BYTE* dst, const uintptr_t len);
public:
    SEDetour();
    SEDetour(BYTE* src, BYTE* dst, BYTE* PtrToGatewayFnPtr, uintptr_t len);
    SEDetour(const char* exportName, const char* modName, BYTE* dst, BYTE* PtrToGatewayFnPtr, uintptr_t len);

    bool SetHook(BYTE* src, BYTE* dst, BYTE* PtrToGatewayFnPtr, uintptr_t len);
    void Enable();
    void Disable();
};
// DirectX helper functions
constexpr void* DXVTableFunction(void* thisptr, size_t index); // this gets the DX function address based on an offset passed by you.
#endif // _WIN32

namespace SEHooks
{
	void InitilizeHooks();
	void DisableHooks();
}
