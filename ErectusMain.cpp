#include "ErectusInclude.h"

int WindowSize[2] = { 0, 0 };
int WindowPosition[2] = { 0, 0 };
HWND WindowHwnd = NULL;

bool OverlayMenuActive = false;
bool OverlayActive = false;
bool OverlayForeground = false;
bool OverlayMenuPress = false;

int WindowTopmostCounter = 0;

bool ExperimentalOverlayFix = false;

void Close()
{
	if (WindowHwnd != NULL)
	{
		SendMessage(WindowHwnd, WM_CLOSE, NULL, NULL);
	}
}

void SetOverlayMenu()
{
	if (WindowSize[0] != 480 || WindowSize[1] != 480)
	{
		WindowSize[0] = 480;
		WindowSize[1] = 720;

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

	ProcessMenuActive = false;
	OverlayMenuActive = true;
	OverlayActive = false;
}

bool SetOverlayPosition(bool Topmost, bool Layered)
{
	if (!HwndValid(Pid))
	{
		OverlayActive = false;
		return false;
	}

	RECT WindowRect;
	if (!GetWindowRect(Hwnd, &WindowRect))
	{
		OverlayActive = false;
		return false;
	}

	RECT ClientRect;
	if (!GetClientRect(Hwnd, &ClientRect))
	{
		OverlayActive = false;
		return false;
	}

	int Size[2];
	Size[0] = ClientRect.right;
	Size[1] = ClientRect.bottom;

	int Position[2];
	Position[0] = WindowRect.left - (((ClientRect.right + WindowRect.left) - WindowRect.right) / 2);
	Position[1] = WindowRect.top - (((ClientRect.bottom + WindowRect.top) - WindowRect.bottom) / 2);

	if (GetWindowLongPtr(Hwnd, GWL_STYLE) & WS_BORDER)
	{
		int Buffer = GetSystemMetrics(SM_CYCAPTION) / 2;
		Buffer += (Buffer & 1);
		Position[1] += Buffer;
	}

	if (GetMenu(Hwnd) != NULL)
	{
		int Buffer = GetSystemMetrics(SM_CYMENU) / 2;
		Buffer += (Buffer & 1);
		Position[1] += Buffer;
	}

	if (Position[0] != WindowPosition[0] || Position[1] != WindowPosition[1])
	{
		WindowPosition[0] = Position[0];
		WindowPosition[1] = Position[1];
		MoveWindow(WindowHwnd, WindowPosition[0], WindowPosition[1], WindowSize[0], WindowSize[1], FALSE);
	}

	if (Size[0] != WindowSize[0] || Size[1] != WindowSize[1])
	{
		WindowSize[0] = Size[0];
		WindowSize[1] = Size[1];
		DeviceResetQueued = true;
	}

	if (Topmost || Layered)
	{
		LONG_PTR Style = GetWindowLongPtr(WindowHwnd, GWL_EXSTYLE);

		if (Topmost && !(Style & WS_EX_TOPMOST))
		{
			SetWindowPos(WindowHwnd, HWND_TOPMOST, WindowPosition[0], WindowPosition[1], WindowSize[0], WindowSize[1], 0);
			WindowTopmostCounter++;
			if (WindowTopmostCounter > 3)
			{
				WindowTopmostCounter = 0;
				SetProcessError(0, "Process State: Overlay not topmost", sizeof("Process State: Overlay not topmost"));
				OverlayActive = false;
				return false;
			}
		}
		else if (!Topmost && (Style & WS_EX_TOPMOST))
		{
			SetWindowPos(WindowHwnd, HWND_NOTOPMOST, WindowPosition[0], WindowPosition[1], WindowSize[0], WindowSize[1], 0);
		}
		else
		{
			WindowTopmostCounter = 0;
		}

		if (Layered && !(Style & WS_EX_LAYERED))
		{
			Style |= WS_EX_LAYERED;
			SetWindowLongPtr(WindowHwnd, GWL_EXSTYLE, Style);
			if (ExperimentalOverlayFix)
			{
				SetLayeredWindowAttributes(WindowHwnd, RGB(0x00, 0x00, 0x00), 0xFF, LWA_ALPHA | LWA_COLORKEY);
			}
			else
			{
				SetLayeredWindowAttributes(WindowHwnd, RGB(0x00, 0x00, 0x00), 0xFF, LWA_ALPHA);
			}
		}
		else if (!Layered && (Style & WS_EX_LAYERED))
		{
			Style &= ~WS_EX_LAYERED;
			SetWindowLongPtr(WindowHwnd, GWL_EXSTYLE, Style);
		}
	}

	ProcessMenuActive = false;
	OverlayMenuActive = false;
	OverlayActive = true;
	return true;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
	{
		return 1;
	}

	switch (uMsg)
	{
	case WM_PAINT:
		D3D9Render();
		return 0;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	WNDCLASSEX WindowClassEx;
	WindowClassEx.cbSize = sizeof(WNDCLASSEX);
	WindowClassEx.style = CS_VREDRAW | CS_HREDRAW;
	WindowClassEx.lpfnWndProc = WindowProc;
	WindowClassEx.cbClsExtra = 0;
	WindowClassEx.cbWndExtra = 0;
	WindowClassEx.hInstance = hInstance;
	WindowClassEx.hIcon = LoadIcon(WindowClassEx.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	WindowClassEx.hCursor = NULL;
	WindowClassEx.hbrBackground = CreateSolidBrush(RGB(0x00, 0x00, 0x00));
	WindowClassEx.lpszMenuName = NULL;
	WindowClassEx.lpszClassName = "ErectusCLS";
	WindowClassEx.hIconSm = NULL;

	if (!RegisterClassEx(&WindowClassEx))
	{
		return 1;
	}

	WindowSize[0] = 384;
	WindowSize[1] = 224;
	WindowPosition[0] = (GetSystemMetrics(SM_CXSCREEN) / 2) - (WindowSize[0] / 2);
	WindowPosition[1] = (GetSystemMetrics(SM_CYSCREEN) / 2) - (WindowSize[1] / 2);
	WindowHwnd = CreateWindowEx(WS_EX_TRANSPARENT | WS_EX_LAYERED, WindowClassEx.lpszClassName, "Erectus", WS_POPUP, WindowPosition[0], WindowPosition[1], WindowSize[0], WindowSize[1], NULL, NULL, WindowClassEx.hInstance, NULL);
	
	if (WindowHwnd == NULL)
	{
		UnregisterClass(WindowClassEx.lpszClassName, WindowClassEx.hInstance);
		return 2;
	}

	MARGINS OverlayMargins = { -1, -1, -1, -1 };
	DwmExtendFrameIntoClientArea(WindowHwnd, &OverlayMargins);
	SetLayeredWindowAttributes(WindowHwnd, RGB(0x00, 0x00, 0x00), 0xFF, LWA_ALPHA);
	SetWindowLongPtr(WindowHwnd, GWL_EXSTYLE, WS_EX_TRANSPARENT);
	ShowWindow(WindowHwnd, SW_SHOW);

	D3D9Initialized = D3D9Initialize();
	if (!D3D9Initialized)
	{
		Close();
		D3D9Cleanup();
		UnregisterClass(WindowClassEx.lpszClassName, WindowClassEx.hInstance);
		return 3;
	}

	ImGuiInitialized = ImGuiInitialize();
	if (!ImGuiInitialized)
	{
		Close();
		D3D9Cleanup();
		ImGuiCleanup();
		UnregisterClass(WindowClassEx.lpszClassName, WindowClassEx.hInstance);
		return 4;
	}

	ResetProcessData(true, 1);
	ReadIniSettings();

	MSG OverlayMsg;
	while (GetMessage(&OverlayMsg, NULL, 0, 0))
	{
		TranslateMessage(&OverlayMsg);
		DispatchMessage(&OverlayMsg);
	}

	ResetProcessData(true, 0);
	WriteIniSettings();

	D3D9Cleanup();
	ImGuiCleanup();
	UnregisterClass(WindowClassEx.lpszClassName, WindowClassEx.hInstance);
	return 0;
}