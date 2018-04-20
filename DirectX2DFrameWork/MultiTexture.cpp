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
			szPath,									// ���
			pTexInfo->ImgInfo.Width,				// �̹����� �ʺ�
			pTexInfo->ImgInfo.Height,				// �̹����� ����
			pTexInfo->ImgInfo.MipLevels,			// �Ӹ��� ����
			0,										// �������ɼ�(�⺻0)
			pTexInfo->ImgInfo.Format,				// �̹����� ����(����)
			D3DPOOL_MANAGED,						// �ؽ�ó�� ��ġó���Ǵ� �޸� ������ ����Ҳ���
			D3DX_DEFAULT,							// �̹����� ���͸�
			D3DX_DEFAULT,							// �Ӹ� ����
			0,		// �̹����� ARGB���� ��� �����Ұų�
			&pTexInfo->ImgInfo,					// �̹���Info�� ����ü �ּ�
			NULL,									// 256�� �ȷ�Ʈ(�⺻NULL)
			&pTexInfo->pTexture					// ���������� ���� �ؽ��� ������ ����
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

