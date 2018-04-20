#pragma once
#include "Texture.h"

class CSingleTexture : public CTexture
{
private:
	TEXINFO* m_pTexInfo;
public:
	virtual const TEXINFO* GetTexture(const TCHAR* pStateKey = 0,
		const int& iCnt = 0);
	virtual const HRESULT InsertTexture(const TCHAR* pFileName,
		const TCHAR* pStateKey = 0, const int& iCnt = 0);
	virtual void Release();
public:
	CSingleTexture();
	virtual ~CSingleTexture();
};

