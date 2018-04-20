#include "stdafx.h"
#include "MultiTexture.h"

CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	this->Release();
}


const TEXINFO* CMultiTexture::GetTexture(const TCHAR* pStateKey /*= 0*/, const int& iCnt /*= 0*/)
{
	map<const TCHAR*, vector<TEXINFO*>>::iterator iter = m_MapTexture.find(pStateKey);

	if (iter == m_MapTexture.end())
		return NULL;

	return iter->second[iCnt];
}

const HRESULT CMultiTexture::InsertTexture(const TCHAR* pFileName, const TCHAR* pStateKey /*= 0*/, const int& iCnt /*= 0*/)
{
	TCHAR szPath[128] = L"";

	vector<TEXINFO*> vecTexture;


	for (int i = 0; i < iCnt; ++i)
	{
		wsprintf(szPath, pFileName, i);

		TEXINFO* pTexInfo = new TEXINFO;
		ZeroMemory(pTexInfo, sizeof(TEXINFO));

		if (FAILED(D3DXGetImageInfoFromFile(szPath, &pTexInfo->ImgInfo)))
			return E_FAIL;

		if (FAILED(D3DXCreateTextureFromFileEx(
			GetDevice(),		// Device
			szPath,									// 경로
			pTexInfo->ImgInfo.Width,				// 이미지의 너비
			pTexInfo->ImgInfo.Height,				// 이미지의 높이
			pTexInfo->ImgInfo.MipLevels,			// 밉맵의 레벨
			0,										// 랜더링옵션(기본0)
			pTexInfo->ImgInfo.Format,				// 이미지의 포맷(형식)
			D3DPOOL_MANAGED,						// 텍스처의 배치처가되는 메모리 관리를 어떻게할꺼냐
			D3DX_DEFAULT,							// 이미지의 필터링
			D3DX_DEFAULT,							// 밉맵 필터
			0,		// 이미지의 ARGB값을 어떻게 설정할거냐
			&pTexInfo->ImgInfo,					// 이미지Info의 구조체 주소
			NULL,									// 256색 팔레트(기본NULL)
			&pTexInfo->pTexture					// 실질적으로 만들 텍스쳐 포인터 공간
			)))
			return E_FAIL;

		vecTexture.push_back(pTexInfo);
	}

	m_MapTexture.insert(make_pair(pStateKey, vecTexture));

	return S_OK;
}

void CMultiTexture::Release()
{
	for (map<const TCHAR*, vector<TEXINFO*>>::iterator iter = m_MapTexture.begin();
		iter != m_MapTexture.end(); ++iter)
	{
		for (unsigned int i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->pTexture->Release();
			delete iter->second[i];
			iter->second[i] = NULL;
		}
		iter->second.clear();
	}
	m_MapTexture.clear();
}

