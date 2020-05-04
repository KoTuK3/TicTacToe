#include <iostream>
#include <windows.h>
#include "Structs.h"

using namespace std;

void HideCursor() {
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
	//Виводить табличку використовуючи символи з таблиці ASCII
	HideCursor();
	system("cls");
	size_t height = 19;
	size_t width = height * 2 - 1;
	// У if-ах і, j порівнюється з розмірами і ділиться націло на розміри
	// Розмір вимірюється в символах(мінімальна одиниця в консолі).
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
	ShowChar(21, 2, ' ');
	cout << "Use WASD to move and Enter to place a mark";
}

void ShowX(size_t cellX, size_t cellY) {
	// Виводить Х використовуючи символ з таблиці ASCII під номером 254
	//X       X
	//  X   X
	//    X
	//  X   X
	//X       X
	size_t x = (cellX * 6) - 3;
	size_t y = (cellY * 6) - 3;
	ShowChar(x, y, (char)254);
	cout << ' ';
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
	// Виводить O використовуючи символ з таблиці ASCII під номером 254
	//  O O O 
	//O       O
	//O       O
	//O       O
	//  O O O 
	size_t x = (cellX * 6) - 3;
	size_t y = (cellY * 6) - 3;
	ShowChar(x, y, ' ');
	cout << ' ';
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
		cord.X = cursor.lastX * 12 - 6;
		cord.Y = cursor.lastY * 6 - 3;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		cout << "  ";
	}
}

void ShowCurrentSymb(Step step) {
	ShowChar(7, 20, ' ');
	cout << "                   ";
	ShowChar(7, 20, ' ');
	if (step.currentSymb == Cell::PLAYER_1)
		cout << "Now: X\n";
	else if (step.currentSymb == Cell::PLAYER_2)
		cout << "Now: O\n";
}

void ShowWinner(Winner winner, Game game) {
	ShowChar(5, 20, ' ');
	if (winner == Winner::PLAYER_1) {
		if ((int)winner == (int)game.player1.player)
			cout << game.player1.name << " win!!!";
		else 
			cout << game.player2.name << " win!!!";
	}
	else if (winner == Winner::PLAYER_2) {
		if ((int)winner == (int)game.player1.player)
			cout << game.player1.name << " win!!!";
		else
			cout << game.player2.name << " win!!!";
	}
	else if (winner == Winner::DRAW)
		cout << "     DRAW!!!";
	cout << "        \n";
}

void ShowLogo() {
	system("cls");
	const size_t HEIGHT = 7;
	const size_t WIDTH = 16;
	char symb = 219;
	char logo[HEIGHT][WIDTH];
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 0xC);

	strcpy_s(logo[0], "#     #   ###  ");
	strcpy_s(logo[1], "##   ##  #   # ");
	strcpy_s(logo[2], " ## ##  #     #");
	strcpy_s(logo[3], "  ###   #     #");
	strcpy_s(logo[4], " ## ##  #     #");
	strcpy_s(logo[5], "##   ##  #   # ");
	strcpy_s(logo[6], "#     #   ###  ");

	cout << "\n\n\n";
	for (size_t i = 0; i < HEIGHT; i++) {
		cout << '\t';
		for (size_t j = 0; j < WIDTH; j++) {
			if (logo[i][j] == '#')
				cout << symb << symb;
			else
				cout << "  ";
		}
		cout << endl;
	}
	SetConsoleTextAttribute(handle, 0xF);

	cout << "\n\n\t   Press any key to start\n";
}