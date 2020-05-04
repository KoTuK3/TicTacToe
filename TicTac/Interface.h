#pragma once
#include "Game.h";
#include "structs.h";

Game GetGameSettings();
bool IsExit();
int Selector(char header[], char menu[][50], size_t menuSize, bool hasExit, bool hasRefresh);