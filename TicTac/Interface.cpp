#include <iostream>
#include <conio.h>
#include "Interface.h"
#include "Show.h"
using namespace std;

GameMode GetMode() {
	const size_t menuSize = 3;
	char header[] = "\tMenu\n\n";
	char menu[menuSize][50] = {
		"Player vs Player",
		"Player vs Computer",
		"Exit"
	};

	int key = 0;
	bool isSelected = false;
	do {
		system("cls");
		cout << header;
		for (int i = 0; i < menuSize; i++) {
			if (key == i)
				cout << ">> ";
			cout << menu[i] << "\n\n";
		}
		cout << "\nUse W and S to move and Enter to select\n";
		switch (_getch())
		{
			//w = 119; W = 87; Up arrow = 72
		case 119: case 87: case 72:
			if (key == 0)
				key = menuSize - 1;
			else
				key--;
			break;
			//s = 115; S = 83; Down arrow = 80
		case 115: case 83: case 80:
			key++;
			break;
		case 13:
			isSelected = true;
			break;
		default:
			break;
		}

		key %= menuSize;
	} while (!isSelected);

	return (GameMode)(key + 1);
}

Complexity GetComplexity() {
	const size_t menuSize = 4;
	char header[] = "\tChoose a difficulty\n\n";
	char menu[menuSize][50] = {
		"Easy",
		"Middle",
		"Hard",
		"Exit"
	};

	int key = 0;
	bool isSelected = false;
	do {
		system("cls");
		cout << header;
		for (int i = 0; i < menuSize; i++) {
			if (key == i)
				cout << ">> ";
			cout << menu[i] << "\n\n";
		}
		cout << "\nUse W and S to move and enter to select\n";
		switch (_getch())
		{
			//w = 119; W = 87; Up arrow = 72
		case 119: case 87: case 72:
			if (key == 0)
				key = menuSize - 1;
			else
				key--;
			break;
			//s = 115; S = 83; Down arrow = 80
		case 115: case 83: case 80:
			key++;
			break;
		case 13:
			isSelected = true;
			break;
		default:
			break;
		}

		key %= menuSize;
	} while (!isSelected);

	return (Complexity)(key + 1);
}

Cell GetSymb() {
	const size_t menuSize = 2;
	char header[] = "\tPlayer 1, enter symbol\n\n";
	char menu[menuSize][50] = {
		"X",
		"O"
	};

	int key = 0;
	bool isSelected = false;
	do {
		system("cls");
		cout << header;
		for (int i = 0; i < menuSize; i++) {
			if (key == i)
				cout << ">> ";
			cout << menu[i] << "\n\n";
		}
		cout << "\nUse W and S to move and enter to select\n";
		switch (_getch())
		{
			//w = 119; W = 87; Up arrow = 72
		case 119: case 87: case 72:
			if (key == 0)
				key = menuSize - 1;
			else
				key--;
			break;
			//s = 115; S = 83; Down arrow = 80
		case 115: case 83: case 80:
			key++;
			break;
		case 13:
			isSelected = true;
			break;
		default:
			break;
		}

		key %= menuSize;
	} while (!isSelected);

	return (Cell)(key + 1);
	
}

void SettingPvpMode(Player& player1, Player& player2) {	
	system("cls");
	cout << "Player 1, enter your name:  ";
	cin.sync();
	cin.getline(player1.name, 50);
	player1.player = GetSymb();
	system("cls");
	cout << "Player 2, enter your name: ";
	cin.sync();
	cin.getline(player2.name, 50);
	player2.player = (player1.player == Cell::PLAYER_1 ? Cell::PLAYER_2 : Cell::PLAYER_1);
}

void SettingPvCMode(Player& player1, Player& player2) {
	system("cls");
	cout << "Player, enter your name: ";
	cin.sync();
	cin.getline(player1.name, 50);
	player1.player = GetSymb();	
	player2.player = (player1.player == Cell::PLAYER_1 ? Cell::PLAYER_2 : Cell::PLAYER_1);
}

Game GetGameSettings() {
	Game game;
	game.gamemode = GetMode();
	switch (game.gamemode)
	{
	case GameMode::PVP:
		SettingPvpMode(game.player1, game.player2);
		game.complexity = Complexity::NOTHING;
		break;
	case GameMode::PVC:
		SettingPvCMode(game.player1, game.player2);
		game.complexity = GetComplexity();
		break;
	case GameMode::NOTHING:
		exit(0);
		break;
	}
	return game;
}

bool isExit() {
	
	const size_t menuSize = 2;
	char header[] = "\tEnter next step\n\n";
	char menu[menuSize][50] = {
		"Play again        ",
		"Exit        "
	};

	int key = 0;
	bool isSelected = false;
	do {
		ShowChar(7, 22, ' ');
		cout << header;
		for (int i = 0; i < menuSize; i++) {
			if (key == i)
				cout << ">> ";
			cout << menu[i] << "\n\n";
		}
		cout << "\nUse W and S to move and enter to select\n";
		switch (_getch())
		{
			//w = 119; W = 87; Up arrow = 72
		case 119: case 87: case 72:
			if (key == 0)
				key = menuSize - 1;
			else
				key--;
			break;
			//s = 115; S = 83; Down arrow = 80
		case 115: case 83: case 80:
			key++;
			break;
		case 13:
			isSelected = true;
			break;
		default:
			break;
		}

		key %= menuSize;
	} while (!isSelected);

	return !bool(key);
}