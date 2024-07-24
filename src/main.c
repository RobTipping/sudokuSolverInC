#include "customStruct.h"
#include "drawFrame.h"
#include "initItems.h"
#include "raylib.h"
#include "userInput.h"

cell grid[81];
int copyGrid[9][9];
button solveButt;
button clearButt;
button clearAllButt;
button inputCell[9];

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

  initGrid(grid, copyGrid);
  initButtons(&solveButt, &clearButt, &clearAllButt, inputCell);

  SetTargetFPS(60);

  initTextures(grid, &solveButt, &clearButt, &clearAllButt, inputCell);

  updateDrawFrame(grid, solveButt, clearButt, clearAllButt, inputCell);
  // Main game loop
  while (!WindowShouldClose()) {
    // Draw
    //----------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      onMouseClick(GetMousePosition(), grid, solveButt, clearButt, clearAllButt, inputCell, copyGrid);
    }
    if (IsKeyPressed(KEY_ENTER)) {
      // add code to see if solution works
      finishGrid(grid, copyGrid);
    }
    if ((key = GetKeyPressed()) != 0) {
      onKeyPress(key, grid, copyGrid);
    }
    updateDrawFrame(grid, solveButt, clearButt, clearAllButt, inputCell);
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  deInitTextures(solveButt, clearButt, clearAllButt);
  CloseWindow();  // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
