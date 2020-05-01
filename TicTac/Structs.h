#pragma once

enum class Cell {
	VOID_CELL,
	PLAYER_1,
	PLAYER_2
};

enum class GameMode {
	NOTHING,
	PVP,
	PVC
};

enum class Complexity {
	NOTHING,
	EASY,
	MIDDLE,
	HARD
};

struct Player {
	char name[50] = "Computer";
	Cell player;
};

struct Cursor {
	size_t x = 2;
	size_t y = 2;
	size_t lastX = 1;
	size_t lastY = 1;
};

enum class Winner {
	NOTHING,
	PLAYER_1,
	PLAYER_2,
	DRAW
};

struct Game {
	GameMode gamemode = GameMode::NOTHING;
	Complexity complexity = Complexity::NOTHING;
	Player player1;
	Player player2;
	bool isExit = false;
};

struct Step {
	unsigned currentStep = 0;
	Cell currentSymb = Cell::VOID_CELL;
};

struct Move {
	int x;
	int y;
};