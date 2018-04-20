#pragma once
#include "Defines.h"
#include "Obj.h"
#include "Prototype.h"


class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr);
private:
	map<const TCHAR*, list<CObj*>> m_MapObject;
public:
	const vector<TILE*>* GetTileInfo();
public:
	HRESULT AddObject(CPrototype* pProto, const TCHAR* pObject);
	E_SCENE Progress();
	void Render();
	void Release();
public:
	const INFO* GetInfo(const TCHAR* pObject, const int& iCnt = 0);
	CObj* GetObj(const TCHAR* pObject, const int& iCnt = 0);
private:
	CObjMgr();
public:
	~CObjMgr();
};

