#pragma once
#include "Include.h"
#include "SceneMgr.h"

class CMainGame
{
private:
	float m_fPlayTime;
	float m_fFrameTime;
	int m_iFrameCount;
public:
	HRESULT Initialize();
	void Progress();
	void Render();
	void Release();
public:
	CMainGame();
	~CMainGame();
};

