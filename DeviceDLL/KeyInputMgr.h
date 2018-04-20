#pragma once
#define DEVICE_EXPORT
#include "DeviceDef.h"

EXTERN class DEVICE_DLL CKeyInputMgr
{
	DECLARE_SINGLETON(CKeyInputMgr);
private:
	LPDIRECTINPUT8 m_pInput;
private:
	LPDIRECTINPUTDEVICE8 m_pKeyBoard;
	BYTE m_byKState[256];
	BYTE m_KeyCur[256];
	BYTE m_KeyOld[256];
	BYTE m_KeyMap[256];
private:
	LPDIRECTINPUTDEVICE8 m_pMouse;
	DIMOUSESTATE m_MState;
public:
	HRESULT InitInputDevice(HWND hWnd, HINSTANCE hInst);
	void SetKeyState();
	void Release();
public:
	BYTE GetKeyBoardState(short nKey) { return m_KeyMap[nKey]; }
	const DIMOUSESTATE* GetMouseState(){ return &m_MState; }
private:
	CKeyInputMgr();
public:
	~CKeyInputMgr();
};

