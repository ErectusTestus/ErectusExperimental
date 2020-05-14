#include "ErectusInclude.h"

int GetTextSize(const char *Text)
{
	if (Text == nullptr)
	{
		return 0;
	}

	for (int i = 0; i < 0x7FFF; i++)
	{
		if (Text[i] == '\0')
		{
			return i + 1;
		}
	}

	return 0;
}

int GetTextLength(const char *Text)
{
	if (Text == nullptr)
	{
		return 0;
	}

	for (int i = 0; i < 0x7FFF; i++)
	{
		if (Text[i] == '\0')
		{
			return i;
		}
	}

	return 0;
}

void ValidateDWORD(DWORD *Value, DWORD Min, DWORD Max)
{
	if (*Value < Min) *Value = Min;
	else if (*Value > Max) *Value = Max;
}

void ValidateInt(int *Value, int Min, int Max)
{
	if (*Value < Min) *Value = Min;
	else if (*Value > Max) *Value = Max;
}

void ValidateFloat(float *Value, float Min, float Max)
{
	if (*Value < Min) *Value = Min;
	else if (*Value > Max) *Value = Max;
}

void ValidateRGB(float *Value)
{
	for (int i = 0; i < 3; i++)
	{
		ValidateFloat(&Value[i], 0.0f, 1.0f);
	}
}

void ValidateRGBA(float *Value)
{
	for (int i = 0; i < 4; i++)
	{
		ValidateFloat(&Value[i], 0.0f, 1.0f);
	}
}

bool Valid(DWORD64 Ptr)
{
	if (Ptr < 0x10000UL || Ptr > 0xF000000000000ULL || (Ptr & 1)) return false;
	else return true;
}

bool RPM(DWORD64 src, void *dst, size_t Size)
{
	return ReadProcessMemory(Handle, (void*)(src), dst, Size, NULL);
}

bool WPM(DWORD64 dst, void *src, size_t Size)
{
	return WriteProcessMemory(Handle, (void*)(dst), src, Size, NULL);
}

DWORD64 AllocEx(size_t Size)
{
	return DWORD64(VirtualAllocEx(Handle, NULL, Size, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE));
}

bool FreeEx(DWORD64 src)
{
	return VirtualFreeEx(Handle, LPVOID(src), 0, MEM_RELEASE);
}

bool vtableSwap(DWORD64 dst, DWORD64 src)
{
	DWORD OldProtect;
	if (!VirtualProtectEx(Handle, (void*)(dst), sizeof(DWORD64), PAGE_READWRITE, &OldProtect)) return false;

	bool Result = WPM(dst, &src, sizeof(src));

	DWORD Buffer;
	if (!VirtualProtectEx(Handle, (void*)(dst), sizeof(DWORD64), OldProtect, &Buffer)) return false;

	return Result;
}

float GetDistance(float *a1, float *a2)
{
	return sqrtf(powf((a1[0] - a2[0]), 2.0f) + powf((a1[1] - a2[1]), 2.0f) + powf((a1[2] - a2[2]), 2.0f));
}

void ProjectView(float *dst, float *Forward, float *Origin, float Distance)
{
	dst[0] = Origin[0] + (Forward[0] * Distance);
	dst[1] = Origin[1] + (Forward[1] * Distance);
	dst[2] = Origin[2] + (Forward[2] * Distance);
}

float RadiansToDegrees(float Radians)
{
	return Radians * (180.0f / 3.14159265f);
}

float GetDegrees(float *src, float *Forward, float *Origin)
{
	float Buffer[3];
	ProjectView(Buffer, Forward, Origin, GetDistance(src, Origin));
	return RadiansToDegrees(sinf(GetDistance(src, Buffer) / GetDistance(Origin, Buffer)));
}

bool WTS(float *View, float *Position, float *Screen)
{
	float Buffer[4];
	Buffer[0] = View[0] * Position[0] + -View[1] * -Position[1] + View[2] * Position[2] + View[3];
	Buffer[1] = View[4] * Position[0] + -View[5] * -Position[1] + View[6] * Position[2] + View[7];
	//Buffer[2] = View[8] * Position[0] + -View[9] * -Position[1] + View[10] * Position[2] + View[11];
	Buffer[3] = View[12] * Position[0] + -View[13] * -Position[1] + View[14] * Position[2] + View[15];
	if (Buffer[3] < 0.1f) return false;

	float HalfWindowSize[2];
	HalfWindowSize[0] = float(WindowSize[0]) * 0.5f;
	HalfWindowSize[1] = float(WindowSize[1]) * 0.5f;

	Screen[0] = HalfWindowSize[0] + HalfWindowSize[0] * Buffer[0] / Buffer[3];
	Screen[1] = HalfWindowSize[1] - HalfWindowSize[1] * Buffer[1] / Buffer[3];
	return true;
}

int GetRangedInt(int Min, int Max)
{
	if (Min < Max)
	{
		return rand() % (1 + (Max - Min)) + (Max - (Max - Min));
	}
	else
	{
		return Min;
	}
}

bool SingleKeyPress(int KeyCode, bool *KeyPress)
{
	if (GetAsyncKeyState(KeyCode))
	{
		if (!*KeyPress)
		{
			*KeyPress = true;
			return true;
		}
	}
	else
	{
		if (*KeyPress)
		{
			*KeyPress = false;
			return false;
		}
	}

	return false;
}

bool DoubleKeyPress(int KeyCodeA, int KeyCodeB, bool *KeyPress)
{
	if (GetAsyncKeyState(KeyCodeA))
	{
		return SingleKeyPress(KeyCodeB, KeyPress);
	}

	if (GetAsyncKeyState(KeyCodeB))
	{
		return SingleKeyPress(KeyCodeA, KeyPress);
	}

	return false;
}