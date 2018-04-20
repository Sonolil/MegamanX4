#ifndef _DEVICE_DEF_H
#define _DEVICE_DEF_H

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#include "Macro.h"
#include "Constants.h"
#include "Struct.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

#ifdef DEVICE_EXPORT
#define DEVICE_DLL _declspec (dllexport)
#else
#define DEVICE_DLL _declspec (dllimport)
#endif



#endif