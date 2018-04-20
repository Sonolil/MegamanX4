#pragma once
#include "Include.h"
#include "SceneObj.h"
#include "Logo.h"
#include "Stage.h"
#include "BossStage.h"

class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr);
private:
	CSceneObj* m_pSceneObj;
public:
	HRESULT InitScene(E_SCENE Scene);
	void Progress();
	void Render();
	void Release();
private:
	CSceneMgr();
public:
	~CSceneMgr();
};

