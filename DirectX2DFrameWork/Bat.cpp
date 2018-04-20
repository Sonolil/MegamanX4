#include "stdafx.h"
#include "Bat.h"
#include "ObjMgr.h"
#include "PhysMgr.h"
#include "Platform.h"
#include "SoundMgr.h"


CBat::CBat()
{
}


CBat::CBat(const INFO& Info)
	:CStageDynamic(Info), m_bInit(true), m_Regen(0.0f)
{

}

void CBat::AIMachine()
{
	m_fHitTimer += GetTime();
	m_Info.vPos.x -= m_Info.vDir.x * m_Speed;

	if (m_pStateKey == L"Before")
	{
		//Bomb
	}

	if (m_pStateKey == L"Drop")
	{
		if (m_CharClip.bEndFrame)
		{
			PlayState(L"Before", true);
		}
	}

	m_Hit = false;
	m_HitBox.vPos = m_Info.vPos;
	m_HitBox.vDir = m_Info.vDir;
	m_Player->GetHitBox()->vPos = m_Player->GetInfo()->vPos;
	m_Player->GetHitBox()->vDir = m_Player->GetInfo()->vDir;
	if (GET_SINGLE(CPhysMgr)->HitTest(m_Player->GetHitBox(), &m_HitBox))
	{
		if (m_Player->GetHitBox()->active)
			m_Player->Damage(m_Att);
	}

	m_Player->GetRange()->vPos = m_Player->GetInfo()->vPos;
	m_Player->GetRange()->vDir = m_Player->GetInfo()->vDir;
	if (GET_SINGLE(CPhysMgr)->HitTest(m_Player->GetRange(), &m_HitBox) &&
		m_Player->GetRange()->active)
	{
		Damage(m_Player->GetAtt());
	}
}

void CBat::MapState()
{
	m_MapState.insert(make_pair(L"Before", 4));
	m_MapState.insert(make_pair(L"After", 5));
	m_MapState.insert(make_pair(L"Drop", 3));
}

void CBat::Damage(float att_)
{
	if (m_fHitTimer < 0.1f)
		return;

	if (m_Block)
	{
		PoolClip(L"FX", L"Block", 5, 30, false,
			D3DXVECTOR3(
				m_Info.vPos.x,
				m_Info.vPos.y,
				m_Info.vPos.z),
			D3DXVECTOR3(2, 2, 1));
		return;
	}

	m_fHitTimer = 0.0f;
	m_Hit = true;
	m_HP -= att_;
	if (m_HP >= m_MaxHP)
		m_HP = m_MaxHP;

	if (m_HP <= 0)
	{
		GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_EXPLODE, false);
		m_Regen = 0;
		PoolClip(L"FX", L"ExplodeS", 16, 30, false,
			D3DXVECTOR3(
				m_Info.vPos.x + 10,
				m_Info.vPos.y,
				m_Info.vPos.z),
			D3DXVECTOR3(2, 2, 1));
		m_Alive = false;
		m_HP = 0;
	}

	GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_HIT, false);
	PoolClip(L"FX", L"Hit", 4, 30, false,
		D3DXVECTOR3(
			m_Info.vPos.x,
			m_Info.vPos.y,
			m_Info.vPos.z),
		D3DXVECTOR3(2, 2, 1));
}

HRESULT CBat::Initialize()
{
	MapState();
	m_Player = (CPlayer*)(GET_SINGLE(CObjMgr)->GetObj(L"Player"));
	m_tPlatform =
		((CPlatform*)(GET_SINGLE(CObjMgr)->GetObj(L"Platform")))->GetPlatform();

	m_Info.vDir.x = 
		(m_Player->GetInfo()->vPos.x < m_Info.vPos.x) ? 1 : -1;

	m_InitPos = m_Info.vPos;
	m_eSortID = E_SORTID_SECOND;
	m_CharClip.pObject = L"Bat";
	ResetState();

	return S_OK;
}

void CBat::ResetState()
{
	m_Alive = true;

	m_Info.vPos = m_InitPos;
	PlayState(L"After", true);
	m_CharClip.fSpeed = 22;

	m_Speed = 1.5f;
	m_MaxHP = m_HP = 2.0f;
	m_Att = 12;

	m_HitBox.vScale.x = 45;
	m_HitBox.vScale.y = 45;
	m_HitBox.vOffset.x = 0;
	m_HitBox.vOffset.y = 15;
	m_HitBox.active = true;
}

E_SCENE CBat::Progress()
{
	SpriteAnimation(&m_CharClip);
	list<CLIP*>::iterator it;
	for (it = m_FXClips.begin(); it != m_FXClips.end(); it++)
	{
		SpriteAnimation((*it));
	}

	if (m_Alive)
		AIMachine();

	else
	{
		m_Regen += GetTime();
		if (m_Regen > 10.0f)
			ResetState();
	}

	TransformMatrix();

	return E_SCENE_NONPASS;
}

void CBat::Render()
{
	if (m_Alive)
	{
		const TEXINFO* TexInfo =
			GET_SINGLE(CTextureMgr)->GetTexture(
				m_CharClip.pObject,
				m_pStateKey,
				int(m_CharClip.fFrame));

		if (TexInfo == NULL)
			return;

		m_Info.vCenter = D3DXVECTOR3(
			TexInfo->ImgInfo.Width / 2.f - 5,
			TexInfo->ImgInfo.Height / 2.f - 6,
			0.0f);

		D3DCOLOR hit;
		if (m_Hit)
			hit = D3DCOLOR_RGBA(255, 50, 50, 235);
		else hit = D3DCOLOR_RGBA(255, 255, 255, 255);


		GetSprite()->SetTransform(&m_Info.matWorld);
		GetSprite()->Draw(TexInfo->pTexture, NULL,
			&m_Info.vCenter, NULL, hit);

		if (m_pStateKey == L"Before")
		{

		}

		//RenderBoxes();
	}

	RenderFX();
}


void CBat::Release()
{
	SAFE_DELETE(m_pAStar);
}

CObj* CBat::Clone()
{
	return new CBat(*this);
}

CBat::~CBat()
{
}
