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
// Наступний крок міняє символ(з х на о або навпаки) і добавляє до лічильника кроків +1
void NextStep(Step& step);
void EasyMod(Cell** gameField, size_t size, Step& step);
void MiddleMod(Cell** gameField, size_t size, Step& step);

// HardMod використовує алгоритм minimax
// Наступні функції потрібні для реалізації цього алгоритму
void HardMod(Cell** gameField, size_t size, Game gameSetting, Step& step);

// Функція Score потрібна для підрахунку результату
// щоб комп'ютер міг вибрати оптимальний варіант де він виграє або де нічія
int Score(Cell** gameField, Game gameSetting);
// Пошук найкращого варіанта для комп'ютера
int MaxSearch(Cell** gameField, size_t size, Game gameSetting);
// Пошук найгіршого варіанта для комп'ютера
int MinSearch(Cell** gameField, size_t size, Game gameSetting);