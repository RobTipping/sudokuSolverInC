#include "initItems.h"

#include "customStruct.h"
#include "raylib.h"

const Vector2 squareSize = {45, 45};
const int padding = 5;

void initGrid(cell grid[81]) {
  for (int i = 0; i < 9; i++) {
    int pointY = 10 + (i * (squareSize.y + padding));
    for (int j = 0; j < 9; j++) {
      int pointX = 10 + (j * (squareSize.x + padding));
      grid[(i * 9) + j].startPos.x = pointX;
      grid[(i * 9) + j].startPos.y = pointY;
      grid[(i * 9) + j].endPos.x = grid[(i * 9) + j].startPos.x + squareSize.x;
      grid[(i * 9) + j].endPos.y = grid[(i * 9) + j].startPos.y + squareSize.y;
      grid[(i * 9) + j].value = 0;
      grid[(i * 9) + j].selected = false;
      grid[(i * 9) + j].cellColor = WHITE;
      grid[(i * 9) + j].validValue = true;
    }
  }
}

void initButtons(button* solveButt, button* clearButt, button* clearAllButt, button inputCell[9]) {
  solveButt->startPos.x = 475;
  solveButt->startPos.y = 10;
  solveButt->endPos.x = solveButt->startPos.x + 100;
  solveButt->endPos.y = solveButt->startPos.y + 25;
  clearButt->startPos.x = 475;
  clearButt->startPos.y = 50;
  clearButt->endPos.x = clearButt->startPos.x + 100;
  clearButt->endPos.y = clearButt->startPos.y + 25;
  clearAllButt->startPos.x = 475;
  clearAllButt->startPos.y = 90;
  clearAllButt->endPos.x = clearAllButt->startPos.x + 100;
  clearAllButt->endPos.y = clearAllButt->startPos.y + 25;
  for (int i = 0; i < 9; i++) {
    inputCell[i].startPos.x = 10 + (i * (squareSize.x + padding));
    inputCell[i].startPos.y = 475;
    inputCell[i].endPos.x = inputCell[i].startPos.x + squareSize.x;
    inputCell[i].endPos.y = inputCell[i].startPos.y + squareSize.y;
  }
}
