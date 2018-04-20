#pragma once
#include "Defines.h"
#include "Texture.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr);
private:
	map<const TCHAR*, CTexture*> m_MapTexture;
	map<const TCHAR*, int> m_ImgCount;
public:
	const TEXINFO* GetTexture(const TCHAR* pObjKey,
		const TCHAR* pStateKey = NULL,
		const int& iCnt = 0);

	int GetImgCount(const TCHAR* pStateKey);

	HRESULT InsertTexture(const TCHAR* pFileName,
		const TCHAR* pObjKey, TEXTYPE TypeID,
		const TCHAR* pStateKey = NULL,
		const int& iCnt = 0);
	void Release();

private:
	CTextureMgr();
public:
	~CTextureMgr();
};

