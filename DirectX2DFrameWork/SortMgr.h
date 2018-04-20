#pragma once
#include "Defines.h"
#include "Obj.h"

class CSortMgr
{
	DECLARE_SINGLETON(CSortMgr);
private:
	list<CObj*> m_ObjList[E_SORTID_END];
public:
	void AddSortObject(CObj* pObj);
	void RenderObject();
	void Release();
private:
	CSortMgr();
public:
	~CSortMgr();
};

