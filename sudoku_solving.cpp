#include "stdafx.h"
#include <stdlib.h>
#include "math.h"
#define SIZE 9

void printGrid(int grid[SIZE][SIZE]);
int isSafe(int grid[SIZE][SIZE], int row, int col, int num);
int findEmptyLocation(int grid[SIZE][SIZE], int *row, int *col);
int solveSudoku(int grid[SIZE][SIZE], int *solutionCount, int solutionGrid[SIZE][SIZE]);

void printGrid(int grid[SIZE][SIZE]) {
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			printf("%d ", grid[row][col]);
		}
		printf("\n");
	}
}

int isSafe(int grid[SIZE][SIZE], int row, int col, int num) {
	for (int x = 0; x < SIZE; x++) {
		if (grid[row][x] == num || grid[x][col] == num)
			return 0;
	}
	int box_size = sqrt(SIZE);
	int startRow = row - row % box_size, startCol = col - col % box_size;
	for (int i = 0; i < box_size; i++) {
		for (int j = 0; j < box_size; j++) {
			if (grid[i + startRow][j + startCol] == num)
				return 0;
		}
	}
	return 1;
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

int solveSudoku(int grid[SIZE][SIZE], int *solutionCount, int solutionGrid[SIZE][SIZE]) {
	int row, col;
	if (!findEmptyLocation(grid, &row, &col)) {
		(*solutionCount)++;
		// Copy the current grid to solutionGrid
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				solutionGrid[i][j] = grid[i][j];
			}
		}
		return 1; // A solution is found
	}

	for (int num = 1; num <= SIZE; num++) {
		if (isSafe(grid, row, col, num)) {
			grid[row][col] = num;
			solveSudoku(grid, solutionCount, solutionGrid);
			grid[row][col] = 0; // Backtrack
		}
	}
	return 0;
}

int main() {
	int grid[SIZE][SIZE] = {
		{ 5, 3, 0, 0, 7, 0, 0, 0, 0 },
		{ 6, 0, 0, 1, 9, 5, 0, 0, 0 },
		{ 0, 9, 8, 0, 0, 0, 0, 6, 0 },
		{ 8, 0, 0, 0, 6, 0, 0, 0, 3 },
		{ 4, 0, 0, 8, 0, 3, 0, 0, 1 },
		{ 7, 0, 0, 0, 2, 0, 0, 0, 6 },
		{ 0, 6, 0, 0, 0, 0, 2, 8, 0 },
		{ 0, 0, 0, 4, 1, 9, 0, 0, 5 },
		{ 0, 0, 0, 0, 8, 0, 0, 7, 9 }
	};

	int solutionGrid[SIZE][SIZE] = { 0 };

	printf("Given Sudoku Puzzle:\n");
	printGrid(grid);

	int solutionCount = 0;
	solveSudoku(grid, &solutionCount, solutionGrid);


	if (solutionCount > 0) {
		printf("\nOne of the possible solutions:\n");
		printGrid(solutionGrid);
		printf("\nNumber of possible solutions: %d\n", solutionCount);
	}

	else
	{
		printf("\nNo solution exists\n");
	}
	return 0;
}
