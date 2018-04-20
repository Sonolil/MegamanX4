#include "stdafx.h"
#include "TextureMgr.h"

CTextureMgr::CTextureMgr()
{
}


CTextureMgr::~CTextureMgr()
{
	this->Release();
}



const TEXINFO* CTextureMgr::GetTexture(const TCHAR* pObjKey, const TCHAR* pStateKey /*= NULL*/, const int& iCnt /*= 0*/)
{
	map<const TCHAR*, CTexture*>::iterator iter = m_MapTexture.find(pObjKey);

	if (iter == m_MapTexture.end())
		return NULL;

	return iter->second->GetTexture(pStateKey, iCnt);
}

int CTextureMgr::GetImgCount(const TCHAR * pStateKey)
{
	map<const TCHAR*, int>::iterator iter = m_ImgCount.find(pStateKey);

	if (iter == m_ImgCount.end())
		return NULL;

	return iter->second;
}

HRESULT CTextureMgr::InsertTexture(const TCHAR* pFileName, const TCHAR* pObjKey, TEXTYPE TypeID, const TCHAR* pStateKey /*= NULL*/, const int& iCnt /*= 0*/)
{
	map<const TCHAR*, CTexture*>::iterator iter = m_MapTexture.find(pObjKey);

	if (iter == m_MapTexture.end())
	{
		CTexture* pTexture = NULL;

		switch (TypeID)
		{
			case E_TEXTYPE_SINGLE:
				pTexture = new CSingleTexture;
				break;
			case E_TEXTYPE_MULTI:
				pTexture = new CMultiTexture;
				break;
		}

		if (FAILED(pTexture->InsertTexture(pFileName, pStateKey, iCnt)))
			return E_FAIL;

		m_MapTexture.insert(make_pair(pObjKey, pTexture));
	}

	else
	{
		if (FAILED(iter->second->InsertTexture(pFileName, pStateKey, iCnt)))
			return E_FAIL;
	}

	return S_OK;
}

void CTextureMgr::Release()
{

}

