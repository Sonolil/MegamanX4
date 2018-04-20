#include "stdafx.h"
#include "Obj.h"
#include "ObjMgr.h"


CObj::CObj()
{
}


CObj::CObj(const INFO& Info)
	:m_Info(Info), m_fAngle(0.f), m_pAStar(NULL), m_fTimer(0.0f)
{

}

CObj::~CObj()
{

}

void CObj::PoolClip(TCHAR* obj_, TCHAR* state_, 
	int maxFrame_, float speed_, bool repeat_,
	D3DXVECTOR3 initPos_, D3DXVECTOR3 initScale_)
{
	bool found = false;
	list<CLIP*>::iterator it;
	for (it = m_FXClips.begin(); it != m_FXClips.end(); ++it)
	{
		if ((*it)->bActive)
			continue;

		else 
		{
			(*it)->vPos = initPos_;
			(*it)->vScale = initScale_;
			(*it)->bRepeat = repeat_;
			(*it)->iMaxFrame = maxFrame_;
			(*it)->fSpeed = speed_;
			(*it)->pObject = obj_;
			(*it)->pState = state_;

			(*it)->fFrame = 0;
			(*it)->bEndFrame = false;
			(*it)->bActive = true;
			found = true;
			break;
		}
	}

	if (!found)
	{
		CLIP* clip = new CLIP();
		clip->vPos = initPos_;
		clip->vScale = initScale_;
		clip->bRepeat = repeat_;
		clip->iMaxFrame = maxFrame_;
		clip->fSpeed = speed_;
		clip->pObject = obj_;
		clip->pState = state_;

		m_FXClips.push_back(clip);
	}
}

void CObj::SpriteAnimation(CLIP * clip)
{
	clip->fFrame += clip->fSpeed * GetTime();

	if (clip->fFrame > clip->iMaxFrame)
	{
		if (clip->bRepeat)
			clip->fFrame = 0;

		else
		{
			clip->fFrame = clip->iMaxFrame - 1;
			clip->bActive = false;
		}

		clip->bEndFrame = true;
	}

	else clip->bEndFrame = false;
}
