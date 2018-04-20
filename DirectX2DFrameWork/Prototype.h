#pragma once
#include "Defines.h"

class CPrototype
{
public:
	virtual HRESULT InitProtoInstance()PURE;
	virtual void Release()PURE;
public:
	CPrototype();
	virtual ~CPrototype();
};

