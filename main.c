
#include "raylib.h"
// #include "raymath.h"

const int cubeSize = 50;
const int innerCube = cubeSize - 5;
int grid[9][9] = {0};

void updateDrawFrame(void);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "SuDoKu Solver!");

  SetTargetFPS(60);
  // Main game loop
  while (!WindowShouldClose()) {
    // Draw
    //----------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------
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
    int pointX = 10 + (i * cubeSize);
    for (int j = 0; j < 9; j++) {
      int pointY = 10 + (j * cubeSize);
      if (mouseX > pointX && mouseX < pointX + innerCube && mouseY > pointY &&
          mouseY < pointY + innerCube) {
        DrawRectangle(pointX, pointY, innerCube, innerCube, RED);
        DrawText(TextFormat("%d", grid[i][j]), 20 + (i * cubeSize),
                 15 + (j * cubeSize), 45, BLACK);
      } else {
        DrawRectangle(pointX, pointY, innerCube, innerCube, WHITE);
        DrawText(TextFormat("%d", grid[i][j]), 20 + (i * cubeSize),
                 15 + (j * cubeSize), 45, BLACK);
      }
    }
  }

  for (int i = 3; i < 9; i += 3) {
    for (int j = 0; j < 6; j++) {
      DrawLine(5 + j + (i * cubeSize), 10, 5 + j + (i * cubeSize),
               5 + (9 * cubeSize), YELLOW);
      DrawLine(10, 5 + j + (i * cubeSize), 5 + (9 * cubeSize),
               5 + j + (i * cubeSize), YELLOW);
    }
  }

  DrawText(TextFormat("FPS: %d", GetFPS()), 40, 160, 10, DARKGRAY);
  DrawText(TextFormat("Mouse at %d,%d", GetMouseX(), GetMouseY()), 40, 180, 10,
           DARKGRAY);

  EndDrawing();
}
