#pragma once
#include "Obj.h"
#include "SortMgr.h"

class CStageStatic : public CObj
{
protected:
public:
	virtual HRESULT Initialize()PURE;
	virtual E_SCENE Progress()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;
	virtual CObj* Clone()PURE;
public:
	CStageStatic();
	CStageStatic(const INFO& Info);
	~CStageStatic();
};

