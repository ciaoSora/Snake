#pragma once
#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_
#include "GameObject.h"

class GameBoard : public GameObject {

public:
	static const int Width;
	static const int Height;

};

const int GameBoard::Width = 40;
const int GameBoard::Height = 30;

#endif // !GAMEBOARD_H_

