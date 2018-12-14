/*****************************************************************************
	File: GameObject.h
	Author: ciaoSora
	Desc: Class GameObject
*****************************************************************************/

#pragma once
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include <d3d9.h>
#include <d3dx9.h>
#include "utility.h"

class GameObject {

protected:

	D3DXVECTOR2 position;
	float rotation;
	D3DXVECTOR2 scale;
	LPDIRECT3DTEXTURE9 texture;
	D3DCOLOR color;

public:

	GameObject(const std::string pictureName);
	virtual ~GameObject() {

	}

	virtual void Draw();

	virtual void Update() {
		
	}
};

#endif // !GAMEOBJECT_H_

