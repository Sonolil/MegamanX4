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

	// ��ο� �ִ� �̹����� ������ �ε���.
	if (FAILED(D3DXGetImageInfoFromFile(pFileName, &m_pTexInfo->ImgInfo)))
		return E_FAIL;

	if (FAILED(D3DXCreateTextureFromFileEx(
		GetDevice(),		// Device
		pFileName,								// ���
		m_pTexInfo->ImgInfo.Width,				// �̹����� �ʺ�
		m_pTexInfo->ImgInfo.Height,				// �̹����� ����
		m_pTexInfo->ImgInfo.MipLevels,			// �Ӹ��� ����
		0,										// �������ɼ�(�⺻0)
		m_pTexInfo->ImgInfo.Format,				// �̹����� ����(����)
		D3DPOOL_MANAGED,						// �ؽ�ó�� ��ġó���Ǵ� �޸� ������ ����Ҳ���
		D3DX_DEFAULT,							// �̹����� ���͸�
		D3DX_DEFAULT,							// �Ӹ� ����
		0,		// �̹����� ARGB���� ��� �����Ұų�
		&m_pTexInfo->ImgInfo,					// �̹���Info�� ����ü �ּ�
		NULL,									// 256�� �ȷ�Ʈ(�⺻NULL)
		&m_pTexInfo->pTexture					// ���������� ���� �ؽ��� ������ ����
		)))
		return E_FAIL;

	return S_OK;
}

void CSingleTexture::Release()
{
	SAFE_DELETE(m_pTexInfo);
}

