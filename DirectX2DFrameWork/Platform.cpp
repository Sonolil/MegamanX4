#include "stdafx.h"
#include "PhysMgr.h"
#include "CamMgr.h"
#include "Platform.h"


CPlatform::CPlatform()
{

}

CPlatform::CPlatform(const INFO& Info)
	:CStageStatic(Info)
{

}

CPlatform::~CPlatform()
{
	this->Release();
}

void CPlatform::CreatePlatform(D3DXVECTOR3 vPos, D3DXVECTOR3 vScale)
{
	BOX* platform = new BOX();
	platform->vPos = vPos;
	platform->vScale = vScale;
	platform->vOffset = D3DXVECTOR3(0, 0, 0);
	m_tPlatform.push_back(platform);
}

void CPlatform::MapState()
{
	//Pillars
	CreatePlatform(D3DXVECTOR3(50, 400, 0), D3DXVECTOR3(100.0f, 800.0f, 1));
	CreatePlatform(D3DXVECTOR3(1950, 400, 0), D3DXVECTOR3(100.0f, 800.0f, 1));

	//Floor
	CreatePlatform(D3DXVECTOR3(1580, 700, 0), D3DXVECTOR3(3000.0f, 100.0f, 1));
	CreatePlatform(D3DXVECTOR3(1580, 0, 0), D3DXVECTOR3(3000.0f, 100.0f, 1));


	CreatePlatform(D3DXVECTOR3(130, 370, 0), D3DXVECTOR3(500.0f, 70.0f, 1));
	CreatePlatform(D3DXVECTOR3(1870, 370, 0), D3DXVECTOR3(500.0f, 70.0f, 1));
	
	CreatePlatform(D3DXVECTOR3(1000, 100, 0), D3DXVECTOR3(200.0f, 700.0f, 1));
	//CreatePlatform(D3DXVECTOR3(980, 1000, 0), D3DXVECTOR3(200.0f, 700.0f, 1));
}

void CPlatform::DrawBackground()
{
	float ratio = 800.0f / 1313.0f;
	float parallelX = GET_SINGLE(CCamMgr)->GetCam().x - WINSIZEX / 2;
	float parallelY = GET_SINGLE(CCamMgr)->GetCam().y - WINSIZEY / 2;
	D3DXMATRIX matTrans, matScale, matWorld;

	const TEXINFO* TexInfo =
		GET_SINGLE(CTextureMgr)->GetTexture(L"BG");

	D3DXMatrixTranslation(&matTrans, 0, 0, 0);
	D3DXMatrixScaling(&matScale, 1, 1, 1);
	matWorld = matScale * matTrans;
	GetSprite()->SetTransform(&matWorld);
	GetSprite()->Draw(TexInfo->pTexture, NULL,
		&D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	TexInfo =
		GET_SINGLE(CTextureMgr)->GetTexture(L"Parallax1");
	GetSprite()->Draw(TexInfo->pTexture, NULL,
		&D3DXVECTOR3((parallelX * ratio) / 5, (parallelY * ratio) / 5, 0), 
		NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	TexInfo =
		GET_SINGLE(CTextureMgr)->GetTexture(L"Parallax2");

	for (int i = 0; i < paraCount; i++)
	{
		m_parallax[i]->fX += m_parallax[i]->fSpeed;
		if (m_parallax[i]->fX > 1600)
			m_parallax[i]->fX = -300;
		else if (m_parallax[i]->fX < -300)
			m_parallax[i]->fX = 1600;
	}

	m_parallax[0]->fSpeed = 0.3f;
	m_parallax[1]->fSpeed = 2.1f;
	m_parallax[2]->fSpeed = - 1.3f;
	m_parallax[3]->fSpeed = 0.8f;

	D3DXMatrixTranslation(&matTrans, 500, 200, 0);
	D3DXMatrixScaling(&matScale, -2, 2, 1);
	matWorld = matScale * matTrans;
	GetSprite()->SetTransform(&matWorld);
	GetSprite()->Draw(TexInfo->pTexture, NULL,
		&D3DXVECTOR3(-(parallelX * ratio) / 4 + m_parallax.at(0)->fX,
		(parallelY * ratio) / 4, 0),
		NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	DrawParallax(L"Ship1", 300, 400, 2, 2, 3.5, m_parallax.at(1)->fX);
	DrawParallax(L"Ship2", 400, 440, 3, 3, 3.3, m_parallax.at(2)->fX);
	DrawParallax(L"Ship3", 400, 440, 2.8, 2.8, 3.2, m_parallax.at(3)->fX);
	DrawParallax(L"Parallax2", 200, 350, 4, 4, 3.5, 0);

	for (int i = 0; i < 4; i++)
	{
		Draw(L"Pillar", i * 740, 400, 1, 1);
	}

	for (int i = 0; i < 4; i++)
	{
		Draw(L"Wall2", 900, 20 + 109 * i, 1, 1);
	}

	Draw(L"PlatformLeft", 0, 320, 1, 1);
	Draw(L"PlatformMiddle", 97, 320, 1, 1);
	Draw(L"PlatformRight", 290, 320, 1, 1);

	Draw(L"PlatformRight", 1904, 320, 1, 1);
	Draw(L"PlatformMiddle", 1716, 320, 1, 1);
	Draw(L"PlatformLeft", 1619, 320, 1, 1);


	for (int i = 0; i < 3; i++)
	{
		Draw(L"Wall", 0, 305 * i, 1, 1);
		Draw(L"Wall", 1700, 305 * i, -1, 1);
	}


	Draw(L"PlatformLeft", 0, 630, 1, 1);
	for (int i = 0; i < 11; i++)
	{
		Draw(L"PlatformMiddle", 97 + i * 193, 630, 1, 1);
	}

	Draw(L"PlatformLeft", 0, -50, 1, 1);
	for (int i = 0; i < 11; i++)
	{
		Draw(L"PlatformMiddle", 97 + i * 193, -50, 1, 1);
	}
}

void CPlatform::DrawParallax(TCHAR* text, 
	float transX, float transY, float scaleX, float scaleY,
	float parallaxRate, float m_parallax)
{
	float ratio = 800.0f / 1313.0f;
	float parallelX = GET_SINGLE(CCamMgr)->GetCam().x - WINSIZEX / 2;
	float parallelY = GET_SINGLE(CCamMgr)->GetCam().y - WINSIZEY / 2;
	D3DXMATRIX matTrans, matScale, matWorld;

	const TEXINFO* TexInfo = 
		GET_SINGLE(CTextureMgr)->GetTexture(text);
	D3DXMatrixTranslation(&matTrans, transX, transY, 0);
	D3DXMatrixScaling(&matScale, scaleX, scaleY, 1);
	matWorld = matScale * matTrans;
	GetSprite()->SetTransform(&matWorld);
	GetSprite()->Draw(TexInfo->pTexture, NULL,
	&D3DXVECTOR3((parallelX * ratio) / parallaxRate + m_parallax,
	(parallelY * ratio) / parallaxRate, 0),
	NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPlatform::Draw(TCHAR * text, float transX, float transY, float scaleX, float scaleY)
{
	float ratio = 800.0f / 1313.0f;
	float parallelX = GET_SINGLE(CCamMgr)->GetCam().x - WINSIZEX / 2;
	float parallelY = GET_SINGLE(CCamMgr)->GetCam().y - WINSIZEY / 2;
	D3DXMATRIX matTrans, matScale, matWorld;

	const TEXINFO* TexInfo =
		GET_SINGLE(CTextureMgr)->GetTexture(text);
	D3DXMatrixTranslation(&matTrans, transX, transY, 0);
	D3DXMatrixScaling(&matScale, scaleX, scaleY, 1);
	matWorld = matScale * matTrans;
	GetSprite()->SetTransform(&matWorld);
	GetSprite()->Draw(TexInfo->pTexture, NULL,
		&D3DXVECTOR3(
			parallelX,
			parallelY,
			0),
		NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}


HRESULT CPlatform::Initialize()
{
	MapState();
	m_eSortID = E_SORTID_FIRST;
	for (int i = 0; i < paraCount; i++)
	{
		ANIM* anim = new ANIM();
		anim->fX = 0;
		m_parallax.push_back(anim);
	}
	
	return S_OK;
}

E_SCENE CPlatform::Progress()
{
	if (GetKeyBoardState(DIK_SPACE) == E_INPUT_DOWN)
		m_showBox = !m_showBox;
		

	return E_SCENE_NONPASS;
}

void CPlatform::DrawPlatform()
{
	if (m_showBox)
	{
		const TEXINFO* TexInfo =
			GET_SINGLE(CTextureMgr)->GetTexture(L"Hitbox");

		if (TexInfo == NULL)
			return;

		float fX = -GET_SINGLE(CCamMgr)->GetCam().x + WINSIZEX / 2;
		float fY = -GET_SINGLE(CCamMgr)->GetCam().y + WINSIZEY / 2;
		D3DXMATRIX matTrans, matScale;
		for (it = m_tPlatform.begin(); it != m_tPlatform.end(); ++it)
		{
			D3DXMatrixTranslation(&matTrans,
				(*it)->vPos.x + fX,
				(*it)->vPos.y + fY,
				(*it)->vPos.z);
			D3DXMatrixScaling(&matScale, (*it)->vScale.x / 100, (*it)->vScale.y / 100, 1);
			(*it)->matWorld = matScale * matTrans;

			(*it)->vCenter = D3DXVECTOR3(
				TexInfo->ImgInfo.Width / 2.f,
				TexInfo->ImgInfo.Height / 2.f,
				0.0f);

			GetSprite()->SetTransform(&((*it)->matWorld));
			GetSprite()->Draw(TexInfo->pTexture, NULL,
				&((*it)->vCenter), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}	
}

void CPlatform::Render()
{	
	DrawBackground();
	DrawPlatform();
}

void CPlatform::Release()
{

}

CObj* CPlatform::Clone()
{
	return new CPlatform(*this);
}

