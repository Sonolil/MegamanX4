#include "stdafx.h"
#include "CamMgr.h"

CCamMgr::CCamMgr()
	:m_vCam(WINSIZEX / 2, WINSIZEY / 2)
{

}

CCamMgr::~CCamMgr()
{

}

void CCamMgr::SetCam(float x_, float y_)
{
	m_vCam = D3DXVECTOR2(x_, y_);
	Relocate();
}

void CCamMgr::AddCam(float x_, float y_)
{
	m_vCam.x += x_;
	m_vCam.y += y_;
	Relocate();
}

void CCamMgr::FollowCam(INFO* m_Info)
{
	SetCam(
		m_Info->vPos.x,
		m_Info->vPos.y
	);
	Relocate();
}

void CCamMgr::Relocate()
{
	if (m_vCam.x < WINSIZEX / 2)
		m_vCam.x = WINSIZEX / 2;

	else if (m_vCam.x > STAGEX - WINSIZEX / 2)
		m_vCam.x = STAGEX - WINSIZEX / 2;


	if (m_vCam.y < STAGEY / 2 - 200)
		m_vCam.y = STAGEY / 2 - 200;

	else if (m_vCam.y > STAGEY / 2)
		m_vCam.y = STAGEY / 2;
	
}
