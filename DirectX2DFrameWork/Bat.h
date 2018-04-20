#pragma once
#include "StageDynamic.h"
#include "Player.h"

class CBat : public CStageDynamic
{
protected:
	bool m_bInit, m_Hit, m_Block;
	float m_Regen;
	D3DXVECTOR3 m_InitPos;
	CPlayer* m_Player;
public:
	void AIMachine();
	void ResetState();
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
	CBat();
	CBat(const INFO& Info);
	~CBat();
};

