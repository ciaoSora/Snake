/*****************************************************************************
	File: utility.h
	Author: ciaoSora
	Desc: Utilities for DirectX operations
*****************************************************************************/

#pragma once
#ifndef UTILITY_H_
#define UTILITY_H_
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <Windows.h>
#include <fstream>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern LPDIRECT3DDEVICE9 pDevice;
extern std::ofstream fout;

namespace util {
	const D3DXVECTOR3 ZeroVector3(0.0f, 0.0f, 0.0f);
	const D3DXVECTOR2 ZeroVector2(0.0f, 0.0f);
	extern int deltaTime;

	LPDIRECT3DTEXTURE9 LoadTexture(std::string filename, D3DCOLOR transcolor = D3DCOLOR_XRGB(0, 0, 0));
	void UpdateDeltaTime();
	void DrawSprite(LPDIRECT3DTEXTURE9 pTexture, D3DXVECTOR2 position, float rotation, D3DXVECTOR2 scale, D3DCOLOR color);
	
	bool isKeyDown(int vk);
	bool hasKeyDowned(int vk);
}

#endif // !UTILITY_H_
