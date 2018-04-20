#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr::CSceneMgr()
	:m_pSceneObj(NULL)
{

}

CSceneMgr::~CSceneMgr()
{
	this->Release();
}

HRESULT CSceneMgr::InitScene(E_SCENE Scene)
{
	SAFE_DELETE(m_pSceneObj);

	switch (Scene)
	{
		case E_SCENE_LOGO:
			m_pSceneObj = new CLogo;
			break;
		case E_SCENE_STAGE:
			m_pSceneObj = new CStage;
			break;
		case E_SCENE_BOSSSTAGE:
			m_pSceneObj = new CBossStage;
			break;
	}

	if (FAILED(m_pSceneObj->Initialize()))
	{
		ERR_MSG(g_hWnd, L"InitScene() Failed !");
		SAFE_DELETE(m_pSceneObj);
		return E_FAIL;
	}

	return S_OK;
}

void CSceneMgr::Progress()
{
	E_SCENE SceneID = m_pSceneObj->Progress();

	if (SceneID >= 0)
		InitScene(SceneID);
}

void CSceneMgr::Render()
{
	m_pSceneObj->Render();
}

void CSceneMgr::Release()
{
	SAFE_DELETE(m_pSceneObj);
}

