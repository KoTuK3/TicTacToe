#pragma once
void ShowTable();
void ShowCursor(Cell** showField, Cursor cursor);
void UpdateField(Cell** gameField, Cell** showField, size_t size);

//Test
void ShowX(size_t cellX, size_t cellY);
void ShowArr(Cell** arr, size_t size);