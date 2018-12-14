#pragma once
#ifndef FODD_H_
#define FOOD_H_
#include "GameObject.h"
#include "Queue.h"
#include "Snake.h"

class Food : public GameObject {

	const Queue<Coordinate> * pBody;
	void NewFood();
	bool isEating();

public:
	Food();
	void Update();
	void Start();
};

#endif // !FODD_H_

