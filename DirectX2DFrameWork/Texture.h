#pragma once
#include "Defines.h"
#include "Include.h"

class CTexture
{
private:
	int m_iCount;
public:
	virtual const TEXINFO* GetTexture(const TCHAR* pStateKey = 0,
		const int& iCnt = 0)PURE;
	virtual const HRESULT InsertTexture(const TCHAR* pFileName,
		const TCHAR* pStateKey = 0, const int& iCnt = 0)PURE;
	virtual void Release()PURE;
public:
	CTexture();
	virtual ~CTexture();
};

