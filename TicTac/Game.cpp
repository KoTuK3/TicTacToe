#include <Windows.h>
#include <conio.h>
#include "Game.h"
#include "Show.h"

Cell** CreateField(size_t size) {
	Cell** pArr = new Cell* [size];
	for (size_t i = 0; i < size; i++)
		pArr[i] = new Cell[size]{};
	return pArr;
}

void ChangeCell(Cell** field, size_t size, size_t x, size_t y, Cell cellValue) {
	// Перевірка чи курсор знаходиться в межах поля
	// а також перевіряється чи вибрана клітинка пуста
	if (x <= size && x > 0 &&
		y <= size && y > 0 && 
		field[y - 1][x - 1] == Cell::VOID_CELL)
		field[y - 1][x - 1] = cellValue;
}

void DeleteField(Cell** field, size_t size) {
	for (size_t i = 0; i < size; i++)
		delete[] field[i];
	delete[] field;
}

void Moves(Cursor& cursor, Cell** gameField, size_t size, Step& step) {
	if (_kbhit()) {
		switch (_getch()) {
		//w = 119; W = 87; Up arrow = 72
		case 119: case 87: case 72:
			if (cursor.y > 1) {
				cursor.lastY = cursor.y--;
				cursor.lastX = cursor.x;
			}
			break;
		//a = 97; A = 65; Left arrow = 75
		case 97: case 65: case 75:
			if (cursor.x > 1) {
				cursor.lastX = cursor.x--;
				cursor.lastY = cursor.y;
			}
			break;
		//s = 115; S = 83; Down arrow = 80
		case 115: case 83: case 80:
			if (cursor.y < size) {
				cursor.lastY = cursor.y++;
				cursor.lastX = cursor.x;
			}
			break;
		//d = 100; D = 68; Right arrow = 77
		case 100: case 68: case 77:
			if (cursor.x < size) {
				cursor.lastX = cursor.x++;
				cursor.lastY = cursor.y;
			}
			break;
		//Enter
		case 13:
			if (gameField[cursor.y - 1][cursor.x - 1] == Cell::VOID_CELL) {
				// Міняємо значення тільки тоді, коли клітинка пуста, іначе ігноруєм Ентер
				// Значення береться зі структури Step
				ChangeCell(gameField, size, cursor.x, cursor.y, step.currentSymb);
				NextStep(step);
			}
			break;
		}
	}
}

Winner CheckWin(Cell** gameField, size_t size) {
	// У нас є 3 положення клітинки: пуста, Х, О.
	// При переведенні клітинки з перечислення в int
	// ми отримаємо 0, 1, 2. Отже коли є хоча б одна пуста клітинка
	// при перемноженні рядка, стовпчика або діагоналі ми отримаємо 0.
	// В іншому випадку коли всі елементи співпали ми отримаємо 1 або 8	
	// в залежності від значеннь рядка, стовпця або діагоналі.
	// В інших виипадках ми ці значення не отримаємо, отже 
	// нам необхідно і достатньо перемножити всі рядки, стовпці і діагоналі.

	int diagonal1 = 1,
		diagonal2 = 1;

	for (size_t i = 0; i < size; i++) {
		int verticalMul = 1,
			horizontalMul = 1;
			
		for (size_t j = 0; j < size; j++) {
			verticalMul *= (int)gameField[i][j];
			horizontalMul *= (int)gameField[j][i];
			if (i == j)
				diagonal1 *= (int)gameField[i][j];
			if (size - 1 - j == i)
				diagonal2 *= (int)gameField[i][j];
		}
		// 1^3 = 1
		if (verticalMul == 1 || horizontalMul == 1)
			return Winner::PLAYER_1;
		// 2^3 = 8
		// Here we can check diagonals because one cell cant contain 8
		else if (verticalMul == 8 || horizontalMul == 8 || diagonal1 == 8 || diagonal2 == 8)
			return Winner::PLAYER_2;
	}
	if (diagonal1 == 1 || diagonal2 == 1)
		return Winner::PLAYER_1;
	else if (IsGameOver(gameField, size))
		return Winner::DRAW;
	return Winner::NOTHING;
}

void PlayPVP(Game gameSettings) {
	// Розмір поля
	size_t size = 3;
	Cursor cursor;
	// 2 поля створенні для того, щоб на одному виконувати ігрові дії
	// за допомогою другого відображати поле.
	// Для того щоб перемальовувати лише ті елементи, які були змінені
	// потрібно поле showField.
	Cell** showField = CreateField(size);
	Cell** gameField = CreateField(size);

	Step step;
	int firstPlayer = rand() % 2;
	step.currentSymb = (firstPlayer == 0 ? gameSettings.player1.player : gameSettings.player2.player);
	Winner winner;

	ShowTable();
	do {
		Moves(cursor, gameField, size, step);
		UpdateField(gameField, showField, size);
		ShowCursor(showField, cursor);
		ShowCurrentSymb(step);
		Sleep(100);
		winner = CheckWin(gameField, size);
	} while (winner == Winner::NOTHING);
	ShowWinner(winner, gameSettings);
	
	DeleteField(gameField, size);
	DeleteField(showField, size);
}

void PlayPVC(Game gameSettings) {
	// Розмір поля
	size_t size = 3;
	Cursor cursor;
	// 2 поля створенні для того, щоб на одному виконувати ігрові дії
	// за допомогою другого відображати поле.
	// Для того щоб перемальовувати лише ті елементи, які були змінені
	// потрібно поле showField.
	Cell** showField = CreateField(size);
	Cell** gameField = CreateField(size);
	Step step;
	Winner winner;
	int firstPlayer = rand() % 2;
	step.currentSymb = (firstPlayer == 0 ? gameSettings.player1.player : gameSettings.player2.player);

	ShowTable();
	do {
		if (step.currentSymb != gameSettings.player1.player) {
			switch (gameSettings.difficulty) {
			case Difficulty::EASY:
				EasyMod(gameField, size, step);
				break;
			case Difficulty::MIDDLE:
				MiddleMod(gameField, size, step);
				break;
			case Difficulty::HARD:
				// У HardMod потрібно передавати налаштування гри для того щоб 
				// алгоритм міг визначити хто якими знаками грає.
				HardMod(gameField, size, gameSettings, step);
				break;
			}
		}
			
		else
			Moves(cursor, gameField, size, step);
		UpdateField(gameField, showField, size);
		ShowCursor(showField, cursor);
		ShowCurrentSymb(step);		
		Sleep(100);
		winner = CheckWin(gameField, size);
	} while (winner == Winner::NOTHING);

	ShowWinner(winner, gameSettings);

	DeleteField(gameField, size);
	DeleteField(showField, size);
}

bool IsGameOver(Cell** gameField, size_t size) {
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			if (gameField[i][j] == Cell::VOID_CELL)
				return false;
	return true;
}

void Play(Game gameSettings) {
	if (gameSettings.gamemode == GameMode::PVP)
		PlayPVP(gameSettings);
	else if (gameSettings.gamemode == GameMode::PVC)
		PlayPVC(gameSettings);
	else
		exit(0);
}

void NextStep(Step& step) {
	if (step.currentSymb == Cell::PLAYER_1)
		step.currentSymb = Cell::PLAYER_2;
	else if (step.currentSymb == Cell::PLAYER_2)
		step.currentSymb = Cell::PLAYER_1;
	step.currentStep++;
}

void EasyMod(Cell** gameField, size_t size, Step& step) {
	size_t x, y;
	do {
		x = rand() % size;
		y = rand() % size;
	} while (gameField[y][x] != Cell::VOID_CELL);
	Sleep(100);
	gameField[y][x] = step.currentSymb;
	NextStep(step);
}

void MiddleMod(Cell** gameField, size_t size, Step& step) {
	// В цьому алгоритмі ми перебираємо всі ходи гравця
	// і якщо в якомусь з них гравець виграє ми ставимо блок
	// іначе вибираємо рандомно
	
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			if (gameField[i][j] == Cell::VOID_CELL) {
				gameField[i][j] = (step.currentSymb == Cell::PLAYER_1 ? Cell::PLAYER_2 : Cell::PLAYER_1);
				if (CheckWin(gameField, size) != Winner::NOTHING) {
					Sleep(100);
					gameField[i][j] = step.currentSymb;
					NextStep(step);
					return;
				}
				gameField[i][j] = Cell::VOID_CELL;
			}
		}
	}

	EasyMod(gameField, size, step);
}

int Score(Cell** gameField, Game gameSetting) {
	// У цій функції ми перевіряємо хто виграв і
	// в залежності від цього повертаємо значення.
	// Це потрібно для алгоритму minimax, щоб він вибирав
	// хід ймовірністю перемоги.

	//If win computer return +10
	//If win player return -10
	size_t size = 3;
	if (CheckWin(gameField, size) == Winner::DRAW)
		return 0;
	else if (CheckWin(gameField, size) == Winner::PLAYER_1) {
		if (gameSetting.player1.player == Cell::PLAYER_2)
			return -10;
		else if (gameSetting.player2.player == Cell::PLAYER_2)
			return 10;
	}
	else if (CheckWin(gameField, size) == Winner::PLAYER_2) {
		if (gameSetting.player1.player == Cell::PLAYER_1)
			return -10;
		else if (gameSetting.player2.player == Cell::PLAYER_1)
			return 10;
	}	
}

int MaxSearch(Cell** gameField, size_t size, Game gameSetting) {
	// Шукає найкращий хід комп'ютера
	if (CheckWin(gameField, size) != Winner::NOTHING)
		return Score(gameField, gameSetting);
	Move bestMove;

	int bestMoveScore = -1000;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (gameField[i][j] == Cell::VOID_CELL) {
				gameField[i][j] = gameSetting.player1.player;
				int tempMoveScore = MinSearch(gameField, size, gameSetting);
				if (tempMoveScore >= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.x = j;
					bestMove.y = i;
				}
				gameField[i][j] = Cell::VOID_CELL;
			}
		}
	}

	return bestMoveScore;
}

int MinSearch(Cell** gameField, size_t size, Game gameSetting) {
	// Шукає найкращий хід гравця(найгірший для комп'ютера)
	if (CheckWin(gameField, size) != Winner::NOTHING)
		return Score(gameField, gameSetting);
	Move bestMove;

	int bestMoveScore = 1000;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (gameField[i][j] == Cell::VOID_CELL) {
				gameField[i][j] = gameSetting.player2.player;
				int tempMove = MaxSearch(gameField, size, gameSetting);
				if (tempMove <= bestMoveScore) {
					bestMoveScore = tempMove;
					bestMove.x = j;
					bestMove.y = i;
				}
				gameField[i][j] = Cell::VOID_CELL;
			}
		}
	}

	return bestMoveScore;
}

void HardMod(Cell** gameField, size_t size, Game gameSetting, Step& step) {
	// Функція HardMod вибирає найкращий хід перебравши всі можливі варіанти.
	int bestMoveScore = 100;
	Move bestMove;
	if (step.currentStep == 0) {
		// для першого кроку завжди ставиться знак в центр
		gameField[1][1] = gameSetting.player2.player;
		NextStep(step);
		return;
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (gameField[i][j] == Cell::VOID_CELL) {
				gameField[i][j] = gameSetting.player2.player;
				int tempMoveScore = MaxSearch(gameField, size, gameSetting);
				if (tempMoveScore <= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.x = j;
					bestMove.y = i;
				}
				gameField[i][j] = Cell::VOID_CELL;
			}
		}
	}
	Sleep(100);
	gameField[bestMove.y][bestMove.x] = gameSetting.player2.player;
	NextStep(step);
}