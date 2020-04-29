#pragma once
void ShowTable();
void ShowCursor(Cell** showField, Cursor cursor);
void UpdateField(Cell** gameField, Cell** showField, size_t size);
void ShowCurrentSymb(Step step);
void ShowWinner(Winner winner, Game game);

