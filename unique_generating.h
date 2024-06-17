#pragma once

#define SIZE 9

int isSafe(int grid[SIZE][SIZE], int row, int col, int num);
int fillGrid(int grid[SIZE][SIZE]);
int findEmptyLocation(int grid[SIZE][SIZE], int *row, int *col);
int solveSudoku(int grid[SIZE][SIZE], int *solutionCount);
int countSolutions(int grid[SIZE][SIZE]);
void removeNumbers(int grid[SIZE][SIZE], int minHidden, int maxHidden);
void shuffleArray(int *array, int size);
