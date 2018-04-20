#include "stdafx.h"
#include "StageDynamic.h"
#include "ObjMgr.h"
#include "PhysMgr.h"

CStageDynamic::CStageDynamic()
{

}

CStageDynamic::CStageDynamic(const INFO& Info)
	:CObj(Info), m_Speed(P_SPEED), m_Jump(0.0f),
	m_HP(100.0f), m_MaxHP(100.0f), m_Att(1.0f), 
	m_Alive(true), m_Hit(false), m_fHitTimer(0.0f)
{

}

CStageDynamic::~CStageDynamic()
{

}

void CStageDynamic::PlayState(TCHAR * state_, bool repeat_)
{
	map<const TCHAR*, const int>::iterator iter = m_MapState.find(state_);
	if (iter == m_MapState.end())
		return;
	m_pStateKey = state_;
	m_CharClip.pState = state_;
	m_CharClip.bRepeat = repeat_;
	m_CharClip.bEndFrame = false;
	m_CharClip.fFrame = 0.0f;
	m_CharClip.iMaxFrame = iter->second;
}

bool CStageDynamic::CheckGround()
{
	list<BOX*>::iterator it;
	m_HitBox.vPos = m_Info.vPos;
	for (it = m_tPlatform->begin(); it != m_tPlatform->end(); ++it)
	{
		if (GET_SINGLE(CPhysMgr)->HitGround(&m_HitBox, (*it)))
		{
			m_Jump = 0;
			m_Info.vPos.y = (*it)->vPos.y - (*it)->vScale.y / 2
				- (m_HitBox.vScale.y / 2 + m_HitBox.vOffset.y);
			return true;
		}
	}

	return false;
}

bool CStageDynamic::CheckCeiling()
{
	list<BOX*>::iterator it;
	m_HitBox.vPos = m_Info.vPos;
	for (it = m_tPlatform->begin(); it != m_tPlatform->end(); ++it)
	{
		if (GET_SINGLE(CPhysMgr)->HitCeiling(&m_HitBox, (*it)))
		{
			if (m_Jump < 0)
				m_Jump = 0;
			m_Info.vPos.y = (*it)->vPos.y + (*it)->vScale.y / 2
				+ (m_HitBox.vScale.y / 2 + m_HitBox.vOffset.y);
			return true;
		}
	}

	return false;
}

bool CStageDynamic::CheckLeft()
{
	list<BOX*>::iterator it;
	m_HitBox.vPos = m_Info.vPos;
	for (it = m_tPlatform->begin(); it != m_tPlatform->end(); ++it)
	{
		if (GET_SINGLE(CPhysMgr)->HitLeft(&m_HitBox, (*it)))
		{
			m_Info.vPos.x = (*it)->vPos.x + (*it)->vScale.x / 2
				+ m_HitBox.vScale.x / 2;
			return true;
		}
	}
	return false;
}

bool CStageDynamic::CheckRight()
{
	list<BOX*>::iterator it;
	m_HitBox.vPos = m_Info.vPos;
	for (it = m_tPlatform->begin(); it != m_tPlatform->end(); ++it)
	{
		if (GET_SINGLE(CPhysMgr)->HitRight(&m_HitBox, (*it)))
		{
			m_Info.vPos.x = (*it)->vPos.x - (*it)->vScale.x / 2
				- m_HitBox.vScale.x / 2;
			return true;
		}
	}
	return false;
}

void CStageDynamic::TransformMatrix()
{
	float fX, fY;
	fX = m_Info.vPos.x - GET_SINGLE(CCamMgr)->GetCam().x + WINSIZEX / 2;
	fY = m_Info.vPos.y - GET_SINGLE(CCamMgr)->GetCam().y + WINSIZEY / 2;

	D3DXMATRIX matTrans, matScale;
	D3DXMatrixTranslation(&matTrans,
		fX,
		fY,
		m_Info.vPos.z);
	D3DXMatrixScaling(&matScale, m_Info.vDir.x, 1, 1);
	m_Info.matWorld = matScale * matTrans;

	D3DXMatrixTranslation(&matTrans,
		fX + m_HitBox.vOffset.x * m_Info.vDir.x,
		fY + m_HitBox.vOffset.y,
		m_HitBox.vOffset.z);
	D3DXMatrixScaling(&matScale, m_HitBox.vScale.x / 100, m_HitBox.vScale.y / 100, 1);
	m_HitBox.matWorld = matScale * matTrans;

	D3DXMatrixTranslation(&matTrans,
		fX + m_Range.vOffset.x * m_Info.vDir.x,
		fY + m_Range.vOffset.y,
		m_Range.vOffset.z);
	D3DXMatrixScaling(&matScale, m_Range.vScale.x / 100, m_Range.vScale.y / 100, 1);
	m_Range.matWorld = matScale * matTrans;
}

void CStageDynamic::RenderBoxes()
{
	if (m_showBox)
	{
		const TEXINFO* BoxInfo =
			GET_SINGLE(CTextureMgr)->GetTexture(L"Hitbox");

		if (BoxInfo == NULL)
			return;

		if (m_HitBox.active)
		{
			m_HitBox.vCenter = D3DXVECTOR3(
				BoxInfo->ImgInfo.Width / 2,
				BoxInfo->ImgInfo.Height / 2,
				0.0f);

			GetSprite()->SetTransform(&m_HitBox.matWorld);
			GetSprite()->Draw(BoxInfo->pTexture, NULL,
				&m_HitBox.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (m_Range.active)
		{
			m_Range.vCenter = D3DXVECTOR3(
				BoxInfo->ImgInfo.Width / 2,
				BoxInfo->ImgInfo.Height / 2,
				0.0f);

			GetSprite()->SetTransform(&m_Range.matWorld);
			GetSprite()->Draw(BoxInfo->pTexture, NULL,
				&m_Range.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 0, 0));
		}
	}
}

void CStageDynamic::RenderFX()
{
	D3DXMATRIX matTrans, matScale;

	list<CLIP*>::iterator it;
	for (it = m_FXClips.begin(); it != m_FXClips.end(); ++it)
	{
		CLIP* clip = (*it);

		if (!(clip->bActive))
			continue;

		const TEXINFO* texInfo =
			GET_SINGLE(CTextureMgr)->GetTexture(
				clip->pObject, 
				clip->pState, 
				(int)(clip->fFrame));

		if (texInfo == NULL)
			continue;
		
		D3DXMatrixTranslation(&matTrans,
			clip->vPos.x - GET_SINGLE(CCamMgr)->GetCam().x + WINSIZEX / 2,
			clip->vPos.y - GET_SINGLE(CCamMgr)->GetCam().y + WINSIZEY / 2,
			clip->vPos.z);
		D3DXMatrixScaling(&matScale, clip->vScale.x, clip->vScale.y, clip->vScale.z);
		clip->matWorld = matScale * matTrans;
		clip->vCenter = D3DXVECTOR3(
			texInfo->ImgInfo.Width / 2,
			texInfo->ImgInfo.Height / 2,
			0.0f);

		GetSprite()->SetTransform(&clip->matWorld);
		GetSprite()->Draw(texInfo->pTexture, NULL,
			&clip->vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
			
	}
}

