#include <iostream>
#include <ctime>
#include "Interface.h"

using namespace std;

int main() {
	srand(time(nullptr));
		
	Game gameSettings = GetGameSettings();

	switch (gameSettings.gamemode)
	{
	case GameMode::PVC:
		PlayPVC(gameSettings);
		break;
	case GameMode::PVP:
		PlayPVP(gameSettings);
		break;
	}

	return 0;
}