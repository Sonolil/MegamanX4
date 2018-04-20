#include "stdafx.h"
#include "SingleTexture.h"

CSingleTexture::CSingleTexture()
	:m_pTexInfo(NULL)
{
}


CSingleTexture::~CSingleTexture()
{
	this->Release();
}

const TEXINFO* CSingleTexture::GetTexture(const TCHAR* pStateKey /*= 0*/, const int& iCnt /*= 0*/)
{
	return m_pTexInfo;
}

const HRESULT CSingleTexture::InsertTexture(const TCHAR* pFileName, const TCHAR* pStateKey /*= 0*/, const int& iCnt /*= 0*/)
{
	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	// 경로에 있는 이미지의 정보를 로드함.
	if (FAILED(D3DXGetImageInfoFromFile(pFileName, &m_pTexInfo->ImgInfo)))
		return E_FAIL;

	if (FAILED(D3DXCreateTextureFromFileEx(
		GetDevice(),		// Device
		pFileName,								// 경로
		m_pTexInfo->ImgInfo.Width,				// 이미지의 너비
		m_pTexInfo->ImgInfo.Height,				// 이미지의 높이
		m_pTexInfo->ImgInfo.MipLevels,			// 밉맵의 레벨
		0,										// 랜더링옵션(기본0)
		m_pTexInfo->ImgInfo.Format,				// 이미지의 포맷(형식)
		D3DPOOL_MANAGED,						// 텍스처의 배치처가되는 메모리 관리를 어떻게할꺼냐
		D3DX_DEFAULT,							// 이미지의 필터링
		D3DX_DEFAULT,							// 밉맵 필터
		0,		// 이미지의 ARGB값을 어떻게 설정할거냐
		&m_pTexInfo->ImgInfo,					// 이미지Info의 구조체 주소
		NULL,									// 256색 팔레트(기본NULL)
		&m_pTexInfo->pTexture					// 실질적으로 만들 텍스쳐 포인터 공간
		)))
		return E_FAIL;

	return S_OK;
}

void CSingleTexture::Release()
{
	SAFE_DELETE(m_pTexInfo);
}

