#include "GameObject.h"

GameObject::GameObject(const std::string pictureName) {
	position = util::ZeroVector2;
	rotation = 0;
	scale = D3DXVECTOR2(1.0f, 1.0f);
	texture = util::LoadTexture(pictureName);
	color = D3DCOLOR_XRGB(255, 255, 255);
	position = D3DXVECTOR2(80.0f, 80.0f);
	scale = D3DXVECTOR2(100.0f, 18.0f);
}

void GameObject::Draw() {
	util::DrawSprite(texture, position, rotation, scale, color);
}
