#include "stdafx.h"

#include "stdlib.h"
#include "time.h"
#include "unique_generating.h"




int isSafe(int grid[SIZE][SIZE], int row, int col, int num) {
	for (int x = 0; x < SIZE; x++) {
		if (grid[row][x] == num || grid[x][col] == num)
			return 0;
	}
	int startRow = row - row % 3, startCol = col - col % 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (grid[i + startRow][j + startCol] == num)
				return 0;
		}
	}
	return 1;
}

void shuffleArray(int *array, int size) {
	for (int i = size - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

int findEmptyLocation(int grid[SIZE][SIZE], int *row, int *col) {
	for (*row = 0; *row < SIZE; (*row)++) {
		for (*col = 0; *col < SIZE; (*col)++) {
			if (grid[*row][*col] == 0)
				return 1;
		}
	}
	return 0;
}

int fillGrid(int grid[SIZE][SIZE]) {
	int row, col;
	if (!findEmptyLocation(grid, &row, &col))
		return 1; // Success!

	int numbers[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	shuffleArray(numbers, SIZE);

	for (int i = 0; i < SIZE; i++) {
		int num = numbers[i];
		if (isSafe(grid, row, col, num)) {
			grid[row][col] = num;
			if (fillGrid(grid))
				return 1;
			grid[row][col] = 0; // Backtrack
		}
	}
	return 0;
}


int solveSudoku(int grid[SIZE][SIZE], int *solutionCount) {
	int row, col;
	if (!findEmptyLocation(grid, &row, &col)) {
		(*solutionCount)++;
		return 1; // A solution is found
	}

	for (int num = 1; num <= SIZE; num++) {
		if (isSafe(grid, row, col, num)) {
			grid[row][col] = num;
			solveSudoku(grid, solutionCount);
			grid[row][col] = 0; // Backtrack
		}
	}
	return 0;
}

int countSolutions(int grid[SIZE][SIZE]) {
	int solutionCount = 0;
	solveSudoku(grid, &solutionCount);
	return solutionCount;
}


void removeNumbers(int grid[SIZE][SIZE], int minHidden, int maxHidden) {
	int totalCellsToRemove = minHidden + rand() % (maxHidden - minHidden + 1);
	int hints = SIZE * SIZE - totalCellsToRemove;

	while (totalCellsToRemove > 0) {
		int row = rand() % SIZE;
		int col = rand() % SIZE;

		if (grid[row][col] != 0) {
			int backup = grid[row][col];
			grid[row][col] = 0;

			int solutionCount = 0;
			solveSudoku(grid, &solutionCount);

			if (solutionCount != 1) {
				grid[row][col] = backup; // Restore the number
			}
			else {
				totalCellsToRemove--;
			}
		}
	}
}




