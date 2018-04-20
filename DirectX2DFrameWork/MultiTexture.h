#pragma once
#include "Texture.h"

class CMultiTexture : public CTexture
{
private:
	map<const TCHAR*, vector<TEXINFO*>> m_MapTexture;
public:
	virtual const TEXINFO* GetTexture(const TCHAR* pStateKey = 0,
		const int& iCnt = 0);
	virtual const HRESULT InsertTexture(const TCHAR* pFileName,
		const TCHAR* pStateKey = 0, const int& iCnt = 0);
	virtual void Release();
public:
	CMultiTexture();
	virtual ~CMultiTexture();
};

