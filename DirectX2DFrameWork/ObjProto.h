#pragma once
#include "Prototype.h"
#include "Obj.h"

class CObjProto : public CPrototype
{
protected:
	map<const TCHAR*, CObj*> m_MapProto;
public:
	CObj* GetProto(const TCHAR* pObjKey);
public:
	virtual HRESULT InitProtoInstance()PURE;
	virtual void Release();
public:
	CObjProto();
	~CObjProto();
};

