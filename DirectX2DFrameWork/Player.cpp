#include "stdafx.h"
#include "ObjMgr.h"
#include "Platform.h"
#include "CamMgr.h"
#include "PhysMgr.h"
#include "Player.h"
#include "SoundMgr.h"

CPlayer::CPlayer()
{

}

CPlayer::CPlayer(const INFO& Info)
	:CStageDynamic(Info), m_Skill(false)
{

}

CPlayer::~CPlayer()
{
	this->Release();
}

void CPlayer::KeyCheck()
{
	if (GetKeyBoardState(DIK_RIGHT) == E_INPUT_PRESS ||
		GetKeyBoardState(DIK_LEFT) == E_INPUT_PRESS)
	{
		if (m_pStateKey == L"Idle" ||
			m_pStateKey == L"FallEnd" ||
			m_pStateKey == L"AttackFinish")
		PlayState(L"WalkBegin", false);
			
		if (m_pStateKey != L"Init" &&
			m_pStateKey != L"Start" &&
			m_pStateKey != L"StartEnd" &&
			m_pStateKey != L"Attack11" &&
			m_pStateKey != L"Attack12" &&
			m_pStateKey != L"Attack21" &&
			m_pStateKey != L"Attack22" &&
			m_pStateKey != L"Attack3" &&
			m_pStateKey != L"DashBegin" &&
			m_pStateKey != L"Dash" &&
			m_pStateKey != L"Hurt" &&
			!m_Skill)
		{
			if (GetKeyBoardState(DIK_RIGHT) == E_INPUT_PRESS)
			{
				m_Info.vDir.x = 1;
				m_Info.vPos.x += m_Speed;
			}
			
			else if (GetKeyBoardState(DIK_LEFT) == E_INPUT_PRESS)
			{
				m_Info.vDir.x = -1;
				m_Info.vPos.x -= m_Speed;
			}
		}
	}

	if (GetKeyBoardState(DIK_RIGHT) == E_INPUT_UP ||
		GetKeyBoardState(DIK_LEFT) == E_INPUT_UP)
	{
		if (m_pStateKey == L"WalkBegin" ||
			m_pStateKey == L"Walk")
		{
			PlayState(L"Idle", false);
		}
	}

	if (GetKeyBoardState(DIK_S) == E_INPUT_DOWN)
	{
		if (m_pStateKey == L"Idle" ||
			m_pStateKey == L"WalkBegin" ||
			m_pStateKey == L"Walk" ||
			m_pStateKey == L"FallEnd" ||
			m_pStateKey == L"DashBegin" ||
			m_pStateKey == L"Dash" ||
			m_pStateKey == L"DashEnd")
		{
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_JUMPG, false);
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_JUMP2, false);
			PlayState(L"JumpBegin", false);
			m_Jump = -10;
		}

		else if (m_pStateKey == L"SlideBegin" ||
			m_pStateKey == L"Slide")
		{
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_JUMPS, false);
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_JUMP1, false);
			PlayState(L"SlideJump", false);
			m_Jump = -7;
		}
	}

	if (GetKeyBoardState(DIK_D) == E_INPUT_DOWN)
	{
		if (m_pStateKey == L"Idle" ||
			m_pStateKey == L"WalkBegin" ||
			m_pStateKey == L"Walk" ||
			m_pStateKey == L"FallEnd" ||
			m_pStateKey == L"AttackFinish")
		{
			m_HitBox.active = false;
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_SWORD, false);
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_HOO, false);
			m_Range.active = true;
			m_Range.vOffset.x = 70;
			m_Range.vOffset.y = -40;
			m_Range.vScale.x = 80;
			m_Range.vScale.y = 180;
			PlayState(L"Attack11", false);
		}

		if (m_pStateKey == L"Attack12")
		{
			m_HitBox.active = false;
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_SWORD, false);
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_HAH, false);
			m_Range.active = true;
			m_Range.vOffset.x = 40;
			m_Range.vOffset.y = 0;
			m_Range.vScale.x = 200;
			m_Range.vScale.y = 60;
			PlayState(L"Attack21", false);
		}
			

		if (m_pStateKey == L"Attack22")
		{
			m_HitBox.active = false;
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_SWORD, false);
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_HO, false);
			m_Range.active = true;
			m_Range.vOffset.x = 70;
			m_Range.vOffset.y = -40;
			m_Range.vScale.x = 160;
			m_Range.vScale.y = 160;
			PlayState(L"Attack3", false);
		}
			

		if (m_pStateKey == L"JumpBegin" ||
			m_pStateKey == L"Jump" ||
			m_pStateKey == L"FallBegin" ||
			m_pStateKey == L"Fall")
		{
			m_HitBox.active = false;
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_SWORD, false);
			m_Range.active = true;
			m_Range.vOffset.x = 50;
			m_Range.vOffset.y = 0;
			m_Range.vScale.x = 140;
			m_Range.vScale.y = 120;
			PlayState(L"JumpAttack", false);
		}
	}

	if (GetKeyBoardState(DIK_A) == E_INPUT_DOWN)
	{
		if (m_pStateKey == L"Idle" ||
			m_pStateKey == L"WalkBegin" ||
			m_pStateKey == L"Walk" ||
			m_pStateKey == L"FallEnd" ||
			m_pStateKey == L"DashEnd")
		{
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_DASH, false);
			PoolClip(L"FX", L"Dash", 8, 30, false,
				D3DXVECTOR3(
					m_Info.vPos.x - 30 * m_Info.vDir.x, 
					m_Info.vPos.y + 10, 
					m_Info.vPos.z),
				D3DXVECTOR3(m_Info.vDir.x * 2, 2, 1)
			);

			m_fTimer = 0;
			m_Speed = P_DASH;
			PlayState(L"DashBegin", false);
		}
	}

	if (GetKeyBoardState(DIK_A) == E_INPUT_PRESS)
	{
		if (m_pStateKey == L"DashBegin" ||
			m_pStateKey == L"Dash")
		{
			m_fTimer += GetTime();
			m_Info.vPos.x += m_Info.vDir.x * m_Speed;
			if (m_fTimer > 0.40f)
			{
				GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_DASHEND, false);
				PlayState(L"DashEnd", false);
			}
		}

		if (m_pStateKey == L"SlideJump")
		{
			m_Speed = P_DASH;
		}
	}

	if (GetKeyBoardState(DIK_A) == E_INPUT_UP)
	{
		if (m_pStateKey == L"DashBegin" || 
			m_pStateKey == L"Dash")
		{
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_DASHEND, false);
			PlayState(L"DashEnd", false);
		}
	}

	if (GetKeyBoardState(DIK_F) == E_INPUT_DOWN)
	{
		if (m_pStateKey == L"WalkBegin" ||
			m_pStateKey == L"Walk" || 
			m_pStateKey == L"Idle")
		{
			if (GetKeyBoardState(DIK_UP) == E_INPUT_PRESS)
			{
				GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_FIRE, false);
				GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_OOM, false);
				m_Jump = -10;
				m_Info.vRender.x = -25;
				m_Info.vRender.y = 30;

				m_Skill = true;
				m_Range.active = true;
				m_Range.vOffset.x = 45;
				m_Range.vOffset.y = -50;
				m_Range.vScale.x = 140;
				m_Range.vScale.y = 150;
				m_HitBox.active = false;
				PlayState(L"SkillFire1", false);
			}

			else
			{
				GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_LIGHTNING1, false);
				m_HitBox.active = false;
				m_Info.vRender.x = -88;
				m_Info.vRender.y = 1;
				m_Skill = true;
				PlayState(L"SkillLightning1", false);
			}
		}

		else if (m_pStateKey == L"Attack12" ||
				m_pStateKey == L"Attack22")
		{
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_LIGHTNING1, false);
			PlayState(L"SkillLightning2", false);
			m_HitBox.active = false;
			m_Info.vRender.x = -88;
			m_Info.vRender.y = 1;

			m_Skill = true;
			m_Range.active = true;
			m_Range.vOffset.x = 145;
			m_Range.vOffset.y = 10;
			m_Range.vScale.x = 140;
			m_Range.vScale.y = 60;
		}

		else if (
			m_pStateKey == L"DashBegin" ||
			m_pStateKey == L"Dash")
		{
			m_HitBox.active = false;
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_SWORD, false);
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_WIND, false);
			m_Skill = true;
			m_Info.vRender.x = -88;
			m_Info.vRender.y = -5;
			m_Range.vOffset.x = 125;
			m_Range.vOffset.y = 10;
			m_Range.vScale.x = 160;
			m_Range.vScale.y = 80;
			PlayState(L"SkillSlash1", false);
		}

		else if (
			m_pStateKey == L"FallBegin" ||
			m_pStateKey == L"Fall")
		{
			m_HitBox.active = false;
			m_Skill = true;
			m_Info.vRender.x = 0;
			m_Info.vRender.y = -20;

			m_Range.vOffset.x = 40;
			m_Range.vOffset.y = 60;
			m_Range.vScale.x = 60;
			m_Range.vScale.y = 160;

			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_ICE1, false);
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_HO, false);
			PlayState(L"SkillIce1", false);
		}

	}
}

void CPlayer::Damage(float att_)
{
	if (m_pStateKey != L"Init" &&
		m_pStateKey != L"Start" &&
		m_pStateKey != L"StartEnd")
	{
		m_RedHP = m_HP;
		PlayState(L"Hurt", true);
		GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_GROAN, false);
		m_HitBox.active = false;
		m_Jump = -3;
		m_fTimer = 0;

		m_HP -= att_;
		if (m_HP > m_MaxHP)
			m_HP = m_MaxHP;

		if (m_HP < 0)
		{
			Die();
		}
	}
}

void CPlayer::Die()
{
	GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_DEATH, false);
	m_HP = 0;
	m_Alive = false;
	m_HitBox.active = false;
	m_Range.active = false;
	
	PoolClip(L"FX", L"ExplodeL", 16, 30, false,
		D3DXVECTOR3(
			m_Info.vPos.x,
			m_Info.vPos.y,
			m_Info.vPos.z),
		D3DXVECTOR3(3.5, 3.5, 1)
	);
}

void CPlayer::StateMachine()
{
	if (m_pStateKey == L"Init")
	{
		m_Info.vPos.y += 15;
		if (CheckGround())
		{
			m_fHitTimer = 0;
			PlayState(L"Start", false);
		}
	}

	if (m_pStateKey == L"Start")
	{
		m_fTimer += GetTime();
		if (m_fTimer > 0.7f)
			PlayState(L"StartEnd", false);
	}

	if (m_pStateKey == L"StartEnd")
	{
		if (m_CharClip.bEndFrame)
		{
			m_HitBox.active = true;
			PlayState(L"Idle", false);
		}
	}

	if (m_pStateKey == L"Idle")
	{
		m_HitBox.vScale.x = 50;
		m_HitBox.vScale.y = 90;
		m_HitBox.vOffset.x = 0;
		m_HitBox.vOffset.y = 0;
	}

	if (m_pStateKey == L"WalkBegin")
	{
		m_HitBox.vScale.x = 50;
		m_HitBox.vScale.y = 90;
		m_HitBox.vOffset.x = 0;
		m_HitBox.vOffset.y = 0;
		if (m_CharClip.bEndFrame)
			PlayState(L"Walk", true);
	}

	if (m_pStateKey == L"JumpBegin")
	{
		m_HitBox.vScale.x = 50;
		m_HitBox.vScale.y = 90;
		m_HitBox.vOffset.x = 0;
		m_HitBox.vOffset.y = 0;
		if (m_CharClip.bEndFrame)
			PlayState(L"Jump", true);
	}

	if (m_pStateKey == L"Jump")
	{
		if (m_Jump > 0)
			PlayState(L"FallBegin", false);
	}

	if (m_pStateKey == L"FallBegin")
	{
		m_HitBox.vScale.x = 50;
		m_HitBox.vScale.y = 90;
		m_HitBox.vOffset.x = -5;
		m_HitBox.vOffset.y = 0;
		if (m_CharClip.bEndFrame)
			PlayState(L"Fall", true);
	}

	if (m_pStateKey == L"JumpAttack")
	{
		m_Range.vScale.x -= 0.3;

		m_HitBox.vScale.x = 50;
		m_HitBox.vScale.y = 90;
		m_HitBox.vOffset.x = -5;
		m_HitBox.vOffset.y = 0;
		if (m_CharClip.bEndFrame)
		{
			m_HitBox.active = true;
			m_Range.active = false;
			PlayState(L"Fall", true);
		}
	}

	if (m_pStateKey == L"FallEnd")
	{
		if (m_CharClip.bEndFrame)
			PlayState(L"Idle", false);
	}

	if (m_pStateKey == L"Attack11")
	{
		m_Range.vScale.y -= 4;
		m_Range.vOffset.y += 2;
		if (m_CharClip.bEndFrame)
		{
			if (!m_Hit)
				m_HitBox.active = true;
			PlayState(L"Attack12", false);
		}
			
	}

	if (m_pStateKey == L"Attack12")
	{
		m_Range.active = false;
		if (m_CharClip.bEndFrame)
			PlayState(L"AttackFinish", false);
	}
	
	if (m_pStateKey == L"Attack21")
	{
		m_Range.vScale.x -= 1.5f;
		m_Range.vOffset.x -= 0.75f;
		if (m_CharClip.bEndFrame)
		{
			if (!m_Hit)
				m_HitBox.active = true;
			PlayState(L"Attack22", false);
		}
			
	}

	if (m_pStateKey == L"Attack22")
	{
		m_Range.active = false;
		if (m_CharClip.bEndFrame)
			PlayState(L"AttackFinish", false);
	}

	if (m_pStateKey == L"Attack3")
	{
		m_Range.vScale.y -= 2.5f;
		m_Range.vOffset.y += 1.25f;
		if (m_CharClip.bEndFrame)
			PlayState(L"AttackFinish", false);
	}

	if (m_pStateKey == L"AttackFinish")
	{
		if (!m_Hit)
			m_HitBox.active = true;
		m_Range.active = false;
		if (m_CharClip.bEndFrame)
			PlayState(L"Idle", false);
	}

	if (m_pStateKey == L"DashBegin")
	{
		m_HitBox.vScale.x = 55;
		m_HitBox.vScale.y = 60;
		m_HitBox.vOffset.x = 15;
		m_HitBox.vOffset.y = 15;
		if (m_CharClip.bEndFrame)
			PlayState(L"Dash", true);
	}

	if (m_pStateKey == L"Dash")
	{
		m_HitBox.vScale.x = 90;
		m_HitBox.vOffset.x = 15;
	}

	if (m_pStateKey == L"DashEnd")
	{
		m_HitBox.vScale.x = 55;
		m_HitBox.vScale.y = 60;
		m_HitBox.vOffset.x = 15;
		m_HitBox.vOffset.y = 15;
		m_Skill = false;
		m_Speed = P_SPEED;
		if (m_CharClip.bEndFrame)
		{
			PlayState(L"Idle", false);
		}
	}

	if (m_pStateKey == L"Hurt")
	{
		m_Info.vRender.x = -35.0f;
		m_Info.vRender.y = 20;
		m_Range.active = false;
		m_Skill = false;
		m_Speed = P_SPEED;
		m_Info.vPos.x -= m_Info.vDir.x * 0.3f;
		m_fTimer += GetTime();
		if (m_fTimer > 0.55f)
		{
			PlayState(L"Idle", false);
			m_Hit = true;
			m_fHitTimer = 0;
		}
	}

	if (m_pStateKey == L"SlideBegin")
	{
		m_Range.active = false;
		m_Speed = P_SPEED;
		m_Jump = 0;
		if (m_CharClip.bEndFrame)
		{
			PlayState(L"Slide", true);
		}
	}

	if (m_pStateKey == L"Slide")
	{
		m_Jump = 1;
	}

	if (m_pStateKey == L"SlideJump")
	{
		m_Info.vRender.x = -35.0f;
		m_Info.vRender.y = 20;
		m_Info.vPos.x -= m_Speed * 2 * m_Info.vDir.x;
		if (m_CharClip.bEndFrame)
		{
			PlayState(L"Jump", true);
		}
	}
	
	if (m_pStateKey == L"SkillFire1")
	{
		if (m_CharClip.bEndFrame)
		{
			PlayState(L"SkillFire2", false);
		}
	}

	if (m_pStateKey == L"SkillFire2")
	{
		if (m_CharClip.bEndFrame)
		{
			if (!m_Hit)
				m_HitBox.active = true;
			m_Range.active = false;
			PlayState(L"SkillFire3", false);
		}
	}

	if (m_pStateKey == L"SkillFire3")
	{
		if (m_CharClip.bEndFrame)
		{
			PlayState(L"Fall", true);
			m_Info.vRender.x = -35.0f;
			m_Info.vRender.y = 20;
			m_Skill = false;
		}
	}

	if (m_pStateKey == L"SkillIce1")
	{
		if (m_CharClip.bEndFrame)
		{
			m_Range.active = true;
			PlayState(L"SkillIce2", true);
		}
	}

	if (m_pStateKey == L"SkillIce3")
	{
		if (m_CharClip.bEndFrame)
		{
			if (!m_Hit)
				m_HitBox.active = true;
			m_Range.active = false;
			m_Speed = P_SPEED;
			m_Info.vRender.x = -35.0f;
			m_Info.vRender.y = 20;
			m_Skill = false;
			PlayState(L"Idle", false);
		}
	}

	if (m_pStateKey == L"SkillLightning1")
	{
		if (m_CharClip.bEndFrame)
		{
			m_Range.active = true;
			m_Range.vOffset.x = 145;
			m_Range.vOffset.y = 10;
			m_Range.vScale.x = 140;
			m_Range.vScale.y = 60;
			PlayState(L"SkillLightning2", false);
		}
	}

	if (m_pStateKey == L"SkillLightning2")
	{
		GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_LIGHTNING2, false);
		m_Range.vOffset.x += 0.5;
		m_Range.vScale.x += 1;
		if (m_CharClip.bEndFrame)
		{
			if (!m_Hit)
				m_HitBox.active = true;
			m_Range.active = false;
			PlayState(L"SkillLightning3", false);
		}
	}

	if (m_pStateKey == L"SkillLightning3")
	{
		if (m_CharClip.bEndFrame)
		{
			m_Info.vRender.x = -35.0f;
			m_Info.vRender.y = 20;
			m_Skill = false;
			PlayState(L"Idle", true);
		}
	}

	if (m_pStateKey == L"SkillSlash1")
	{
		m_Info.vPos.x += m_Info.vDir.x * 3;
		if (m_CharClip.bEndFrame)
		{
			m_Range.active = true;
			PlayState(L"SkillSlash2", false);
		}
	}

	if (m_pStateKey == L"SkillSlash2")
	{
		m_Info.vPos.x += m_Info.vDir.x * 2;
		if (m_CharClip.bEndFrame)
		{
			if (!m_Hit)
				m_HitBox.active = true;
			m_Range.active = false;
			PlayState(L"SkillSlash3", false);
		}
	}

	if (m_pStateKey == L"SkillSlash3")
	{
		m_Info.vPos.x += m_Info.vDir.x;
		if (m_CharClip.bEndFrame)
		{
			m_Info.vRender.x = -35.0f;
			m_Info.vRender.y = 20;
			PlayState(L"DashEnd", false);
		}
	}
}

void CPlayer::CheckCollision()
{
	bool left, right; 
	left = CheckLeft();
	right = CheckRight();

	if (m_Hit)
	{
		m_fHitTimer += GetTime();
		if (m_fHitTimer > 1.0f)
		{
			m_HitBox.active = true;
			m_Hit = false;
		}
	}
	m_Jump += GRAVITY;
	m_Info.vPos.y += m_Jump;

	if (m_Jump > 1 &&
		(m_pStateKey == L"Walk" ||
		m_pStateKey == L"Idle" ||
		m_pStateKey == L"DashBegin" ||
		m_pStateKey == L"Dash"))
	{
		PlayState(L"FallBegin", false);
		m_Speed = P_SPEED;
	}

	if ((m_Info.vDir.x < 0 && left) ||
		(m_Info.vDir.x > 0 && right))
	{
		if (m_pStateKey == L"Walk" ||
			m_pStateKey == L"WalkBegin")
		{
			PlayState(L"Idle", false);
		}

		if (m_pStateKey == L"DashBegin" ||
			m_pStateKey == L"Dash")
		{
			PlayState(L"DashEnd", false);
		}

		if (m_pStateKey == L"Jump" ||
			m_pStateKey == L"FallBegin" ||
			m_pStateKey == L"Fall" ||
			m_pStateKey == L"JumpAttack")
		{
			if (!m_Hit)
				m_HitBox.active = true;
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_SLIDE_HIT, false);
			PlayState(L"SlideBegin", false);
			m_Info.vRender.x = -20;
			m_Info.vRender.y = 25;
		}
	}

	if (m_pStateKey == L"Slide")
	{
		if (!left && m_Info.vDir.x < 0)
		{
			PlayState(L"FallBegin", false);
			m_Info.vRender.x = -35.0f;
			m_Info.vRender.y = 20;	
		}
			
		if (!right && m_Info.vDir.x > 0)
		{
			PlayState(L"FallBegin", false);
			m_Info.vRender.x = -35.0f;
			m_Info.vRender.y = 20;
		}
			
	}
	
	if (m_Jump > 0.0f && CheckGround())
	{
		if (m_pStateKey == L"FallStart" ||
			m_pStateKey == L"Fall" ||
			m_pStateKey == L"JumpAttack" ||
			m_pStateKey == L"Slide")
		{
			if (!m_Hit)
				m_HitBox.active = true;
			m_Range.active = false;
			m_Speed = P_SPEED;
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_LAND, false);
			PlayState(L"FallEnd", false);
		}

		else if (m_pStateKey == L"SkillIce2")
		{
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_ICE2, false);
			m_Range.vOffset.y = 30;
			m_Range.vScale.x = 150;
			m_Range.vScale.y = 80;

			m_Speed = 0;
			PlayState(L"SkillIce3", false);
		}
	}

	if (CheckCeiling() && m_pStateKey == L"SkillFire2")
	{
		PlayState(L"SkillFire3", false);
		m_Info.vRender.x = -35.0f;
		m_Info.vRender.y = 20;
	}
}

void CPlayer::MapState()
{
	m_MapState.insert(make_pair(L"Init", 1));
	m_MapState.insert(make_pair(L"Start", 13));
	m_MapState.insert(make_pair(L"StartEnd", 2));

	m_MapState.insert(make_pair(L"Idle", 1));

	m_MapState.insert(make_pair(L"WalkBegin", 2));
	m_MapState.insert(make_pair(L"Walk", 14));

	m_MapState.insert(make_pair(L"JumpBegin", 2));
	m_MapState.insert(make_pair(L"Jump", 2));
	m_MapState.insert(make_pair(L"JumpAttack", 9));

	m_MapState.insert(make_pair(L"FallBegin", 4));
	m_MapState.insert(make_pair(L"Fall", 3));
	m_MapState.insert(make_pair(L"FallEnd", 4));

	m_MapState.insert(make_pair(L"Attack11", 6));
	m_MapState.insert(make_pair(L"Attack12", 6));
	m_MapState.insert(make_pair(L"Attack21", 5));
	m_MapState.insert(make_pair(L"Attack22", 6));
	m_MapState.insert(make_pair(L"Attack3", 14));
	m_MapState.insert(make_pair(L"AttackFinish", 4));

	m_MapState.insert(make_pair(L"DashBegin", 4));
	m_MapState.insert(make_pair(L"Dash", 3));
	m_MapState.insert(make_pair(L"DashEnd", 4));

	m_MapState.insert(make_pair(L"Hurt", 6));

	m_MapState.insert(make_pair(L"End", 7));
	m_MapState.insert(make_pair(L"EndBegin", 7));

	m_MapState.insert(make_pair(L"SlideBegin", 3));
	m_MapState.insert(make_pair(L"Slide", 2));
	m_MapState.insert(make_pair(L"SlideJump", 3));

	m_MapState.insert(make_pair(L"SkillFire1", 2));
	m_MapState.insert(make_pair(L"SkillFire2", 12));
	m_MapState.insert(make_pair(L"SkillFire3", 2));

	m_MapState.insert(make_pair(L"SkillIce1", 2));
	m_MapState.insert(make_pair(L"SkillIce2", 2));
	m_MapState.insert(make_pair(L"SkillIce3", 5));

	m_MapState.insert(make_pair(L"SkillLightning1", 7));
	m_MapState.insert(make_pair(L"SkillLightning2", 13));
	m_MapState.insert(make_pair(L"SkillLightning3", 4));

	m_MapState.insert(make_pair(L"SkillSlash1", 2));
	m_MapState.insert(make_pair(L"SkillSlash2", 4));
	m_MapState.insert(make_pair(L"SkillSlash3", 5));
}

HRESULT CPlayer::Initialize()
{
	GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_BEGIN, false);
	MapState();
	m_eSortID = E_SORTID_THIRD;
	m_tPlatform = 
		((CPlatform*)(GET_SINGLE(CObjMgr)->GetObj(L"Platform")))->GetPlatform();
	
	m_Info.vPos.x = 1000;

	m_CharClip.fSpeed = 28;
	m_CharClip.pObject = L"Zero";
	PlayState(L"Init", false);

	m_HitBox.vScale.x = 40;
	m_HitBox.vScale.y = 90;
	m_Info.vPos.y = 0;
	m_Info.vDir.x = 1;

	m_Info.vRender.x = -35.0f; 
	m_Info.vRender.y = 20.0f,

	m_pAStar = new CAstar;

	return S_OK;
}

E_SCENE CPlayer::Progress()
{
	SpriteAnimation(&m_CharClip);
	list<CLIP*>::iterator it;
	for (it = m_FXClips.begin(); it != m_FXClips.end(); it++)
	{
		SpriteAnimation((*it));
	}


	if (GetKeyBoardState(DIK_SPACE) == E_INPUT_DOWN)
		m_showBox = !m_showBox;

	m_HitBox.vPos = m_Info.vPos;
	if (m_Alive)
	{
		CheckCollision();
		KeyCheck();
		StateMachine();
	}

	GET_SINGLE(CCamMgr)->FollowCam(&m_Info);
	
	TransformMatrix();

	return E_SCENE_NONPASS;
}

void CPlayer::Render()
{
	if (m_Alive)
	{
		const TEXINFO* TexInfo =
			GET_SINGLE(CTextureMgr)->GetTexture(
				m_CharClip.pObject,
				m_CharClip.pState,
				int(m_CharClip.fFrame));

		if (TexInfo == NULL)
			return;

		m_Info.vCenter = D3DXVECTOR3(
			TexInfo->ImgInfo.Width / 2.f + m_Info.vRender.x,
			TexInfo->ImgInfo.Height / 2.f + m_Info.vRender.y,
			0.0f);

		D3DCOLOR hit;
		if (m_Hit && ((int)(m_fHitTimer * 1000)) % 2 == 0)
			hit = D3DCOLOR_ARGB(80, 255, 255, 255);
		else hit = D3DCOLOR_ARGB(255, 255, 255, 255);

		GetSprite()->SetTransform(&m_Info.matWorld);
		GetSprite()->Draw(TexInfo->pTexture, NULL,
			&m_Info.vCenter, NULL, hit);
	}

	RenderFX();
	RenderBoxes();
	RenderBars();
	//DebugLog();
}

void CPlayer::RenderBars()
{
	float fX = 60, fY = 160;
	const TEXINFO* TexInfo; 
	D3DXMATRIX matTrans, matScale;

	TexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"HPBar");
	m_Info.vCenter = D3DXVECTOR3(
		TexInfo->ImgInfo.Width / 2.f,
		TexInfo->ImgInfo.Height,
		0.0f);

	D3DXMatrixTranslation(&matTrans, fX - 13, fY + 48, 0);
	D3DXMatrixScaling(&matScale, 1, m_RedHP / m_MaxHP, 1);
	m_Info.matWorld = matScale * matTrans;
	if (m_RedHP > m_HP)
		m_RedHP -= 0.2f;
	GetSprite()->SetTransform(&m_Info.matWorld);
	GetSprite()->Draw(TexInfo->pTexture, NULL,
		&m_Info.vCenter, NULL, D3DCOLOR_ARGB(180, 255, 0, 0));

	float ratio = m_HP / m_MaxHP;
	D3DXMatrixTranslation(&matTrans, fX - 13, fY + 48, 0);
	D3DXMatrixScaling(&matScale, 1, ratio, 1);
	m_Info.matWorld = matScale * matTrans;
	GetSprite()->SetTransform(&m_Info.matWorld);
	GetSprite()->Draw(TexInfo->pTexture, NULL,
		&m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255 - (int)(ratio * 255), 255, 0));


	TexInfo = GET_SINGLE(CTextureMgr)->GetTexture(L"HPContainer");
	m_Info.vCenter = D3DXVECTOR3(
		TexInfo->ImgInfo.Width / 2.f,
		TexInfo->ImgInfo.Height / 2.f,
		0.0f);

	D3DXMatrixTranslation(&matTrans, fX, fY, 0);
	D3DXMatrixScaling(&matScale, 1, 1, 1);

	m_Info.matWorld = matScale * matTrans;

	GetSprite()->SetTransform(&m_Info.matWorld);
	GetSprite()->Draw(TexInfo->pTexture, NULL,
		&m_Info.vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}



void CPlayer::DebugLog()
{
	D3DXMATRIX matWorld, matScale, matTrans;
	D3DXMatrixTranslation(&matTrans,
		10,
		10,
		1);
	D3DXMatrixScaling(&matScale, 1, 1, 1);
	matWorld = matScale * matTrans;

	GetSprite()->SetTransform(&matWorld);

	TCHAR wcTmp[128];
	RECT rcFont = { 0, };
	swprintf(wcTmp, 128, L"Jump: %f", m_Jump);
	GetFont()->DrawTextW(GetSprite(), wcTmp, lstrlen(wcTmp),
		&rcFont, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 0));

	D3DXMatrixTranslation(&matWorld, 10, 40, 0);
	GetSprite()->SetTransform(&matWorld);
	swprintf(wcTmp, 128, L"CamX: %f", GET_SINGLE(CCamMgr)->GetCam().x);
	GetFont()->DrawTextW(GetSprite(), wcTmp, lstrlen(wcTmp),
		&rcFont, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 0));
}

void CPlayer::Release()
{
	SAFE_DELETE(m_pAStar);
}

CObj* CPlayer::Clone()
{
	return new CPlayer(*this);
}

