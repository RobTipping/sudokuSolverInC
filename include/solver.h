#ifndef __SOLVER_H__
#define __SOLVER_H__


int validGrid(int grid[9][9]);
int checkSquare(int grid[9][9], int i, int j);
int solveGrid(int grid[9][9]);
int findGridSolution(int grid[9][9], int pos);
// x = y
void gridFill(int x[9][9], int y[9][9]);

#endif
