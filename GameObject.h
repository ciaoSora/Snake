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

	LPDIRECT3DTEXTURE9 texture;
	D3DCOLOR color;
	std::string tag;

public:
	D3DXVECTOR2 position;
	float rotation;
	D3DXVECTOR2 scale;

	GameObject(const std::string pictureName);
	virtual ~GameObject() {

	}

	virtual void Draw();

	virtual void Update() {
		
	}

	virtual void Start() {

	}

	std::string GetTag() {
		return tag;
	}

	void SetTag(const std::string newtag) {
		tag = newtag;
	}
};

#endif // !GAMEOBJECT_H_

