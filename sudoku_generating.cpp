#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 9;
int solvedGrid[SIZE][SIZE];
int puzzleGrid[SIZE][SIZE];

void printGrid(int grid[SIZE][SIZE]);
bool isSafe(int grid[SIZE][SIZE], int row, int col, int num);
bool fillGrid(int grid[SIZE][SIZE]);
bool findEmptyLocation(int grid[SIZE][SIZE], int &row, int &col);
void hideNumbers(int grid[SIZE][SIZE], int minHidden, int maxHidden);

int main() {
	srand(time(0));

	fillGrid(solvedGrid);

	// Copy solvedGrid to puzzleGrid
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			puzzleGrid[row][col] = solvedGrid[row][col];
		}
	}

	hideNumbers(puzzleGrid, 20, 40);

	cout << "Sudoku Puzzle:" << endl;
	printGrid(puzzleGrid);

	cout << "\nSolved Sudoku:" << endl;
	printGrid(solvedGrid);

	return 0;
}

void printGrid(int grid[SIZE][SIZE]) {
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			cout << grid[row][col] << " ";
		}
		cout << endl;
	}
}

bool isSafe(int grid[SIZE][SIZE], int row, int col, int num) {
	for (int x = 0; x < SIZE; x++) {
		if (grid[row][x] == num || grid[x][col] == num)
			return false;
	}
	int startRow = row - row % 3, startCol = col - col % 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (grid[i + startRow][j + startCol] == num)
				return false;
		}
	}
	return true;
}

bool fillGrid(int grid[SIZE][SIZE]) {
	int row, col;
	if (!findEmptyLocation(grid, row, col))
		return true; // Success!

	vector<int> numbers{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	random_shuffle(numbers.begin(), numbers.end());

	for (int num : numbers) {
		if (isSafe(grid, row, col, num)) {
			grid[row][col] = num;
			if (fillGrid(grid))
				return true;
			grid[row][col] = 0;
		}
	}
	return false;
}

bool findEmptyLocation(int grid[SIZE][SIZE], int &row, int &col) {
	for (row = 0; row < SIZE; row++) {
		for (col = 0; col < SIZE; col++) {
			if (grid[row][col] == 0)
				return true;
		}
	}
	return false;
}

void hideNumbers(int grid[SIZE][SIZE], int minHidden, int maxHidden) {
	int count = minHidden + rand() % (maxHidden - minHidden + 1);
	while (count > 0) {
		int row = rand() % SIZE;
		int col = rand() % SIZE;
		if (grid[row][col] != 0) {
			grid[row][col] = 0;
			count--;
		}
	}
}
