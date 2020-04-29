#pragma once
#include "Structs.h";

Cell** CreateField(size_t size);
void ChangeCell(Cell** field, size_t size, size_t x, size_t y, Cell cellValue);
void DeleteField(Cell** field, size_t size);
void Moves(Cursor& cursor, Cell** gameField, size_t size, Step& step);
Winner CheckWin(Cell** gameField, size_t size);
void PlayPVP(Game gameSettings);
void PlayPVC(Game gameSettings);
bool IsGameOver(Cell** gameField, size_t size);
void NextStep(Step& step);
void EasyMod(Cell** gameField, Step& step);
void MiddleMod(Cell** gameField, Step& step);
void HardMod(Cell** gameField, size_t size, Game gameSetting, Step& step);

int Score(Cell** gameField, Game gameSetting);
int MaxSearch(Cell** gameField, size_t size, Game gameSetting);
int MinSearch(Cell** gameField, size_t size, Game gameSetting);