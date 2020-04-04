#include <iostream>
#include <windows.h>
#include "Game.h"
#include "Show.h"
using namespace std;

int main() {
	size_t size = 3;
	Cursor cursor;
	Cell** showField = CreateField(size);
	Cell** gameField = CreateField(size);

	//Test
	ChangeCell(gameField, size, 1, 1, Cell::PLAYER_1);
	ChangeCell(gameField, size, 2, 1, Cell::PLAYER_2);
	ChangeCell(gameField, size, 3, 1, Cell::PLAYER_1);	
	//

	ShowTable();
	do {		
		UpdateField(gameField, showField, size);
		Moves(cursor, size);
		ShowCursor(showField, cursor);
		Sleep(100);
	} while (true);

	DeleteField(gameField, size);
	DeleteField(showField, size);
	return 0;
}