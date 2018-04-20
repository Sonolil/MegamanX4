#pragma once
#include "Defines.h"
#include "Obj.h"
#include "StageDynamic.h"

class CPhysMgr
{
	DECLARE_SINGLETON(CPhysMgr);
private:
	D3DXVECTOR2 m_vCam;
private:
	bool HitVertical(const BOX* box1, const BOX* box2);
	bool HitHorizontal(const BOX* box1, const BOX* box2);
public:
	bool HitTest(const BOX* box1, const BOX* box2);
	bool HitLeft(const BOX * obj, const BOX * platform);
	bool HitRight(const BOX * obj, const BOX * platform);
	bool HitGround(const BOX* obj, const BOX* platform);
	bool HitCeiling(const BOX* obj, const BOX* platform);
	
private:
	CPhysMgr();
public:
	~CPhysMgr();
};

