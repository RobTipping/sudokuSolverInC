#include "raylib.h"
#include "solver.h"
// #include <stdio.h>
//  #include "raymath.h"

extern int solvedGrid[9][9];

typedef struct cell {
  Vector2 pos;
  int value;
  bool validValue;
  bool selected;
  Color cellColor;
  Texture2D texture;
} cell;

typedef struct button {
  Vector2 startPos;
  Vector2 endPos;
  Texture2D texture;
} button;

cell grid[81];
int copyGrid[9][9];
button solveButt;
button clearButt;
button inputCell[9];

const int cubeSize = 50;
const int innerCube = cubeSize - 5;
const Vector2 squareSize = {45, 45};
const int padding = 5;
const Color normColorValid = WHITE;
const Color selColorValid = DARKBLUE;
const Color normColorInvalid = RED;
const Color selColorInvalid = DARKPURPLE;

int selectedSquare = 0;

void updateDrawFrame(void);
void initGrid(void);
void onMouseClick(Vector2 pos);
void onKeyPress(int key);
void finishGrid(void);
void initButtons(void);
void cellInput(int value);
void clearGrid(void);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 600;
  const int screenHeight = 600;
  int key = 0;

  InitWindow(screenWidth, screenHeight, "SuDoKu Solver!");

  initGrid();
  initButtons();

  SetTargetFPS(60);
  updateDrawFrame();
  // Main game loop
  while (!WindowShouldClose()) {
    // Draw
    //----------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      onMouseClick(GetMousePosition());
    }
    if (IsKeyPressed(KEY_ENTER)) {
      // add code to see if solution works
      finishGrid();
    }
    if ((key = GetKeyPressed()) != 0) {
      onKeyPress(key);
    }
    updateDrawFrame();
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

void updateDrawFrame(void) {
  int mouseX = GetMouseX();
  int mouseY = GetMouseY();
  BeginDrawing();

  ClearBackground(LIGHTGRAY);

  for (int i = 0; i < 81; i++) {
    if (grid[i].selected == false) {
      if (grid[i].validValue == true) {
        grid[i].cellColor = normColorValid;
      } else {
        grid[i].cellColor = normColorInvalid;
      }
    } else {
      if (grid[i].validValue == true) {
        grid[i].cellColor = selColorValid;
      } else {
        grid[i].cellColor = selColorInvalid;
      }
    }

    // DrawRectangleV(grid[i].pos, squareSize, grid[i].cellColor);
    DrawTextureV(grid[i].texture, grid[i].pos, grid[i].cellColor);
    DrawText(TextFormat("%d", grid[i].value), 10 + grid[i].pos.x,
             5 + grid[i].pos.y, 45, BLACK);
  }

  for (int i = 3; i < 9; i += 3) {
    for (int j = 0; j < 6; j++) {
      DrawLine(5 + j + (i * cubeSize), 10, 5 + j + (i * cubeSize),
               5 + (9 * cubeSize), YELLOW);
      DrawLine(10, 5 + j + (i * cubeSize), 5 + (9 * cubeSize),
               5 + j + (i * cubeSize), YELLOW);
    }
  }

  DrawTexture(solveButt.texture, solveButt.startPos.x, solveButt.startPos.y,
              WHITE);
  DrawTexture(clearButt.texture, clearButt.startPos.x, clearButt.startPos.y,
              WHITE);

  for (int i = 0; i < 9; i++) {
    DrawTextureV(inputCell[i].texture, inputCell[i].startPos, WHITE);
    DrawText(TextFormat("%d", i + 1), inputCell[i].startPos.x + 10,
             inputCell[i].startPos.y + 5, 45, BLACK);
  }

  // DrawText(TextFormat("FPS: %d", GetFPS()), 40, 160, 10, RED);
  // DrawText(TextFormat("Mouse at %d,%d", GetMouseX(), GetMouseY()), 40, 180,
  // 10, RED);

  EndDrawing();
}

void initGrid() {
  Image cellImage = LoadImage("images/testNormCellValid.png");
  Texture2D tempTexture = LoadTextureFromImage(cellImage);
  UnloadImage(cellImage);
  for (int i = 0; i < 9; i++) {
    int pointY = 10 + (i * (squareSize.y + padding));
    for (int j = 0; j < 9; j++) {
      int pointX = 10 + (j * (squareSize.x + padding));
      grid[(i * 9) + j].pos.x = pointX;
      grid[(i * 9) + j].pos.y = pointY;
      grid[(i * 9) + j].value = 0;
      grid[(i * 9) + j].selected = false;
      grid[(i * 9) + j].cellColor = normColorValid;
      grid[(i * 9) + j].validValue = true;
      grid[(i * 9) + j].texture = tempTexture;
      copyGrid[i][j] = 0;
    }
  }
}

void clearGrid(void) {
  for (int i = 0; i < 9; i++) {
    int pointY = 10 + (i * (squareSize.y + padding));
    for (int j = 0; j < 9; j++) {
      int pointX = 10 + (j * (squareSize.x + padding));
      grid[(i * 9) + j].pos.x = pointX;
      grid[(i * 9) + j].pos.y = pointY;
      grid[(i * 9) + j].value = 0;
      grid[(i * 9) + j].selected = false;
      grid[(i * 9) + j].cellColor = normColorValid;
      grid[(i * 9) + j].validValue = true;
      copyGrid[i][j] = 0;
    }
  }
}

void onMouseClick(Vector2 pos) {
  for (int i = 0; i < 9; i++) {
    if (pos.x > inputCell[i].startPos.x && pos.x < inputCell[i].endPos.x &&
        pos.y > inputCell[i].startPos.y && pos.y < inputCell[i].endPos.y) {
      if (grid[selectedSquare].selected == true) {
        cellInput(i + 1);
        return;
      }
    }
  }
  for (int i = 0; i < 81; i++) {
    if (pos.x > grid[i].pos.x && pos.x < grid[i].pos.x + squareSize.x &&
        pos.y > grid[i].pos.y && pos.y < grid[i].pos.y + squareSize.y) {
      grid[i].selected = true;
      selectedSquare = i;
    } else {
      grid[i].selected = false;
    }
  }
  if (pos.x > solveButt.startPos.x && pos.x < solveButt.endPos.x &&
      pos.y > solveButt.startPos.y && pos.y < solveButt.endPos.y) {
    finishGrid();
  }
  if (pos.x > clearButt.startPos.x && pos.x < clearButt.endPos.x &&
      pos.y > clearButt.startPos.y && pos.y < clearButt.endPos.y) {
    clearGrid();
  }
}

void onKeyPress(int key) {
  if (key > 58 || key < 47) {
    return;
  }
  if (grid[selectedSquare].selected) {
    cellInput(key - 48);
  }
}

void finishGrid(void) {
  if (solveGrid(copyGrid) == 0) {
    return;
  }
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      grid[(i * 9) + j].value = solvedGrid[i][j];
    }
  }
}

void initButtons(void) {
  Image solveButton = LoadImage("images/testSolveButt.png");
  solveButt.texture = LoadTextureFromImage(solveButton);
  UnloadImage(solveButton);
  Image clearButton = LoadImage("images/testClearButt.png");
  clearButt.texture = LoadTextureFromImage(clearButton);
  UnloadImage(clearButton);
  Image inputCellImage = LoadImage("images/testInputCell.png");
  Texture2D tempTextrue = LoadTextureFromImage(inputCellImage);
  UnloadImage(inputCellImage);
  solveButt.startPos.x = 475;
  solveButt.startPos.y = 10;
  solveButt.endPos.x = solveButt.startPos.x + 100;
  solveButt.endPos.y = solveButt.startPos.y + 25;
  clearButt.startPos.x = 475;
  clearButt.startPos.y = 50;
  clearButt.endPos.x = clearButt.startPos.x + 100;
  clearButt.endPos.y = clearButt.startPos.y + 25;
  for (int i = 0; i < 9; i++) {
    inputCell[i].texture = tempTextrue;
    inputCell[i].startPos.x = 10 + (i * (squareSize.x + padding));
    inputCell[i].startPos.y = 475;
    inputCell[i].endPos.x = inputCell[i].startPos.x + squareSize.x;
    inputCell[i].endPos.y = inputCell[i].startPos.y + squareSize.y;
  }
}

void cellInput(int value) {
  grid[selectedSquare].value = value;
  int x = (selectedSquare / 9);
  int y = (selectedSquare % 9);
  copyGrid[x][y] = grid[selectedSquare].value;
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
