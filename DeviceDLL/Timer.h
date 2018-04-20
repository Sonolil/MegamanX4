#pragma once

#define DEVICE_EXPORT
#include "DeviceDef.h"

EXTERN class DEVICE_DLL CTimer
{
	DECLARE_SINGLETON(CTimer);
private:
	LARGE_INTEGER m_FrameTime;
	LARGE_INTEGER m_FixTime;
	LARGE_INTEGER m_LastTime;
	LARGE_INTEGER m_CpuTick;
	float m_fTime;
public:
	void InitTimer();
	void SetTime();
public:
	float GetTime() const { return m_fTime; }
private:
	CTimer();
public:
	~CTimer();
};