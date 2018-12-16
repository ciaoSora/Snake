#include "Snake.h"
#include <string>
#include "GameBoard.h"
#include "Food.h"

const int Snake::dirx[4] = { 1, 0, -1, 0 };
const int Snake::diry[4] = { 0, 1, 0, -1 };
const float Snake::CELL_WIDTH = 20.0f;
const float Snake::BODY_WIDTH = 18.0f;
const int Snake::SLEEP_TIME = 100;

Snake::Snake() : GameObject("white.png") {
	body.Resize(GameBoard::Width * GameBoard::Height);
	direction = 0;
	int initY = GameBoard::Height / 2;
	for (int i = 0; i < 5; ++i) {
		body.Push(Coordinate(i, initY));
	}
	tag = "Snake";
	color = D3DCOLOR_XRGB(255, 0, 0);
}


Snake::~Snake() {
	
}

void Snake::Start() {
	GameObject * pGameObject = util::FindWithTag("Food");
	food = dynamic_cast<Food*>(pGameObject);
}

D3DXVECTOR2 Snake::c2v(Coordinate c) {
	return D3DXVECTOR2(c.x * CELL_WIDTH, c.y * CELL_WIDTH);
}

void Snake::DrawAuxiliary(D3DXVECTOR2 pos, int dir) {
	static const float da_p_dirx[4] = {BODY_WIDTH, 0.0f, BODY_WIDTH - CELL_WIDTH, 0.0f};
	static const float da_p_diry[4] = {0.0f, BODY_WIDTH, 0.0f, BODY_WIDTH - CELL_WIDTH};
	static const float lng = BODY_WIDTH, sht = CELL_WIDTH - BODY_WIDTH;
	static const float da_s_dirx[4] = {sht, lng, sht, lng};
	static const float da_s_diry[4] = {lng, sht, lng, sht};
	pos =  D3DXVECTOR2(pos.x + da_p_dirx[dir], pos.y + da_p_diry[dir]);
	D3DXVECTOR2 sca(da_s_dirx[dir], da_s_diry[dir]);
	util::DrawSprite(texture, pos, 0, sca, color);
}

int Snake::RelativeDirection(Coordinate c1, Coordinate c2) {
	if (c1.x == c2.x) {
		return c1.y < c2.y? 1: 3;
	}
	return c1.x < c2.x? 0: 2;
}

void Snake::Draw() {
	int len = body.Count();
	Coordinate c1, c2;
	int d1, d2;
	D3DXVECTOR2 pos;
	static const D3DXVECTOR2 sca(BODY_WIDTH, BODY_WIDTH);
	static const D3DXVECTOR2 deltaPos((CELL_WIDTH - BODY_WIDTH) / 2, (CELL_WIDTH - BODY_WIDTH) / 2);

	for (int i = 0; i < len; ++i) {
		c1 = body.Get(i);
		pos = c2v(c1) + deltaPos;
		util::DrawSprite(texture, pos, 0, sca, color);
	}

	c1 = body.GetLeft();
	c2 = body.Get(1);
	d2 = RelativeDirection(c1, c2);
	d1 = d2 ^ 2;
	pos = c2v(c1) + deltaPos;
	DrawAuxiliary(pos, d1);
	DrawAuxiliary(pos, d2);
	for (int i = 1; i < len - 1; ++i) {
		c1 = body.Get(i);
		pos = c2v(c1) + deltaPos;

		c2 = body.Get(i - 1);
		d1 = RelativeDirection(c1, c2);
		DrawAuxiliary(pos, d1);
		c2 = body.Get(i + 1);
		d2 = RelativeDirection(c1, c2);
		DrawAuxiliary(pos, d2);
	}
	c1 = body.GetRight();
	c2 = body.Get(len - 2);
	d1 = RelativeDirection(c1, c2);
	d2 = d1 ^ 2;
	pos = c2v(c1) + deltaPos;
	DrawAuxiliary(pos, d1);
	DrawAuxiliary(pos, d2);
}

void Snake::UpdateColor() {
	static const float speed = 0.1;
	static float r = 255.0f, g = 0.0f, b = 0.0f;

	float delta = util::deltaTime * speed;
	if (r == 255.0f && g < 255.0f) {
		if (b > 0.0f) {
			b = max(0.0f, b - delta);
		}
		else {
			g = min(255.0f, g + delta);
		}
	}
	else if (g == 255.0f && b < 255.0f) {
		if (r > 0.0f) {
			r = max(0.0f, r - delta);
		}
		else {
			b = min(255.0f, b + delta);
		}
	}
	else {
		if (g > 0.0f) {
			g = max(0.0f, g - delta);
		}
		else {
			r = min(255.0f, r + delta);
		}
	}

	color = D3DCOLOR_XRGB((int)r, (int)g, (int)b);
	
}

void Snake::Update() {
	UpdateColor();

	static int acc = 0;
	static int ready_dir = 0;

	int new_dir = -1;
	if (util::hasKeyDowned(VK_RIGHT) || util::hasKeyDowned('D')) {
		new_dir = 0;
	}
	else if (util::hasKeyDowned(VK_DOWN) || util::hasKeyDowned('S')) {
		new_dir = 1;
	}
	else if (util::hasKeyDowned(VK_LEFT) || util::hasKeyDowned('A')) {
		new_dir = 2;
	}
	else if (util::hasKeyDowned(VK_UP) || util::hasKeyDowned('W')) {
		new_dir = 3;
	}

	if (new_dir != -1) {
		if ((new_dir ^ direction) & 1) {
			ready_dir = new_dir;
		}
	}

	acc += util::deltaTime;
	if (acc < SLEEP_TIME) {
		return;
	}
	direction = ready_dir;
	acc = 0;
	Move();
}

void Snake::Move() {
	Coordinate c1 = body.GetRight();
	c1.x += dirx[direction];
	c1.y += diry[direction];
	int foodX = (int)food->position.x / (int)CELL_WIDTH;
	int foodY = (int)food->position.y / (int)CELL_WIDTH;
	if (c1.x != foodX || c1.y != foodY) {
		body.Pop();
	}

	if (c1.x < 0 || c1.x >= GameBoard::Width || c1.y < 0 || c1.y >= GameBoard::Height) {
		util::GameOver("Watch your way!");
	}

	int len = body.Count();
	Coordinate c2;
	for (int i = 0; i < len - 1; ++i) {
		c2 = body.Get(i);
		if (c1.x == c2.x && c1.y == c2.y) {
			util::GameOver("You eat yourself!");
			break;
		}
	}

	body.Push(c1);

	
}
