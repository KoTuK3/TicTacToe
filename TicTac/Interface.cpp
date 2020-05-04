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

	return (GameMode)(Selector(header, menu, menuSize, true, true) + 1);
}



Difficulty GetDifficulty() {
	const size_t menuSize = 4;
	char header[] = "\tChoose a difficult\n\n";
	char menu[menuSize][50] = {
		"Easy",
		"Middle",
		"Hard",
		"Exit"
	};
	
	return (Difficulty)(Selector(header, menu, menuSize, true, true) + 1);
}

Cell GetSymb() {
	const size_t menuSize = 2;
	char header[] = "\tPlayer 1, enter symbol\n\n";
	char menu[menuSize][50] = {
		"X",
		"O"
	};
	
	return (Cell)(Selector(header, menu, menuSize, false, true) + 1);
	
}

void SettingPvpMode(Player& player1, Player& player2) {
	do {
		system("cls");
		cout << "Player 1, enter your name(min. 1 symbol):  ";
		cin.sync();
		cin.getline(player1.name, 50);
	} while (strlen(player1.name) == 0);
	
	player1.player = GetSymb();

	do {
		system("cls");
		cout << "Player 2, enter your name(min. 1 symbol): ";
		cin.sync();
		cin.getline(player2.name, 50);
	} while (strlen(player2.name) == 0);

	player2.player = (player1.player == Cell::PLAYER_1 ? Cell::PLAYER_2 : Cell::PLAYER_1);
}

void SettingPvCMode(Player& player1, Player& player2) {
	do {
		system("cls");
		cout << "Player, enter your name(min. 1 symbol): ";
		cin.sync();
		cin.getline(player1.name, 50);
	} while (strlen(player1.name) == 0);
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
		game.difficulty = Difficulty::NOTHING;
		break;
	case GameMode::PVC:
		SettingPvCMode(game.player1, game.player2);
		game.difficulty = GetDifficulty();
		break;
	case GameMode::NOTHING:
		exit(0);
		break;
	}
	return game;
}

bool IsExit() {
	
	const size_t menuSize = 2;
	char header[] = "\tEnter next step\n\n";
	char menu[menuSize][50] = {
		"Play again        ",
		"Exit        "
	};

	return !bool(Selector(header, menu, menuSize, true, false));
}

int Selector(char header[], char menu[][50], size_t menuSize, bool hasExit, bool hasRefresh) {
	int key = 0;
	bool isSelected = false;
	do {
		if (hasRefresh)
			system("cls");
		else
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
			if (key == menuSize - 1 && hasExit)
				exit(0);
			isSelected = true;
			break;
		}
		// «меншуЇ key до допустимого д≥апазону (0 -- (menuSize - 1))
		key %= menuSize;
	} while (!isSelected);
	return key;
}