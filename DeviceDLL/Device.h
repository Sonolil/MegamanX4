#pragma once

#define DEVICE_EXPORT
#include "DeviceDef.h"

EXTERN class DEVICE_DLL CDevice
{
	DECLARE_SINGLETON(CDevice);
private:
	LPDIRECT3D9 m_p3D;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXSPRITE m_pSprite;
	LPD3DXFONT m_pFont;
public:
	LPDIRECT3DDEVICE9 GetDevice(){ return m_pDevice; }
	LPD3DXSPRITE GetSprite() { return m_pSprite; }
	LPD3DXFONT GetFont() { return m_pFont; }
public:
	HRESULT InitDevice(WINMODE Mode, HWND hWnd, const int& iWinCX, const int& iWinCY);
	void Render_Begin();
	void Render_End(HWND hWnd);
	void DrawFont(RECT rcFont, const TCHAR* pFont, DWORD dwFlag, DWORD dwColor);
	void Release();
private:
	CDevice();
public:
	~CDevice();
};

