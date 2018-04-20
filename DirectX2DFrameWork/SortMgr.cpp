#include "stdafx.h"
#include "SortMgr.h"

CSortMgr::CSortMgr()
{
}


CSortMgr::~CSortMgr()
{
	this->Release();
}

void CSortMgr::AddSortObject(CObj* pObj)
{
	E_SORTID ID = pObj->GetSortID();

	m_ObjList[ID].push_back(pObj);
}

void CSortMgr::RenderObject()
{
	for (int i = 0; i < E_SORTID_END; ++i)
	{
		for (list<CObj*>::iterator iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->Render();
		}
		m_ObjList[i].clear();
	}
}

void CSortMgr::Release()
{
	for (int i = 0; i < E_SORTID_END; ++i)
	{
		m_ObjList[i].clear();
	}
}

