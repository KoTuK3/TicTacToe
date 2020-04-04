#include <iostream>
#include <windows.h>
#include "Game.h"

using namespace std;

void hideCursor() {
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo);
}

void ShowChar(size_t x, size_t y, char character) {
	COORD cord;
	//1 unit = 0.5 width and 1 height
	cord.X = x * 2;
	cord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	cout << character;
}

void ShowTable() {
	hideCursor();
	system("cls");
	size_t height = 19;
	size_t width = height * 2 - 1;

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			// Upper left corner
			if (i == 0 && j == 0)
				cout << (char)201;
			// Upper right corner
			else if (i == 0 && j == width - 1)
				cout << (char)187;
			// Lower left corner
			else if (i == height - 1 && j == 0)
				cout << (char)200;
			// Lower right corner
			else if (i == height - 1 && j == width - 1)
				cout << (char)188;
			// Upper intersections
			else if (i == 0 && j % 12 == 0)
				cout << (char)203;
			// Lower intersections
			else if (i == height - 1 && j % 12 == 0)
				cout << (char)202;
			// Left intersections
			else if (i % 6 == 0 && j == 0)
				cout << (char)204;
			// Right intersections
			else if (i % 6 == 0 && j == width - 1)
				cout << (char)185;
			else if (i % 6 == 0 && j % 12 != 0)
				cout << (char)205;
			else if (i % 6 != 0 && j % 12 == 0)
				cout << (char)186;
			else if (i % 6 == 0 && j % 12 == 0)
				cout << (char)206;
			else 
				cout << " ";
		}
		cout << endl;
	}
}

void ShowX(size_t cellX, size_t cellY) {
	//X       X
	//  X   X
	//    X
	//  X   X
	//X       X
	size_t x = (cellX * 6) - 3;
	size_t y = (cellY * 6) - 3;
	ShowChar(x, y, (char)254);
	ShowChar(x - 1, y - 1, (char)254);
	ShowChar(x - 2, y - 2, (char)254);
	ShowChar(x + 1, y + 1, (char)254);
	ShowChar(x + 2, y + 2, (char)254);
	ShowChar(x - 1, y + 1, (char)254);
	ShowChar(x - 2, y + 2, (char)254);
	ShowChar(x + 1, y - 1, (char)254);
	ShowChar(x + 2, y - 2, (char)254);
}

void ShowO(size_t cellX, size_t cellY) {
	//  O O O 
	//O       O
	//O       O
	//O       O
	//  O O O 
	size_t x = (cellX * 6) - 3;
	size_t y = (cellY * 6) - 3;
	ShowChar(x - 1, y - 2, (char)254);
	ShowChar(x,		y - 2, (char)254);
	ShowChar(x + 1, y - 2, (char)254);

	ShowChar(x - 2, y - 1, (char)254);
	ShowChar(x - 2, y,	   (char)254);
	ShowChar(x - 2, y + 1, (char)254);

	ShowChar(x + 2, y - 1, (char)254);
	ShowChar(x + 2, y,     (char)254);
	ShowChar(x + 2, y + 1, (char)254);

	ShowChar(x - 1, y + 2, (char)254);
	ShowChar(x,		y + 2, (char)254);
	ShowChar(x + 1, y + 2, (char)254);
}

void UpdateField(Cell** gameField, Cell** showField, size_t size) {
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			if (gameField[i][j] != showField[i][j]) {
				showField[i][j] = gameField[i][j];
				if (showField[i][j] == Cell::PLAYER_1)
					ShowX(j + 1, i + 1);
				else if (showField[i][j] == Cell::PLAYER_2)
					ShowO(j + 1, i + 1);
			}
		}
	}
}

void ShowCursor(Cell** showField, Cursor cursor) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 0xB);
	if (showField[cursor.y - 1][cursor.x - 1] == Cell::PLAYER_1)
		ShowX(cursor.x, cursor.y);
	else if (showField[cursor.y - 1][cursor.x - 1] == Cell::PLAYER_2)
		ShowO(cursor.x, cursor.y);
	else {
		COORD cord;
		//1 unit = 0.5 width and 1 height
		cord.X = cursor.x * 12 - 6;
		cord.Y = cursor.y * 6 - 3;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		cout << (char)176 << (char)176;
	}

	
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 0xF);
	if (showField[cursor.lastY - 1][cursor.lastX - 1] == Cell::PLAYER_1)
		ShowX(cursor.lastX, cursor.lastY);
	else if (showField[cursor.lastY - 1][cursor.lastX - 1] == Cell::PLAYER_2)
		ShowO(cursor.lastX, cursor.lastY);
	else {
		COORD cord;
		//1 unit = 0.5 width and 1 height
		cord.X = cursor.lastX * 12 - 6;
		cord.Y = cursor.lastY * 6 - 3;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		cout << "  ";
	}
}
//Test
void ShowArr(Cell** arr, size_t size) {
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++)
			cout << (int)arr[i][j] << " ";
		cout << endl;
	}
}