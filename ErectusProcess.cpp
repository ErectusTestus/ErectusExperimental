#include "ErectusInclude.h"

int ProcessErrorId = 0;
char *ProcessError = nullptr;
bool ProcessSelected = false;
int ProcessListSize = 0;
int ProcessIndex = 0;
char **ProcessList = nullptr;
DWORD *ProcessIdList = nullptr;
bool ProcessListUpdated = false;
int ProcessValidCounter = 0;
bool ProcessMenuActive = false;

DWORD Pid = 0;
HWND Hwnd = NULL;
DWORD64 Exe = 0;
HANDLE Handle = NULL;

void SetProcessMenu()
{
	if (WindowSize[0] != 384 || WindowSize[1] != 224)
	{
		WindowSize[0] = 384;
		WindowSize[1] = 224;

		if (WindowHwnd != NULL)
		{
			DeviceResetQueued = true;
			SetWindowPos(WindowHwnd, HWND_NOTOPMOST, WindowPosition[0], WindowPosition[1], WindowSize[0], WindowSize[1], 0);
		}
	}

	int BufferPosition[2];
	BufferPosition[0] = (GetSystemMetrics(SM_CXSCREEN) / 2) - (WindowSize[0] / 2);
	BufferPosition[1] = (GetSystemMetrics(SM_CYSCREEN) / 2) - (WindowSize[1] / 2);

	if (WindowPosition[0] != BufferPosition[0] || WindowPosition[1] != BufferPosition[1])
	{
		WindowPosition[0] = BufferPosition[0];
		WindowPosition[1] = BufferPosition[1];

		if (WindowHwnd != NULL)
		{
			MoveWindow(WindowHwnd, WindowPosition[0], WindowPosition[1], WindowSize[0], WindowSize[1], FALSE);
			if (!DeviceResetQueued)
			{
				SetWindowPos(WindowHwnd, HWND_NOTOPMOST, WindowPosition[0], WindowPosition[1], WindowSize[0], WindowSize[1], 0);
			}
		}
	}

	if (WindowHwnd != NULL)
	{
		LONG_PTR Style = GetWindowLongPtr(WindowHwnd, GWL_EXSTYLE);

		if (Style & WS_EX_LAYERED)
		{
			Style &= ~WS_EX_LAYERED;
			SetWindowLongPtr(WindowHwnd, GWL_EXSTYLE, Style);
		}

		if (Style & WS_EX_TOPMOST)
		{
			SetWindowPos(WindowHwnd, HWND_NOTOPMOST, WindowPosition[0], WindowPosition[1], WindowSize[0], WindowSize[1], 0);
		}
	}

	ProcessMenuActive = true;
	OverlayMenuActive = false;
	OverlayActive = false;
}

void SetProcessError(int ErrorId, const char *Error, size_t Length)
{
	if (ProcessError != nullptr)
	{
		delete[]ProcessError;
		ProcessError = nullptr;
	}

	if (ErrorId != -1)
	{
		ProcessErrorId = ErrorId;
		ProcessError = new char[Length];
		sprintf_s(ProcessError, Length, Error);
	}
}

void ResetProcessData(bool ClearProcessError, int NewProcessListSize)
{
	if (ProcessList != nullptr)
	{
		if (ProcessListSize)
		{
			for (int i = 0; i < ProcessListSize; i++)
			{
				if (ProcessList[i] != nullptr)
				{
					delete[]ProcessList[i];
					ProcessList[i] = nullptr;
				}
			}
		}

		delete[]ProcessList;
		ProcessList = nullptr;
	}

	if (ProcessIdList != nullptr)
	{
		delete[]ProcessIdList;
		ProcessIdList = nullptr;
	}

	ProcessSelected = false;
	ProcessIndex = 0;

	if (NewProcessListSize)
	{
		ProcessListSize = NewProcessListSize;
		ProcessList = new char*[ProcessListSize];
		ProcessList[ProcessIndex] = new char[sizeof("No process selected")];
		sprintf_s(ProcessList[ProcessIndex], sizeof("No process selected"), "No process selected");
		ProcessIdList = new DWORD[ProcessListSize];
		ProcessIdList[ProcessIndex] = 0;

		if (!ProcessMenuActive)
		{
			SetProcessMenu();
		}

		if (ClearProcessError)
		{
			SetProcessError(0, "Process State: No process selected", sizeof("Process State: No process selected"));
		}
	}
	else
	{
		ProcessListSize = 0;
		SetProcessError(-1, "", sizeof(""));
	}

	if (ThreadCreationState)
	{
		bool AreThreadsActive = false;

		while (!ThreadDestruction())
		{
			ThreadDestructionCounter++;
			if (ThreadDestructionCounter > 14400)
			{
				AreThreadsActive = true;

				if (NewProcessListSize)
				{
					Close();
				}

				break;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		if (!AreThreadsActive)
		{
			MessagePatcher(false);
		}
	}

	if (CustomEntityListUpdated)
	{
		DeleteCustomEntityList();
	}

	if (CustomNPCListUpdated)
	{
		DeleteCustomNPCList();
	}

	if (CustomPlayerListUpdated)
	{
		DeleteCustomPlayerList();
	}

	Pid = 0;
	Hwnd = NULL;
	Exe = 0;

	if (Handle != NULL)
	{
		CloseHandle(Handle);
		Handle = NULL;
	}
}

int GetProcessCount()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) return 1;

	PROCESSENTRY32 lppe;
	lppe.dwSize = sizeof(lppe);

	int ProcessCount = 1;
	while (Process32Next(hSnapshot, &lppe))
	{
		if (!strcmp(lppe.szExeFile, "Fallout76.exe"))
		{
			ProcessCount++;
		}
	}

	CloseHandle(hSnapshot);
	return ProcessCount;
}

bool UpdateProcessList()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) return false;

	PROCESSENTRY32 lppe;
	lppe.dwSize = sizeof(lppe);

	int ProcessCount = GetProcessCount();
	if (ProcessCount == 1)
	{
		CloseHandle(hSnapshot);
		return false;
	}
	else
	{
		ResetProcessData(true, ProcessCount);
	}

	int CurrentProcess = 0;
	while (Process32Next(hSnapshot, &lppe))
	{
		if (!strcmp(lppe.szExeFile, "Fallout76.exe"))
		{
			CurrentProcess++;
			ProcessList[CurrentProcess] = new char[sizeof("Fallout76.exe - 4294967295")];
			sprintf_s(ProcessList[CurrentProcess], sizeof("Fallout76.exe - 4294967295"), "Fallout76.exe - %lu", lppe.th32ProcessID);
			ProcessIdList[CurrentProcess] = lppe.th32ProcessID;
		}
	}

	CloseHandle(hSnapshot);
	return true;
}

BOOL HwndEnumFunc(HWND hwnd, LPARAM lParam)
{
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(hwnd, &lpdwProcessId);

	if (lpdwProcessId == lParam)
	{
		char Buffer[sizeof("Fallout76")] = { '\0' };
		if (GetClassName(hwnd, Buffer, sizeof(Buffer)))
		{
			if (!strcmp(Buffer, "Fallout76"))
			{
				Hwnd = hwnd;
				return FALSE;
			}
		}
	}

	Hwnd = NULL;
	return TRUE;
}

bool HwndValid(DWORD ProcessId)
{
	Pid = ProcessId;
	if (!Pid)
	{
		SetProcessError(2, "Process State: PID (Process Id) invalid", sizeof("Process State: PID (Process Id) invalid"));
		return false;
	}

	EnumWindows(WNDENUMPROC(HwndEnumFunc), Pid);
	if (Hwnd == NULL)
	{
		SetProcessError(2, "Process State: HWND (Window) invalid", sizeof("Process State: HWND (Window) invalid"));
		return false;
	}

	BOOL Minimized = IsIconic(Hwnd);
	if (Minimized == TRUE)
	{
		SetProcessError(2, "Process State: HWND (Window) minimized", sizeof("Process State: HWND (Window) minimized"));
		return false;
	}

	RECT Rect;
	if (GetClientRect(Hwnd, &Rect) == FALSE || Rect.right < 16 || Rect.bottom < 16)
	{
		SetProcessError(2, "Process State: HWND (Window) invalid/minimized", sizeof("Process State: HWND (Window) invalid/minimized"));
		return false;
	}

	SetProcessError(1, "Process State: Process selected", sizeof("Process State: Process selected"));
	return true;
}

DWORD64 GetModuleBaseAddress(DWORD ProcessId, const char *Module)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessId);
	if (hSnapshot == INVALID_HANDLE_VALUE) return 0;

	MODULEENTRY32 lpme;
	lpme.dwSize = sizeof(lpme);

	while (Module32Next(hSnapshot, &lpme))
	{
		if (!strcmp(lpme.szModule, Module))
		{
			CloseHandle(hSnapshot);
			return DWORD64(lpme.modBaseAddr);
		}
	}

	CloseHandle(hSnapshot);
	return 0;
}

bool ProcessValid(DWORD ProcessId)
{
	Pid = ProcessId;
	if (!Pid)
	{
		SetProcessError(2, "Process State: PID (Process Id) invalid", sizeof("Process State: PID (Process Id) invalid"));
		return false;
	}

	Exe = GetModuleBaseAddress(Pid, "Fallout76.exe");
	if (!Exe)
	{
		SetProcessError(2, "Process State: Base Address invalid", sizeof("Process State: Base Address invalid"));
		return false;
	}

	Handle = OpenProcess(PROCESS_ALL_ACCESS, false, Pid);
	if (Handle == NULL)
	{
		SetProcessError(2, "Process State: HANDLE invalid", sizeof("Process State: HANDLE invalid"));
		return false;
	}

	SetProcessError(1, "Process State: Process selected", sizeof("Process State: Process selected"));
	return true;
}
