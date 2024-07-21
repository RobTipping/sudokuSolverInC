#include "raylib.h"
#include "solver.h"
// #include <stdio.h>
//  #include "raymath.h"

typedef struct cell {
  Vector2 pos;
  int value;
  bool selected;
  Color cellColor;
} cell;

cell grid[81];

const int cubeSize = 50;
const int innerCube = cubeSize - 5;
const Vector2 squareSize = {45, 45};
const int padding = 5;
const Color normColor = DARKGRAY;
const Color selColor = DARKBLUE;

int selectedSquare = 0;

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
    if (IsKeyPressed(KEY_ENTER)) {
      // add code to see if solution works
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
    DrawRectangleV(grid[i].pos, squareSize, grid[i].cellColor);
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
      grid[(i * 9) + j].pos.x = pointX;
      grid[(i * 9) + j].pos.y = pointY;
      grid[(i * 9) + j].value = 0;
      grid[(i * 9) + j].selected = false;
      grid[(i * 9) + j].cellColor = normColor;
    }
  }
}

void onMouseClick(Vector2 pos) {
  for (int i = 0; i < 81; i++) {
    if (pos.x > grid[i].pos.x && pos.x < grid[i].pos.x + squareSize.x &&
        pos.y > grid[i].pos.y && pos.y < grid[i].pos.y + squareSize.y) {
      grid[i].selected = true;
      grid[i].cellColor = selColor;
      selectedSquare = i;
    } else {
      grid[i].selected = false;
      grid[i].cellColor = normColor;
    }
  }
}

void onKeyPress(int key) {
  if (key > 58 || key < 47) {
    return;
  }
  if (grid[selectedSquare].selected) {
    grid[selectedSquare].value = key - 48;
  }
}
