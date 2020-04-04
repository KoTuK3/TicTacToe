#pragma once
enum class Cell {
	VOID_CELL,
	PLAYER_1,
	PLAYER_2
};

struct Cursor {
	size_t x = 2;
	size_t y = 2;
	size_t lastX = 1;
	size_t lastY = 1;
};

Cell** CreateField(size_t size);
void ChangeCell(Cell** field, size_t size, size_t x, size_t y, Cell cellValue);
void DeleteField(Cell** field, size_t size);
void Moves(Cursor& cursor, size_t size);