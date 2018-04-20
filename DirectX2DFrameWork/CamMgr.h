#pragma once
#include "Defines.h"

class CCamMgr
{
	DECLARE_SINGLETON(CCamMgr);
private:
	D3DXVECTOR2 m_vCam;
public:
	void SetCam(float x_, float y_);
	void AddCam(float x_, float y_);
	void FollowCam(INFO* m_Info);
	void Relocate();
	D3DXVECTOR2 GetCam(){ return m_vCam; }
private:
	CCamMgr();
public:
	~CCamMgr();
};

