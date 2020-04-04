#include <iostream>
using namespace std;

enum class GameMode {
	PVP,
	PVC
};

enum class Complexity {
	EASY,
	MIDDLE,
	HARD
};

int ShowModes() {
	int key;
	do {	
		cout << "\tMenu\n\n";
		cout << "1. Player vs Player\n";
		cout << "2. Player vs Computer\n";
		cout << "0. Exit\n";
		cin >> key;
	} while (0 > key || key > 2);
	return key;
}

int ShowComplexity() {
	int key;
	do {
		cout << "\tChoose a difficulty\n\n";
		cout << "1. Easy\n";
		cout << "2. Middle\n";
		cout << "3. Hard\n";
		cout << "0. Exit\n";
		cin >> key;
	} while (0 > key || key > 3);
	return key;
}