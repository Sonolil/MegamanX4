#include "stdafx.h"
#include "Stage.h"
#include "SoundMgr.h"

CStage::CStage()
	:m_MettGen(0.0f), m_MettGen2(0.0f), m_Mett(0), m_GenStage(1)
{
}


CStage::~CStage()
{
	this->Release();
}

HRESULT CStage::ZeroTexture()
{
	HRESULT result = S_OK;
	result = InsertMulti(L"Zero", L"Init", L"zero_anime__000%d", 1);
	result = InsertMulti(L"Zero", L"Start", L"zero_anime__000%d", 13);
	result = InsertMulti(L"Zero", L"StartEnd", L"zero_anime__000%d", 2);
	result = InsertMulti(L"Zero", L"Idle", L"zero_anime__000%d", 1);
	result = InsertMulti(L"Zero", L"WalkBegin", L"zero_anime__000%d", 2);
	result = InsertMulti(L"Zero", L"Walk", L"zero_anime__000%d", 14);
	result = InsertMulti(L"Zero", L"JumpBegin", L"zero_anime__000%d", 2);
	result = InsertMulti(L"Zero", L"Jump", L"zero_anime__000%d", 2);
	result = InsertMulti(L"Zero", L"JumpAttack", L"zero_anime__000%d", 9);
	result = InsertMulti(L"Zero", L"FallBegin", L"zero_anime__000%d", 4);
	result = InsertMulti(L"Zero", L"Fall", L"zero_anime__000%d", 3);
	result = InsertMulti(L"Zero", L"FallEnd", L"zero_anime__000%d", 4);
	result = InsertMulti(L"Zero", L"Attack11", L"zero_anime__000%d", 6);
	result = InsertMulti(L"Zero", L"Attack12", L"zero_anime__000%d", 6);
	result = InsertMulti(L"Zero", L"Attack21", L"zero_anime__000%d", 5);
	result = InsertMulti(L"Zero", L"Attack22", L"zero_anime__000%d", 6);
	result = InsertMulti(L"Zero", L"Attack3", L"zero_anime__000%d", 14);
	result = InsertMulti(L"Zero", L"AttackFinish", L"zero_anime__000%d", 4);
	result = InsertMulti(L"Zero", L"DashBegin", L"zero_anime__000%d", 4);
	result = InsertMulti(L"Zero", L"Dash", L"zero_anime__000%d", 3);
	result = InsertMulti(L"Zero", L"DashEnd", L"zero_anime__000%d", 4);
	result = InsertMulti(L"Zero", L"Hurt", L"zero_anime__000%d", 6);
	result = InsertMulti(L"Zero", L"SlideBegin", L"zero_anime__000%d", 3);
	result = InsertMulti(L"Zero", L"Slide", L"zero_anime__000%d", 2);
	result = InsertMulti(L"Zero", L"SlideJump", L"zero_anime__000%d", 3);
	result = InsertMulti(L"Zero", L"EndBegin", L"zero_anime__000%d", 7);
	result = InsertMulti(L"Zero", L"End", L"zero_anime__000%d", 7);
	result = InsertMulti(L"Zero", L"SkillFire1", L"zero_anime__000%d", 2);
	result = InsertMulti(L"Zero", L"SkillFire2", L"zero_anime__000%d", 12);
	result = InsertMulti(L"Zero", L"SkillFire3", L"zero_anime__000%d", 2);
	result = InsertMulti(L"Zero", L"SkillIce1", L"zero_anime__000%d", 2);
	result = InsertMulti(L"Zero", L"SkillIce2", L"zero_anime__000%d", 2);
	result = InsertMulti(L"Zero", L"SkillIce3", L"zero_anime__000%d", 5);
	result = InsertMulti(L"Zero", L"SkillLightning1", L"zero_anime__000%d", 7);
	result = InsertMulti(L"Zero", L"SkillLightning2", L"zero_anime__000%d", 13);
	result = InsertMulti(L"Zero", L"SkillLightning3", L"zero_anime__000%d", 4);
	result = InsertMulti(L"Zero", L"SkillSlash1", L"zero_anime__000%d", 2);
	result = InsertMulti(L"Zero", L"SkillSlash2", L"zero_anime__000%d", 4);
	result = InsertMulti(L"Zero", L"SkillSlash3", L"zero_anime__000%d", 5);

	return result;
}

HRESULT CStage::MettTexture()
{
	HRESULT result = S_OK;
	result = InsertMulti(L"Mett", L"Fall", L"mett_anime__00%d", 4);
	result = InsertMulti(L"Mett", L"Idle", L"mett_anime__00%d", 1);
	result = InsertMulti(L"Mett", L"Walk", L"mett_anime__00%d", 10);
	result = InsertMulti(L"Mett", L"JumpBegin", L"mett_anime__00%d", 1);
	result = InsertMulti(L"Mett", L"Jump", L"mett_anime__00%d", 2);
	result = InsertMulti(L"Mett", L"Attack", L"mett_anime__00%d", 5);
	result = InsertMulti(L"Mett", L"Frozen", L"mett_anime__00%d", 1);
	result = InsertMulti(L"Mett", L"Hide", L"mett_anime__00%d", 3);
	result = InsertMulti(L"Mett", L"Hide", L"mett_anime__00%d", 2);

	return result;
}

HRESULT CStage::BatTexture()
{
	HRESULT result = S_OK;
	result = InsertMulti(L"Bat", L"Before", L"bat_anime___000%d", 4);
	result = InsertMulti(L"Bat", L"After", L"bat_anime___000%d", 5);
	result = InsertMulti(L"Bat", L"Drop", L"bat_anime___000%d", 3);

	return result;
}

HRESULT CStage::PeacockTexture()
{
	HRESULT result = S_OK;
	InsertMulti(L"Peacock", L"Init", L"peacock_anime_%d", 31);
	InsertMulti(L"Peacock", L"Start", L"peacock_anime_%d", 6);
	InsertMulti(L"Peacock", L"Idle1", L"peacock_anime_%d", 1);
	InsertMulti(L"Peacock", L"Idle2", L"peacock_anime_%d", 3);
	InsertMulti(L"Peacock", L"Hit1", L"peacock_anime_%d", 1);
	InsertMulti(L"Peacock", L"Hit2", L"peacock_anime_%d", 11);
	InsertMulti(L"Peacock", L"Attack11", L"peacock_anime_%d", 7);
	InsertMulti(L"Peacock", L"Attack12", L"peacock_anime_%d", 7);
	InsertMulti(L"Peacock", L"Attack13", L"peacock_anime_%d", 1);
	InsertMulti(L"Peacock", L"Attack21", L"peacock_anime_%d", 8);
	InsertMulti(L"Peacock", L"Attack22", L"peacock_anime_%d", 1);
	InsertMulti(L"Peacock", L"Attack31", L"peacock_anime_%d", 14);
	InsertMulti(L"Peacock", L"Attack32", L"peacock_anime_%d", 2);

	return result;
}

HRESULT CStage::FXTexture()
{
	HRESULT result = S_OK;
	result = InsertMulti(L"FX", L"Dash", L"dash_anime__00%d", 8);
	result = InsertMulti(L"FX", L"ExplodeS", L"explosion___000%d", 16);
	result = InsertMulti(L"FX", L"ExplodeL", L"explosion___000%d", 16);
	result = InsertMulti(L"FX", L"Hit", L"explosion___000%d", 4);
	result = InsertMulti(L"FX", L"Block", L"explosion___000%d", 5);

	return result;
}

HRESULT CStage::ObjTexture()
{
	HRESULT result = S_OK;

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Obj/health_bar.png",
		L"HPContainer",
		E_TEXTYPE_SINGLE
	);

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Obj/bar.png",
		L"HPBar",
		E_TEXTYPE_SINGLE
	);

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Bat/BatBomb.png",
		L"BatBomb",
		E_TEXTYPE_SINGLE
	);
	
	return result;
}

HRESULT CStage::ParallaxTexture()
{
	HRESULT result = S_OK;

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Background/background.png",
		L"BG",
		E_TEXTYPE_SINGLE
	);

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Background/parallax1.png",
		L"Parallax1",
		E_TEXTYPE_SINGLE
	);

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Background/parallax2.png",
		L"Parallax2",
		E_TEXTYPE_SINGLE
	);

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Background/ship1.png",
		L"Ship1",
		E_TEXTYPE_SINGLE
	);

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Background/ship2.png",
		L"Ship2",
		E_TEXTYPE_SINGLE
	);

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Background/ship3.png",
		L"Ship3",
		E_TEXTYPE_SINGLE
	);

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Background/platform_l.png",
		L"PlatformLeft",
		E_TEXTYPE_SINGLE
	);

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Background/platform_m.png",
		L"PlatformMiddle",
		E_TEXTYPE_SINGLE
	);

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Background/platform_r.png",
		L"PlatformRight",
		E_TEXTYPE_SINGLE
	);

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Background/wall.png", L"Wall",
		E_TEXTYPE_SINGLE
	);

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Background/wall2.png", L"Wall2",
		E_TEXTYPE_SINGLE
	);

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Background/bg.png", L"Pillar",
		E_TEXTYPE_SINGLE
	);

	result = GET_SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Rect/Hitbox.png", L"Hitbox",
		E_TEXTYPE_SINGLE
	);


	return result;
}


HRESULT CStage::InsertMulti(TCHAR* objKey, TCHAR* stateKey, TCHAR* address, int cnt)
{
	TCHAR concat[128] = L"";
	wsprintf(concat, L"../Resource/Texture/Stage/%s/%s/%s.png", 
		objKey, stateKey, address);

	if (FAILED(GET_SINGLE(CTextureMgr)->InsertTexture(
		concat,
		objKey,
		E_TEXTYPE_MULTI,
		stateKey, cnt)))
	{
		ERR_MSG(g_hWnd, L"CStage::InsertTexture() Failed !");
		return E_FAIL;
	}

	return S_OK;
}


HRESULT CStage::Initialize()
{
	HRESULT result = S_OK;
	m_pPrototype = new CStageObjProto;
	result = m_pPrototype->InitProtoInstance();

	GET_SINGLE(CSoundMgr)->Initialize();
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/bgm1.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/ready.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/begin.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/hoo.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/hah.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/ho.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/oom.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/sword.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/jump1.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/jump2.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/jumpG.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/jumpS.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/land.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/slide.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/slideHit.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/fire.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/ice1.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/ice2.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/lightning1.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/lightning2.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/wind.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/dash.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/dashend.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/groan.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/death.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/hit.wav");
	GET_SINGLE(CSoundMgr)->LoadWave(L"../Resource/Sound/explode.wav");

	GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_BGM1, true);
	result = GET_SINGLE(CObjMgr)->AddObject(m_pPrototype, L"Platform");
	GET_SINGLE(CCamMgr)->SetCam(1000, 0);
	ZeroTexture();
	MettTexture();
	BatTexture();
	FXTexture();
	ObjTexture();
	ParallaxTexture();

	return result;
}


void CStage::GenMonster()
{
	m_MettGen += GetTime();
	if (m_MettGen > 14.0f)
	{
		GET_SINGLE(CObjMgr)->AddObject(m_pPrototype, L"Mett1");
		GET_SINGLE(CObjMgr)->AddObject(m_pPrototype, L"Mett2");
		m_MettGen = 0;
	}

	m_MettGen2 += GetTime();
	if (m_MettGen2 > 28.0f)
	{
		GET_SINGLE(CObjMgr)->AddObject(m_pPrototype, L"Bat1");
		GET_SINGLE(CObjMgr)->AddObject(m_pPrototype, L"Bat2");
		m_MettGen2 = 0;
	}
}


E_SCENE CStage::Progress()
{
	m_fSceneTime += GetTime();

	if (m_fSceneTime > 0.5f)
	{
		if (!ready)
		{
			GET_SINGLE(CSoundMgr)->SoundPlay(E_SOUND_READY, false);
			ready = true;
		}
	}

	if (m_fSceneTime > 1.5f)
	{
		if (!init)
		{
			GET_SINGLE(CObjMgr)->AddObject(m_pPrototype, L"Player");
			init = true;
		}
	}

	GenMonster();

	E_SCENE SceneID = GET_SINGLE(CObjMgr)->Progress();

	if (SceneID >= 0)
		return SceneID;

	return E_SCENE_NONPASS;
}

void CStage::Render()
{
	GET_SINGLE(CObjMgr)->Render();
}

void CStage::Release()
{
	DESTROY_SINGLETON(CObjMgr);
	DESTROY_SINGLETON(CTextureMgr);
	DESTROY_SINGLETON(CSortMgr);

	SAFE_DELETE(m_pPrototype);
}

