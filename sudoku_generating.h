#pragma once

#define SIZE 9



bool isSafe(int grid[SIZE][SIZE], int row, int col, int num);
bool fillGrid(int grid[SIZE][SIZE]);
bool findEmptyLocation(int grid[SIZE][SIZE], int &row, int &col);
void hideNumbers(int grid[SIZE][SIZE], int minHidden, int maxHidden);
