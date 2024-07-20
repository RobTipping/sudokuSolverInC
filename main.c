#include "raylib.h"
#include <stdio.h>
// #include "raymath.h"

typedef struct cell {
  Vector2 pos;
  int value;
  bool selected;
} cell;

cell grid[9][9];

const int cubeSize = 50;
const int innerCube = cubeSize - 5;
const Vector2 squareSize = {45, 45};
const int padding = 5;

int selectedSquare[2] = {0, 0};

void updateDrawFrame(void);
void initGrid(void);
void onMouseClick(Vector2 pos);
void onKeyPress(int key);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 600;
  const int screenHeight = 600;
  int key = 0;

  initGrid();

  InitWindow(screenWidth, screenHeight, "SuDoKu Solver!");

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

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      DrawRectangleV(grid[i][j].pos, squareSize, DARKGRAY);
      DrawText(TextFormat("%d", grid[i][j].value), 20 + (j * cubeSize),
               15 + (i * cubeSize), 45, BLACK);
    }
  }
  if (grid[selectedSquare[0]][selectedSquare[1]].selected) {
    DrawRectangleV(grid[selectedSquare[0]][selectedSquare[1]].pos, squareSize,
                   BLUE);
    DrawText(TextFormat("%d", grid[selectedSquare[0]][selectedSquare[1]].value),
             10 + grid[selectedSquare[0]][selectedSquare[1]].pos.x,
             5 + grid[selectedSquare[0]][selectedSquare[1]].pos.y, 45, BLACK);
  }

  for (int i = 3; i < 9; i += 3) {
    for (int j = 0; j < 6; j++) {
      DrawLine(5 + j + (i * cubeSize), 10, 5 + j + (i * cubeSize),
               5 + (9 * cubeSize), YELLOW);
      DrawLine(10, 5 + j + (i * cubeSize), 5 + (9 * cubeSize),
               5 + j + (i * cubeSize), YELLOW);
    }
  }

  DrawText(TextFormat("FPS: %d", GetFPS()), 40, 160, 10, RED);
  DrawText(TextFormat("Mouse at %d,%d", GetMouseX(), GetMouseY()), 40, 180, 10,
           RED);

  EndDrawing();
}

void initGrid() {
  for (int i = 0; i < 9; i++) {
    int pointY = 10 + (i * (squareSize.y + padding));
    for (int j = 0; j < 9; j++) {
      int pointX = 10 + (j * (squareSize.x + padding));
      grid[i][j].pos.x = pointX;
      grid[i][j].pos.y = pointY;
      grid[i][j].value = 0;
      grid[i][j].selected = false;
    }
  }
}

void onMouseClick(Vector2 pos) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (pos.x > grid[i][j].pos.x && pos.x < grid[i][j].pos.x + squareSize.x &&
          pos.y > grid[i][j].pos.y && pos.y < grid[i][j].pos.y + squareSize.y) {
        grid[i][j].selected = true;
        selectedSquare[0] = i;
        selectedSquare[1] = j;
      } else {
        grid[i][j].selected = false;
      }
    }
  }
}

void onKeyPress(int key) {
  if (key > 58 || key < 47) {
    return;
  }
  if (grid[selectedSquare[0]][selectedSquare[1]].selected) {
    grid[selectedSquare[0]][selectedSquare[1]].value = key - 48;
  }
}
