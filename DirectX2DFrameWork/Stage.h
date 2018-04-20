#pragma once
#include "SceneObj.h"
#include "StageObjProto.h"

class CStage : public CSceneObj
{
private:
	int m_GenStage;
	int m_Mett;
	float m_MettGen, m_MettGen2;
	bool ready, init;
private:
	HRESULT ZeroTexture();
	HRESULT MettTexture();
	HRESULT BatTexture();
	HRESULT PeacockTexture();
	HRESULT FXTexture();
	HRESULT ObjTexture();
	HRESULT ParallaxTexture();
	HRESULT InsertMulti(TCHAR* objKey, TCHAR* stateKey, TCHAR* address, int cnt);
private:
	void GenMonster();
public:
	virtual HRESULT Initialize();
	virtual E_SCENE Progress();
	virtual void Render();
	virtual void Release();
public:
	CStage();
	virtual ~CStage();
};

