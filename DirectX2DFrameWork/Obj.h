#pragma once
#include "Include.h"
#include "TextureMgr.h"
#include "CamMgr.h"
#include "Astar.h"

class CObj
{
protected:
	INFO m_Info;
	E_SORTID m_eSortID;
	CLIP m_CharClip;
	list<CLIP*> m_FXClips;
	TCHAR *m_pStateKey;
	float m_fAngle, m_fTimer;
	BOX m_HitBox, m_Range;
	CAstar* m_pAStar;

public:
	void SpriteAnimation(CLIP* clip);
	void PoolClip(TCHAR* obj_, TCHAR* state_, 
		int maxFrame, float speed_, bool repeat_,
		D3DXVECTOR3 initPos_, D3DXVECTOR3 initScale_);
public:
	E_SORTID GetSortID() { return m_eSortID; }
	const INFO* GetInfo(){ return &m_Info; }
	BOX* GetHitBox() { return &m_HitBox; }
	BOX* GetRange() { return &m_Range; }
public:
	virtual HRESULT Initialize()PURE;
	virtual E_SCENE Progress()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;
	virtual CObj* Clone()PURE;
public:
	CObj();
	CObj(const INFO& Info);
	virtual ~CObj();
};

