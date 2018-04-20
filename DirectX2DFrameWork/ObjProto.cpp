#include "stdafx.h"
#include "ObjProto.h"

CObjProto::CObjProto()
{
}


CObjProto::~CObjProto()
{
	Release();
}

CObj* CObjProto::GetProto(const TCHAR* pObjKey)
{
	map<const TCHAR*, CObj*>::iterator iter = m_MapProto.find(pObjKey);

	if (iter == m_MapProto.end())	// 찾지 못했다.
	{
		ERR_MSG(g_hWnd, L"m_MapProto.find() Failed !");
		return NULL;
	}

	return iter->second;
}

void CObjProto::Release()
{
	for (map<const TCHAR*, CObj*>::iterator iter = m_MapProto.begin();
		iter != m_MapProto.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_MapProto.clear();
}

