#pragma once
#include "Obj.h"
#include "GameInclude.h"
#include "Astar.h"

class CStageDynamic : public CObj
{
protected:
	map<const TCHAR*, const int> m_MapState;
	list<BOX*>* m_tPlatform;
protected:
	COLLISION m_Collision;
	float m_Jump, m_Speed;
	float m_HP, m_MaxHP, m_Att;
	float m_fHitTimer;
	bool m_Hit, m_Alive, m_showBox;
public:
	void PlayState(TCHAR* state_, bool repeat_);
public:
	float GetAtt() { return m_Att; }
protected:
	virtual bool CheckGround();
	virtual bool CheckCeiling();
	virtual bool CheckLeft();
	virtual bool CheckRight();
	virtual void TransformMatrix();
	virtual void RenderBoxes();
	virtual void RenderFX();
public:
	virtual HRESULT Initialize()PURE;
	virtual E_SCENE Progress()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;
	virtual CObj* Clone()PURE;
public:
	virtual void MapState()PURE;
	virtual void Damage(float att_)PURE;
public:
	CStageDynamic();
	CStageDynamic(const INFO& Info);
	~CStageDynamic();
};

