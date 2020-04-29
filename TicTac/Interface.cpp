#include <iostream>
#include "Interface.h"
using namespace std;

GameMode GetMode() {
	system("cls");
	int key;
	do {	
		cout << "\tMenu\n\n";
		cout << "1. Player vs Player\n";
		cout << "2. Player vs Computer\n";
		cout << "0. Exit\n";
		cin >> key;
	} while (0 < key && key > 2);
	
	return (GameMode)key;
}

Complexity GetComplexity() {
	system("cls");
	int key;
	do {
		cout << "\tChoose a difficulty\n\n";
		cout << "1. Easy\n";
		cout << "2. Middle\n";
		cout << "3. Hard\n";
		cout << "0. Exit\n";
		cin >> key;
	} while (0 < key && key > 3);
	return (Complexity)key;
}

Cell GetSymb() {
	system("cls");
	int key;
	do {
		cout << "Player 1, enter symbol\n";
		cout << "1. X\n";
		cout << "2. O\n";
		cin >> key;
	} while (0 < key && key > 2);
	if (key == 0)
		exit(0);
	return (Cell)key;
}

void SettingPvpMode(Player& player1, Player& player2) {
	system("cls");
	cout << "Player 1, enter your name:  ";
	cin.ignore();
	cin.getline(player1.name, 50);
	player1.player = GetSymb();
	cout << "Player 2, enter your name: ";
	cin.ignore();
	cin.getline(player2.name, 50);
	player2.player = (player1.player == Cell::PLAYER_1 ? Cell::PLAYER_2 : Cell::PLAYER_1);
}

void SettingPvCMode(Player& player1, Player& player2) {
	system("cls");
	cout << "Player, enter your name: ";
	cin.ignore();
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