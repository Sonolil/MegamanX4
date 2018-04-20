#include "stdafx.h"
#include "MainGame.h"

CMainGame::CMainGame()
	:m_fPlayTime(0.f), m_fFrameTime(0.f), m_iFrameCount(0)
{
}

CMainGame::~CMainGame()
{
	this->Release();
}

HRESULT CMainGame::Initialize()
{
	// Device Init
	if (FAILED(InitDevice(E_WINMODE_WIN, g_hWnd, WINSIZEX, WINSIZEY)))
	{
		ERR_MSG(g_hWnd, L"InitDevice() Failed !");
		return E_FAIL;
	}

	// Timer Init
	InitTimer();

	// KeyInput Init
	if (FAILED(InitInputDevice(g_hWnd, hInst)))
	{
		ERR_MSG(g_hWnd, L"InitInputDevice() Failed !");
		return E_FAIL;
	}

	// Init Scene
	if (FAILED(GET_SINGLE(CSceneMgr)->InitScene(E_SCENE_STAGE)))
	{
		ERR_MSG(g_hWnd, L"CMainGame::InitScene() Failed !");
		return E_FAIL;
	}

	return S_OK;
}

void CMainGame::Progress()
{
	// Time Update
	SetTime();

	// Key Update
	SetKeyState();

	// Scene Progress
	GET_SINGLE(CSceneMgr)->Progress();

	m_fPlayTime += GetTime();
	m_fFrameTime += GetTime();
}

void CMainGame::Render()
{
	Render_Begin();

	GET_SINGLE(CSceneMgr)->Render();
	
	Render_End(g_hWnd);

	// Frame Check
	++m_iFrameCount;
	if (m_fFrameTime >= 1.000f)
	{
		m_fFrameTime = 0.f;
		TCHAR wcTmp[128];
		swprintf(wcTmp, 128, L"Frame : %d", m_iFrameCount);
		SetWindowText(g_hWnd, wcTmp);
		m_iFrameCount = 0;
	}
}

void CMainGame::Release()
{
	DestroyDevice();
	DestroyTimer();
	DestroyKeyInput();

	DESTROY_SINGLETON(CSceneMgr);
}

