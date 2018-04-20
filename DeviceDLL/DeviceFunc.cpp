#include "DeviceFunc.h"
#include "Device.h"
#include "Timer.h"
#include "KeyInputMgr.h"

EXTERN DEVICE_DLL LPDIRECT3DDEVICE9 GetDevice()
{
	return GET_SINGLE(CDevice)->GetDevice();
}

EXTERN DEVICE_DLL LPD3DXSPRITE GetSprite()
{
	return GET_SINGLE(CDevice)->GetSprite();
}

EXTERN DEVICE_DLL LPD3DXFONT GetFont()
{
	return GET_SINGLE(CDevice)->GetFont();
}

EXTERN DEVICE_DLL HRESULT InitDevice(WINMODE Mode, HWND hWnd, const int& iWinCX, const int& iWinCY)
{
	return GET_SINGLE(CDevice)->InitDevice(Mode, hWnd, iWinCX, iWinCY);
}

EXTERN DEVICE_DLL void Render_Begin()
{
	GET_SINGLE(CDevice)->Render_Begin();
}

EXTERN DEVICE_DLL void Render_End(HWND hWnd)
{
	GET_SINGLE(CDevice)->Render_End(hWnd);
}

EXTERN DEVICE_DLL void DrawFont(RECT rcFont, const TCHAR* pFont, DWORD dwFlag, DWORD dwColor)
{
	GET_SINGLE(CDevice)->DrawFont(rcFont, pFont, dwFlag, dwColor);
}

EXTERN DEVICE_DLL void DestroyDevice()
{
	DESTROY_SINGLETON(CDevice);
}

EXTERN DEVICE_DLL void InitTimer()
{
	GET_SINGLE(CTimer)->InitTimer();
}

EXTERN DEVICE_DLL void SetTime()
{
	GET_SINGLE(CTimer)->SetTime();
}

EXTERN DEVICE_DLL float GetTime()
{
	return GET_SINGLE(CTimer)->GetTime();
}

EXTERN DEVICE_DLL void DestroyTimer()
{
	DESTROY_SINGLETON(CTimer);
}

EXTERN DEVICE_DLL HRESULT InitInputDevice(HWND hWnd, HINSTANCE hInst)
{
	return GET_SINGLE(CKeyInputMgr)->InitInputDevice(hWnd, hInst);
}

EXTERN DEVICE_DLL void SetKeyState()
{
	GET_SINGLE(CKeyInputMgr)->SetKeyState();
}

EXTERN DEVICE_DLL BYTE GetKeyBoardState(short nKey)
{
	return GET_SINGLE(CKeyInputMgr)->GetKeyBoardState(nKey);
}

EXTERN DEVICE_DLL const DIMOUSESTATE* GetMouseState()
{
	return GET_SINGLE(CKeyInputMgr)->GetMouseState();
}

EXTERN DEVICE_DLL void DestroyKeyInput()
{
	DESTROY_SINGLETON(CKeyInputMgr);
}
