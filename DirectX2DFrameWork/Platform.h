#pragma once
#include "StageStatic.h"

class CPlatform : public CStageStatic
{
public:
	bool testHit, m_showBox;
	vector<ANIM*> m_parallax;
	int paraCount = 5;
	list<BOX*> m_tPlatform;
	list<BOX*>::iterator it;
private:
	void CreatePlatform(D3DXVECTOR3 vPos, D3DXVECTOR3 vScale);
	void DrawParallax(TCHAR* text, 
		float transX, float transY, float scaleX, float scaleY,
		float parallaxRate, float m_parallax);
	void Draw(TCHAR* text,
		float transX, float transY, float scaleX, float scaleY);
	void MapState();
	void DrawPlatform();
	void DrawBackground();
public:
	list<BOX*>* GetPlatform() { return &m_tPlatform; }
public:
	virtual HRESULT Initialize();
	virtual E_SCENE Progress();
	virtual void Render();
	virtual void Release();
	virtual CObj* Clone();
public:
	CPlatform();
	CPlatform(const INFO& info);
	~CPlatform();
};

