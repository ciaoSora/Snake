/*****************************************************************************
	File: utility.cpp
	Author: ciaoSora
	Desc: Utilities for DirectX operations
*****************************************************************************/

#include "utility.h"
#include "GameObject.h"
#pragma comment(lib, "winmm.lib")

LPDIRECT3DTEXTURE9 util::LoadTexture(std::string filename, D3DCOLOR transcolor) {
	LPDIRECT3DTEXTURE9 texture = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filename.c_str(), &info);
	if (result != D3D_OK) {
		return NULL;
	}
	D3DXCreateTextureFromFileEx(pDevice,
								filename.c_str(),
								info.Width,
								info.Height,
								1,
								D3DPOOL_DEFAULT,
								D3DFMT_UNKNOWN,
								D3DPOOL_DEFAULT,
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								transcolor,
								&info,
								NULL,
								&texture);
	if (result != D3D_OK) {
		return NULL;
	}
	return texture;
}
extern LPD3DXSPRITE pSprite;
extern std::ofstream fout("log.txt");
extern GameObject* gameobjects[10];
extern bool gameover;

int util::deltaTime;

void util::UpdateDeltaTime() {
	static DWORD last_time = timeGetTime();

	util::deltaTime = timeGetTime() - last_time;
	last_time = timeGetTime();
}

void util::DrawSprite(LPDIRECT3DTEXTURE9 pTexture, D3DXVECTOR2 position, float rotation, D3DXVECTOR2 scale, D3DCOLOR color) {
	if (pTexture == NULL) {
		return;
	}
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0, &scale, NULL, 0, &position);
	pSprite->SetTransform(&mat);
	pSprite->Draw(pTexture, NULL, NULL, NULL, color);
}

bool util::isKeyDown(int vk) {
	return ::GetAsyncKeyState(vk) & 0x8000;
}

bool util::hasKeyDowned(int vk) {
	return ::GetAsyncKeyState(vk) & 1;
}

int util::randint(int n) {
	return rand() % n;
}

int util::randint(int mn, int mx) {
	return rand() % (mx - mn) + mn;
}

GameObject * util::FindWithTag(const std::string tag) {
	for (int i = 0; i < sizeof gameobjects / sizeof(GameObject*); ++i) {
		if (gameobjects[i]) {
			if (gameobjects[i]->GetTag() == tag) {
				return gameobjects[i];
			}
		}
	}
	return NULL;
}

void util::GameOver(const std::string prompt) {
	gameover = true;
	::MessageBox(0, prompt.c_str(), "Game Over", 0);
}
