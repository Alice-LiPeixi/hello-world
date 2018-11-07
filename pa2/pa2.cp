//  pa2.cpp
//	minesweeper

#include "definition.h"

/* ATTENTION:
 * 1. PLEASE Read the introduction before each function carefully!
 * 2. You can ONLY add your code where you find a comment:
 *   // complete your code here
 * 3. DO NOT modify other things!!
 */

/************* Functions Requires You to Complete. *************/

/* ================================================================
 * Randomly place mines and flowers on the play board.
 * mine and flower should not exist in the same cell.
 * ----------------------------------------------------------------
 * Input:
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - num_mines: number of mines;
 * - num_flowers: number of flowers;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * ----------------------------------------------------------------
 */
void generateMineAndFlower(Cell cell[MAXSIZE][MAXSIZE], int num_mines,
                           int num_flowers, int height, int width) {
	cout << "\nPlacing mines and flowers ......";

	// cout << "MAXSIZE: " << MAXSIZE << endl;
	// cout << "num_mines: " << num_mines << endl;
	// cout << "num_flowers: " << num_flowers << endl;
	// cout << "height: " << height << endl;
	// cout << "width: " << width << endl;

	srand (time(NULL));

	while (num_flowers > 0 || num_mines > 0) {
		int i = rand() % height;
		int j = rand() % width;
		if (num_flowers > 0 && cell[i][j].content == EMPTY) {
			// try to place one flower
			cell[i][j].content = FLOWER;
			num_flowers -= 1;
		} else if (num_mines > 0 && cell[i][j].content == EMPTY) {
			cell[i][j].content = MINE;
			num_mines -= 1;
		}
	}
}

/* ================================================================
 * Count the number of surrounding mines of all cells on the game board.
 * You should compute this number not just for empty cells,
 * but also the mine cells and flower cells.
 * ----------------------------------------------------------------
 * Input:
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * ----------------------------------------------------------------
 */
void generateMinecountMap(Cell cell[MAXSIZE][MAXSIZE], int height,
	                      int width) {

	cout << "\ngenerate real maps ......" << endl;

	// complete your code here
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (cell[i][j].content == MINE) {
				if (isOnBoard(i - 1, j - 1, height, width)) {
					cell[i - 1][j - 1].count += 1;
				}
				if (isOnBoard(i, j - 1, height, width)) {
					cell[i][j - 1].count += 1;
				}
				if (isOnBoard(i + 1, j - 1, height, width)) {
					cell[i + 1][j - 1].count += 1;
				}
				if (isOnBoard(i - 1, j, height, width)) {
					cell[i - 1][j].count += 1;
				}
				if (isOnBoard(i + 1, j, height, width)) {
					cell[i + 1][j].count += 1;
				}
				if (isOnBoard(i - 1, j + 1, height, width)) {
					cell[i - 1][j + 1].count += 1;
				}
				if (isOnBoard(i, j + 1, height, width)) {
					cell[i][j + 1].count += 1;
				}
				if (isOnBoard(i + 1, j + 1, height, width)) {
					cell[i + 1][j + 1].count += 1;
				}
			}
		}
	}
}

/* ================================================================
 * Sweep the empty cell recursively.
 * You are REQUIRED to implement this function using recursion.
 * You will receive NO mark if your implementation is not an recursion.
 * ----------------------------------------------------------------
 * Input:
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * - row: index of current row;
 * - col: index of current column;
 * Output:
 * - additional_life: how many additional lives are obtained
 * ----------------------------------------------------------------
 */
int recursiveSweep(Cell cell[MAXSIZE][MAXSIZE], int height, int width,
	               int row, int col) {
	int life = 0;
	cout << "recursive sweep: " << row << " " << col << "content: " << cell[row][col].content << endl;
	if (cell[row][col].swept || cell[row][col].marked) {
		return life;
	}

	cell[row][col].swept = true;
	if (cell[row][col].content == MINE) {
		// it is a mine, life -1
		life = -1;
	}
	if (cell[row][col].content == FLOWER) {
		// it is a flower, life +	1
		life = 1;
	}
	if (cell[row][col].content == EMPTY) {
		// empty
		if (cell[row][col].count == 0) {
			// check neigbour cells
			if (isOnBoard(row, col - 1, height, width)) {
				life += recursiveSweep(cell, height, width, row, col - 1);
			}
			if (isOnBoard(row - 1, col, height, width)) {
				life += recursiveSweep(cell, height, width, row - 1, col);
			}
			if (isOnBoard(row + 1, col, height, width)) {
				life += recursiveSweep(cell, height, width, row + 1, col);
			}
			if (isOnBoard(row, col + 1, height, width)) {
				life += recursiveSweep(cell, height, width, row, col + 1);
			}
		}
	}
	return life;
}

/* ================================================================
 * Run the game according to the operation chosen
 * ATTENTION:
 * 1. you will use recursiveSweep() in this function.
 * 2. you will use isOnBoard() to help validate the input.
 * ----------------------------------------------------------------
 * Input:
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * - row: index of current row;
 * - col: index of current column;
 * - life: record number of lives remaining;
 * - num_mines: number of mines;
 * - num_marked_mines: number of mines marked as mine by player;
 * - op: operation taken. { 0: sweep; 1: mark; 2: unmark}
 * ----------------------------------------------------------------
 */
void operation(Cell cell[MAXSIZE][MAXSIZE], int height, int width,
	           int row , int col, int& life, int num_mines,
	           int& num_marked_mines, int op) {

	/* choose to sweep */
	if (op == 0) {
		life += recursiveSweep(cell, height, width, row, col);
	}

	/* choose to mark */
	if (op == 1) {
		if (num_marked_mines < num_mines && !cell[row][col].swept && !cell[row][col].marked) {
			cell[row][col].marked = true;
			if (cell[row][col].content == FLOWER) {
				cell[row][col].swept = true;
			} else {
				num_marked_mines += 1;
			}
		}
	}

	/* choose to unmark */
	if (op == 2) {
		if (num_marked_mines > 0 && !cell[row][col].swept && cell[row][col].marked) {
			cell[row][col].marked = false;
			num_marked_mines -= 1;
		}
	}
}

/* ================================================================
 * Check game state: win/lose/continue
 * ----------------------------------------------------------------
 * Input:
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - num_mines: number of mines;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * - life: record number of lives remaining;
 * Output:
 * - {return -1: lose; return 0: continue; return 1: win}
 * ----------------------------------------------------------------
 */
int checkWin(const Cell cell[MAXSIZE][MAXSIZE], int num_mines,
             int height, int width, int life) {

	// complete your code here
	if (life <= 0) {
		return -1;
	}
	bool isWin = true;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (!cell[i][j].swept && cell[i][j].content != MINE) {
				isWin = false;
			}
		}
	}
	return isWin ? 1 : 0;
}
