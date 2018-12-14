#include "Food.h"
#include "GameBoard.h"

Food::Food() : GameObject("white.png") {
	color = D3DCOLOR_XRGB(255, 255, 0);
	scale = D3DXVECTOR2(Snake::BODY_WIDTH, Snake::BODY_WIDTH);
	tag = "Food";

}

void Food::Start() {
	GameObject * pGameObject = util::FindWithTag("Snake");
	Snake * pSnake = dynamic_cast<Snake*>(pGameObject);
	pBody = pSnake->GetBodyPointer();
	NewFood();
}

void Food::NewFood() {
	static char book[GameBoard::Width][GameBoard::Height];

	::ZeroMemory(book, sizeof book);
	int len = pBody->Count();
	Coordinate c;
	for (int i = 0; i < len; ++i) {
		c = pBody->Get(i);
		book[c.x][c.y] = 1;
	}

	int n = GameBoard::Width * GameBoard::Height - len;
	int sel = util::randint(n);
	int cnt = 0;
	for (int i = 0; i < GameBoard::Width; ++i) {
		for (int j = 0; j < GameBoard::Height; ++j) {
			if (!book[i][j]) {
				if (cnt++ == sel) {
					position.x = i * Snake::CELL_WIDTH + (Snake::CELL_WIDTH - Snake::BODY_WIDTH) / 2;
					position.y = j * Snake::CELL_WIDTH + (Snake::CELL_WIDTH - Snake::BODY_WIDTH) / 2;
					return;
				}
			}
		}
	}

}

bool Food::isEating() {
	Coordinate c = pBody->GetRight();
	int coorX = (int)position.x / Snake::CELL_WIDTH;
	int coorY = (int)position.y / Snake::CELL_WIDTH;
	return c.x == coorX && c.y == coorY;
}

void Food::Update() {
	if (isEating()) {
		NewFood();
	}
}
