#pragma once
#ifndef SNAKE_H_
#define SNAKE_H_

#include "GameObject.h"
#include "Queue.h"

struct Coordinate {
	int x, y;
	Coordinate(int x_ = 0, int y_ = 0) {
		x = x_;
		y = y_;
	}
};

class Snake : public GameObject {

	Queue<Coordinate> body;
	int direction;
	D3DXVECTOR2 c2v(Coordinate c);
	void DrawAuxiliary(D3DXVECTOR2 pos, int dir);
	int RelativeDirection(Coordinate c1, Coordinate c2);
	void Move();

	static const int dirx[4];
	static const int diry[4];
	static const float CELL_WIDTH;
	static const float BODY_WIDTH;
	static const int SLEEP_TIME;

public:
	Snake();
	virtual ~Snake();
	void Draw();
	void Update();

};

#endif // !SNAKE_H_
