#include "stdafx.h"
#include "ObjMgr.h"
#include "ObjProto.h"
#include "Tile.h"

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	this->Release();
}

const INFO* CObjMgr::GetInfo(const TCHAR* pObject, const int& iCnt)
{
	map<const TCHAR*, list<CObj*>>::iterator iter = m_MapObject.find(pObject);

	if (iter == m_MapObject.end())
		return NULL;

	list<CObj*>::iterator iteri = iter->second.begin();

	for (int i = 0; i < iCnt; ++i)
		++iteri;

	return (*iteri)->GetInfo();
}

CObj* CObjMgr::GetObj(const TCHAR * pObject, const int & iCnt)
{
	map<const TCHAR*, list<CObj*>>::iterator iter = m_MapObject.find(pObject);

	if (iter == m_MapObject.end())
		return NULL;

	list<CObj*>::iterator iteri = iter->second.begin();
	for (int i = 0; i < iCnt; ++i)
		++iteri;

	return (*iteri);
}

const vector<TILE*>* CObjMgr::GetTileInfo()
{
	map<const TCHAR*, list<CObj*>>::iterator iter = m_MapObject.find(L"StageTile");

	if (iter == m_MapObject.end())
	{
		ERR_MSG(g_hWnd, L"find(StageTile) Failed !");
		return NULL;
	}

	return ((CTile*)(iter->second.front()))->GetTileInfo();
}

HRESULT CObjMgr::AddObject(CPrototype* pProto, const TCHAR* pObject)
{
	map<const TCHAR*, list<CObj*>>::iterator iter = m_MapObject.find(pObject);

	CObj* pProtoInst = ((CObjProto*)pProto)->GetProto(pObject);

	if (pProtoInst == NULL)
		return E_FAIL;

	CObj* pObj = pProtoInst->Clone();
	pObj->Initialize();

	if (iter == m_MapObject.end())	//키값을 못찾았다면
	{
		list<CObj*> ObjList;
		ObjList.push_back(pObj);

		m_MapObject.insert(make_pair(pObject, ObjList));
	}
	
	else							//키값이 이미 있었다면
	{
		iter->second.push_back(pObj);
	}

	return S_OK;
}

E_SCENE CObjMgr::Progress()
{
	for (map<const TCHAR*, list<CObj*>>::iterator iter = m_MapObject.begin();
		iter != m_MapObject.end(); ++iter)
	{
		for (list<CObj*>::iterator iteri = iter->second.begin();
			iteri != iter->second.end(); ++iteri)
		{
			E_SCENE SceneID = (*iteri)->Progress();

			if (SceneID >= 0)
				return SceneID;

			GET_SINGLE(CSortMgr)->AddSortObject(*iteri);
		}
	}

	return E_SCENE_NONPASS;
}

void CObjMgr::Render()
{
	GET_SINGLE(CSortMgr)->RenderObject();
}

void CObjMgr::Release()
{
	for (map<const TCHAR*, list<CObj*>>::iterator iter = m_MapObject.begin();
		iter != m_MapObject.end(); ++iter)
	{
		for (list<CObj*>::iterator iteri = iter->second.begin();
			iteri != iter->second.end(); ++iteri)
		{
			SAFE_DELETE(*iteri);
		}
		iter->second.clear();
	}
	m_MapObject.clear();
}