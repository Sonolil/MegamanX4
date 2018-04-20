#pragma once
#include "Include.h"
#include "Prototype.h"
#include "SortMgr.h"
#include "ObjMgr.h"

class CSceneObj
{
protected:
	CPrototype* m_pPrototype;
	float m_fSceneTime;
public:
	virtual HRESULT Initialize()PURE;
	virtual E_SCENE Progress()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;
public:
	CSceneObj();
	virtual ~CSceneObj();
};

