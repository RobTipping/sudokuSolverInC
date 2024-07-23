#include "solver.h"

int originalGrid[9][9];
int solvedGrid[9][9];

int validGrid(int grid[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (grid[i][j] != 0) {
        if (checkSquare(grid, i, j) == 0) {
          return 0;
        }
      }
    }
  }
  return 1;
}

int checkSquare(int grid[9][9], int i, int j) {
  // find 3x3
  int a = (i / 3) * 3;
  int b = (j / 3) * 3;
  for (int k = 0; k < 9; k++) {
    // Check Row
    if (j != k && grid[i][j] == grid[i][k]) {
      return 0;
    }
    // Check Column
    if (i != k && grid[i][j] == grid[k][j]) {
      return 0;
    } // Check 3x3 grid
    int x = a + k / 3;
    int y = b + k % 3;
    if (i == x && j == y) {
      continue;
    }
    if (grid[i][j] == grid[x][y]) {
      return 0;
    }
  }
  return 1;
}

int solveGrid(int grid[9][9]) {
  // originalGrid = grid; need to work out how we copy this
  gridFill(originalGrid, grid);
  if (validGrid(grid) == 0) {
    return 0;
  }
  if (findGridSolution(grid, 0) == 1) {
    return 1; // need to pass solvedGrid }
  }
  return 0;
}

int findGridSolution(int grid[9][9], int pos) {
  int x = (pos / 9);
  int y = (pos % 9);
  if (originalGrid[x][y] != 0) {
    if (pos < 80) {
      return findGridSolution(grid, pos + 1);
    }
    if (checkSquare(grid, x, y) == 1) {
      gridFill(solvedGrid, grid);
      return 1;
    }
    return 0;
  }
  for (int i = 1; i < 10; i++) {
    grid[x][y] = i;
    if (checkSquare(grid, x, y) == 1) {
      if (pos == 80) {
        gridFill(solvedGrid, grid);
        return 1;
      }
      if (findGridSolution(grid, pos + 1) == 1) {
        return 1;
      }
    }
  }
  grid[x][y] = 0;
  return 0;
}

void gridFill(int x[9][9], int y[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      x[i][j] = y[i][j];
    }
  }
}
