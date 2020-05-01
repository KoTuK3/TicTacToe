#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include "Interface.h"
#include "Show.h"
using namespace std;

int main() {
	srand(time(nullptr));
	Game gameSettings;
	ShowLogo();
	_getch();

	do {
		gameSettings = GetGameSettings();
		switch (gameSettings.gamemode)
		{
		case GameMode::PVC:
			PlayPVC(gameSettings);
			break;
		case GameMode::PVP:
			PlayPVP(gameSettings);
			break;
		}
	} while (isExit());

	return 0;
}