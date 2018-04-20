#include "stdafx.h"
#include "StageObjProto.h"

#include "Tile.h"
#include "Player.h"
#include "Monster.h"
#include "Platform.h"
#include "Bat.h"

CStageObjProto::CStageObjProto()
{
}


CStageObjProto::~CStageObjProto()
{
}

HRESULT CStageObjProto::InitProtoInstance()
{
	INFO ObjInfo;
	ZeroMemory(&ObjInfo, sizeof(INFO));

	D3DXMatrixIdentity(&ObjInfo.matWorld);

	ObjInfo.vPos = D3DXVECTOR3(400.f, 300.f, 0.f);
	ObjInfo.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	ObjInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);

	// 원형객체를 map에 담는다.
	m_MapProto.insert(make_pair(L"Platform", new CPlatform(ObjInfo)));
	m_MapProto.insert(make_pair(L"Player", new CPlayer(ObjInfo)));

	ObjInfo.vPos = D3DXVECTOR3(200.f, -50.f, 0.f);
	ObjInfo.vDir = D3DXVECTOR3(-1.f, 0.f, 0.f);
	m_MapProto.insert(make_pair(L"Mett1", new CMonster(ObjInfo)));
	ObjInfo.vPos = D3DXVECTOR3(-100.f, 400.f, 0.f);
	m_MapProto.insert(make_pair(L"Bat1", new CBat(ObjInfo)));

	ObjInfo.vPos = D3DXVECTOR3(1800.f, -50.f, 0.f);
	ObjInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_MapProto.insert(make_pair(L"Mett2", new CMonster(ObjInfo)));
	ObjInfo.vPos = D3DXVECTOR3(2100.f, 400.f, 0.f);
	m_MapProto.insert(make_pair(L"Bat2", new CBat(ObjInfo)));

	return S_OK;
}

