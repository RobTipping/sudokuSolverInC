#include "userInput.h"

#include "customStruct.h"
#include "initItems.h"
#include "raylib.h"
#include "solver.h"

extern int solvedGrid[9][9];
int copyGrid[9][9];
int selectedSquare = 0;

void onMouseClick(Vector2 pos, cell grid[81], button solveButt, button clearButt, button clearAllButt, button inputCell[9]) {
  for (int i = 0; i < 9; i++) {
    if (pos.x > inputCell[i].startPos.x && pos.x < inputCell[i].endPos.x && pos.y > inputCell[i].startPos.y && pos.y < inputCell[i].endPos.y) {
      if (grid[selectedSquare].selected == true) {
        cellInput(i + 1, grid);
        return;
      }
    }
  }
  if (pos.x > clearButt.startPos.x && pos.x < clearButt.endPos.x && pos.y > clearButt.startPos.y && pos.y < clearButt.endPos.y) {
    if (grid[selectedSquare].selected == true) {
      cellInput(0, grid);
      return;
    }
  }
  for (int i = 0; i < 81; i++) {
    if (pos.x > grid[i].startPos.x && pos.x < grid[i].endPos.x && pos.y > grid[i].startPos.y && pos.y < grid[i].endPos.y) {
      grid[i].selected = true;
      selectedSquare = i;
    } else {
      grid[i].selected = false;
    }
  }
  if (pos.x > solveButt.startPos.x && pos.x < solveButt.endPos.x && pos.y > solveButt.startPos.y && pos.y < solveButt.endPos.y) {
    finishGrid(grid);
  }
  if (pos.x > clearAllButt.startPos.x && pos.x < clearAllButt.endPos.x && pos.y > clearAllButt.startPos.y && pos.y < clearAllButt.endPos.y) {
    initGrid(grid);
  }
}

void onKeyPress(int key, cell grid[81]) {
  if (key > 58 || key < 47) {
    return;
  }
  if (grid[selectedSquare].selected) {
    cellInput(key - 48, grid);
  }
}

void cellInput(int value, cell grid[81]) {
  grid[selectedSquare].value = value;
  int x = (selectedSquare / 9);
  int y = (selectedSquare % 9);
  genCopyGrid(grid);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (copyGrid[i][j] == 0) {
        grid[(i * 9) + j].validValue = true;
        continue;
      }
      if (checkSquare(copyGrid, i, j) == 0) {
        grid[(i * 9) + j].validValue = false;
      } else {
        grid[(i * 9) + j].validValue = true;
      }
    }
  }
}

void finishGrid(cell grid[81]) {
  genCopyGrid(grid);
  if (solveGrid(copyGrid) == 0) {
    return;
  }
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      grid[(i * 9) + j].value = solvedGrid[i][j];
    }
  }
}

void genCopyGrid(cell grid[81]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      copyGrid[i][j] = grid[(i * 9) + j].value;
    }
  }
}
