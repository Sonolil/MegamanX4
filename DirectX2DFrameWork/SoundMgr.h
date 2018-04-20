#pragma once
#include "Include.h"

class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr);
private:
	//directx sdk (����ũ�μ���Ʈ���� ��ǻ�Ϳ��ִ� �ϵ��� ���� ����Ҽ� �ְ�
	// �������� �Լ���, ���������� �����س��� ������ϰ� ���̺귯�������� ����.)
	//���̷�Ʈ ���� �������̽�
	LPDIRECTSOUND				m_pSound; //����ī�带 ��ǥ�ϴ� ��ü.
	vector<LPDIRECTSOUNDBUFFER> m_vecSoundBuff;	//���������� �ε��ؼ� ������ ����

public:
	HRESULT Initialize();	// ��ġ�� �ʱ�ȭ �ϴ¿�Ȱ.
	HRESULT LoadWave(TCHAR* pFileName);	//���ϰ�θ� ���� ������ �о� �帮�ڴ�.
	void SoundPlay(int iIndex /*���° ������ ����ҷ�?*/, DWORD dwFlag/*���ѷ���, �ѹ�*/); //������ ��� �ϰڴ�.
	void SoundStop(int iIndex);
	void SoundAllStop();
	bool SoundPlaying(int iIndex);	// ���� iIndex��° ���尡 ����ǰ��ִ��� �ƴ���.
	void SoundReset();
	void Release();
private:
	CSoundMgr();
public:
	~CSoundMgr();
};

