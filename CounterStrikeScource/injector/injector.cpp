/*
	created by: captain_X-X#2181
				https://github.com/Captain-X-X
*/
#include <windows.h>
#include <iostream>
#include <TlHelp32.h>
// helper
std::string getExePath()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	if (pos == std::string::npos) { return ""; }
	else { return std::string(buffer).substr(0, pos); }
}

// Injector
DWORD GetProcessId(const char* ProcessName) 
{
	DWORD ProcessId = 0;
	HANDLE HSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	// Logic
	if (HSnap != INVALID_HANDLE_VALUE) 
	{
		PROCESSENTRY32 ProcessEntry;
		ProcessEntry.dwSize = sizeof(ProcessEntry);
		// Logic 2
		if (Process32First(HSnap, &ProcessEntry)) 
		{
			do {
				if (!_stricmp(ProcessEntry.szExeFile, ProcessName)) 
				{
					ProcessId = ProcessEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(HSnap, &ProcessEntry));
		}
	}
	CloseHandle(HSnap);
	return ProcessId;
}
int main() 
{
	std::string DllPath = getExePath() + "\\CounterStrikeScource.dll";
	std::string ProcessN = "hl2.exe";
	printf("Finding process...\n");
	// Find Process/Open process 
	DWORD ProcessId = 0;
	while (!ProcessId) 
	{
		ProcessId = GetProcessId(ProcessN.c_str());
		Sleep(50);
	}
	printf("Found process[%lu]...\n", ProcessId);
	HANDLE HProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, ProcessId);
	if (HProcess && HProcess != INVALID_HANDLE_VALUE) 
	{
		void* Loc = VirtualAllocEx(HProcess, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		// Inject dll.
		WriteProcessMemory(HProcess, Loc, DllPath.c_str(), strlen(DllPath.c_str()) + 0, 0);
		HANDLE HThread = CreateRemoteThread(HProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, Loc, 0, 0);
		// Close Handle DUUH
		if (HThread) CloseHandle(HThread);
	}
	// Close Handle DUUH
	if (HProcess) CloseHandle(HProcess), std::cout << "Dll Injected!";
	return 0;
}