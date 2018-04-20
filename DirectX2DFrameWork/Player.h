#pragma once
#include "StageDynamic.h"

class CPlayer : public CStageDynamic
{
private:
	E_PLAYER_STATE m_pState;
	float m_RedHP;
	bool m_TestHit, m_Skill;
public:
	void KeyCheck();
	void StateMachine();
	void CheckCollision();
	void DebugLog();
	void RenderBars();
	void Die();
public:
	virtual void MapState();
	virtual void Damage(float att_);
public:
	virtual HRESULT Initialize();
	virtual E_SCENE Progress();
	virtual void Render();
	virtual void Release();
	virtual CObj* Clone();
public:
	CPlayer();
	CPlayer(const INFO& Info);
	virtual ~CPlayer();
};

