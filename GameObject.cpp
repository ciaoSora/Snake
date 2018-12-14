#include "GameObject.h"

GameObject::GameObject(const std::string pictureName) {
	position = util::ZeroVector2;
	rotation = 0;
	scale = D3DXVECTOR2(1.0f, 1.0f);
	texture = util::LoadTexture(pictureName);
	color = D3DCOLOR_XRGB(255, 255, 255);
	tag = "GameObject";
}

void GameObject::Draw() {
	util::DrawSprite(texture, position, rotation, scale, color);
}
