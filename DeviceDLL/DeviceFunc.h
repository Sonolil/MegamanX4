#ifndef _DEVICE_FUNC_H
#define _DEVICE_FUNC_H

#define DEVICE_EXPORT
#include "DeviceDef.h"

// Device
EXTERN DEVICE_DLL LPDIRECT3DDEVICE9 GetDevice();
EXTERN DEVICE_DLL LPD3DXSPRITE GetSprite();
EXTERN DEVICE_DLL LPD3DXFONT GetFont();
EXTERN DEVICE_DLL HRESULT InitDevice(WINMODE Mode, HWND hWnd, const int& iWinCX, const int& iWinCY);
EXTERN DEVICE_DLL void Render_Begin();
EXTERN DEVICE_DLL void Render_End(HWND hWnd);
EXTERN DEVICE_DLL void DrawFont(RECT rcFont, const TCHAR* pFont, DWORD dwFlag, DWORD dwColor);
EXTERN DEVICE_DLL void DestroyDevice();

// Timer
EXTERN DEVICE_DLL void InitTimer();
EXTERN DEVICE_DLL void SetTime();
EXTERN DEVICE_DLL float GetTime();
EXTERN DEVICE_DLL void DestroyTimer();

// KeyInput
EXTERN DEVICE_DLL HRESULT InitInputDevice(HWND hWnd, HINSTANCE hInst);
EXTERN DEVICE_DLL void SetKeyState();
EXTERN DEVICE_DLL BYTE GetKeyBoardState(short nKey);
EXTERN DEVICE_DLL const DIMOUSESTATE* GetMouseState();
EXTERN DEVICE_DLL void DestroyKeyInput();


#endif // !_DEVICE_FUNC_H
