#include "stdafx.h"
#include "PhysMgr.h"


bool CPhysMgr::HitVertical(const BOX* box1, const BOX* box2)
{
	float right1, left1, right2, left2; 
	
	left1 = box1->vPos.x -
		box1->vScale.x / 2 + box1->vOffset.x * box1->vDir.x;
	right1 = box1->vPos.x +
		box1->vScale.x / 2 + box1->vOffset.x * box1->vDir.x;
	left2 = box2->vPos.x -
		box2->vScale.x / 2 + box2->vOffset.x * box2->vDir.x;
	right2 = box2->vPos.x +
		box2->vScale.x / 2 + box2->vOffset.x * box2->vDir.x;
	
	if (left1 < right2 && right1 > left2)
		return true;

	return false;
}

bool CPhysMgr::HitHorizontal(const BOX* box1, const BOX* box2)
{
	float bottom1, top1, bottom2, top2;

	top1 = box1->vPos.y -
		box1->vScale.y / 2 + box1->vOffset.y;
	bottom1 = box1->vPos.y +
		box1->vScale.y / 2 + box1->vOffset.y;
	top2 = box2->vPos.y -
		box2->vScale.y / 2 + box2->vOffset.y;
	bottom2 = box2->vPos.y +
		box2->vScale.y / 2 + box2->vOffset.y;

	if (top1 < bottom2 && bottom1 > top2)
		return true;

	return false;
}

bool CPhysMgr::HitTest(const BOX * box1, const BOX * box2)
{
	bool hori, verti;
	hori = HitHorizontal(box1, box2);
	verti = HitVertical(box1, box2);

	if (hori && verti)
		return true;
	return false;
}

bool CPhysMgr::HitLeft(const BOX* obj, const BOX* platform)
{
	bool hori = HitHorizontal(obj, platform);

	float pRight, oLeft;
	pRight = platform->vPos.x +
		platform->vScale.x / 2;
	oLeft = obj->vPos.x -
		obj->vScale.x / 2;

	if (pRight > oLeft &&
		pRight < oLeft + 25.0f &&
		hori)
		return true;

	return false;
}

bool CPhysMgr::HitRight(const BOX* obj, const BOX* platform)
{
	bool hori = HitHorizontal(obj, platform);

	float oRight, pLeft;
	oRight = obj->vPos.x +
		obj->vScale.x / 2;
	pLeft = platform->vPos.x -
		platform->vScale.x / 2;

	if (oRight > pLeft &&
		oRight < pLeft + 25.0f &&
		hori)
		return true;

	return false;
}

bool CPhysMgr::HitGround(const BOX * obj, const BOX * platform)
{
	bool verti = HitVertical(obj, platform);

	float oFeet, pTop;
	oFeet = obj->vPos.y +
			obj->vScale.y / 2 + obj->vOffset.y;
	pTop =  platform->vPos.y -
			platform->vScale.y / 2 + platform->vOffset.y;

	if (oFeet > pTop &&
		oFeet < pTop + 25.0f &&
		verti)
		return true;

	return false;
}

bool CPhysMgr::HitCeiling(const BOX* obj, const BOX* platform)
{
	bool verti = HitVertical(obj, platform);

	float pFeet, oTop;
	pFeet = platform->vPos.y +
			platform->vScale.y / 2 + platform->vOffset.y;
	oTop =  obj->vPos.y -
			obj->vScale.y / 2 + obj->vOffset.y;

	if (pFeet > oTop &&
		pFeet < oTop + 25.0f &&
		verti)
		return true;

	return false;
}

CPhysMgr::CPhysMgr()
{

}

CPhysMgr::~CPhysMgr()
{

}

