#include <Windows.h>
#include <conio.h>
#include "Game.h"
#include "Show.h"

Cell** CreateField(size_t size) {
	Cell** pArr = new Cell* [size];
	for (size_t i = 0; i < size; i++)
		pArr[i] = new Cell[size]{};
	return pArr;
}

void ChangeCell(Cell** field, size_t size, size_t x, size_t y, Cell cellValue) {
	if (x <= size && x > 0 && y <= size && y > 0)
		field[y - 1][x - 1] = cellValue;
}

void DeleteField(Cell** field, size_t size) {
	for (size_t i = 0; i < size; i++)
		delete[] field[i];
	delete[] field;
	field = nullptr;
}

void Moves(Cursor& cursor, size_t size) {
	if (_kbhit()) {
		switch (_getch()) {
			//w = 119; W = 87; Up arrow = 72
		case 119: case 87: case 72:
			if (cursor.y > 1) {
				cursor.lastY = cursor.y--;
				cursor.lastX = cursor.x;
			}
			break;
			//a = 97; A = 65; Left arrow = 75
		case 97: case 65: case 75:
			if (cursor.x > 1) {
				cursor.lastX = cursor.x--;
				cursor.lastY = cursor.y;
			}
			break;
			//s = 115; S = 83; Down arrow = 80
		case 115: case 83: case 80:
			if (cursor.y < size) {
				cursor.lastY = cursor.y++;
				cursor.lastX = cursor.x;
			}
			break;
			//d = 100; D = 68; Right arrow = 77
		case 100: case 68: case 77:
			if (cursor.x < size) {
				cursor.lastX = cursor.x++;
				cursor.lastY = cursor.y;
			}
			break;
		}
	}
	
}