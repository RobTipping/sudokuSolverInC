#include "drawFrame.h"

#include "customStruct.h"
#include "raylib.h"

Texture2D backgroundTexture;
Texture2D cellTexture;
Texture2D inputCellTexture;

void initTextures(cell grid[81], button* solveButt, button* clearButt, button* clearAllButt, button inputCell[9]) {
  Image backgroundImage = LoadImage("images/testBackGround.png");
  backgroundTexture = LoadTextureFromImage(backgroundImage);
  UnloadImage(backgroundImage);
  Image solveButton = LoadImage("images/testSolveButt.png");
  solveButt->texture = LoadTextureFromImage(solveButton);
  UnloadImage(solveButton);
  Image clearButton = LoadImage("images/testClearButt.png");
  clearButt->texture = LoadTextureFromImage(clearButton);
  UnloadImage(clearButton);
  Image clearAllButton = LoadImage("images/testClearAllButt.png");
  clearAllButt->texture = LoadTextureFromImage(clearAllButton);
  UnloadImage(clearAllButton);
  Image inputCellImage = LoadImage("images/testInputCell.png");
  inputCellTexture = LoadTextureFromImage(inputCellImage);
  UnloadImage(inputCellImage);
  for (int i = 0; i < 9; i++) {
    inputCell[i].texture = inputCellTexture;
  }
  Image cellImage = LoadImage("images/testNormCellValid.png");
  cellTexture = LoadTextureFromImage(cellImage);
  UnloadImage(cellImage);
  for (int i = 0; i < 81; i++) {
    grid[i].texture = cellTexture;
  }
}

void deInitTextures(button solveButt, button clearButt, button clearAllButt) {
  UnloadTexture(backgroundTexture);
  UnloadTexture(cellTexture);
  UnloadTexture(inputCellTexture);
  UnloadTexture(solveButt.texture);
  UnloadTexture(clearButt.texture);
  UnloadTexture(clearAllButt.texture);
}

void updateDrawFrame(cell grid[81], button solveButt, button clearButt, button clearAllButt, button inputCell[9]) {
  // int mouseX = GetMouseX();
  // int mouseY = GetMouseY();
  BeginDrawing();

  // ClearBackground(LIGHTGRAY);
  DrawTextureV(backgroundTexture, (Vector2){0, 0}, WHITE);

  for (int i = 0; i < 81; i++) {
    // would like to do this somewhere else!!
    if (grid[i].selected == false) {
      if (grid[i].validValue == true) {
        grid[i].cellColor = WHITE;
      } else {
        grid[i].cellColor = RED;
      }
    } else {
      if (grid[i].validValue == true) {
        grid[i].cellColor = DARKBLUE;
      } else {
        grid[i].cellColor = DARKPURPLE;
      }
    }

    // DrawRectangleV(grid[i].pos, squareSize, grid[i].cellColor);
    DrawTextureV(grid[i].texture, grid[i].startPos, grid[i].cellColor);
    if (grid[i].value != 0) {
      DrawText(TextFormat("%d", grid[i].value), 10 + grid[i].startPos.x, 5 + grid[i].startPos.y, 45, BLACK);
    }
  }

  DrawTexture(solveButt.texture, solveButt.startPos.x, solveButt.startPos.y, WHITE);
  DrawTexture(clearButt.texture, clearButt.startPos.x, clearButt.startPos.y, WHITE);
  DrawTexture(clearAllButt.texture, clearAllButt.startPos.x, clearAllButt.startPos.y, WHITE);

  for (int i = 0; i < 9; i++) {
    DrawTextureV(inputCell[i].texture, inputCell[i].startPos, WHITE);
    DrawText(TextFormat("%d", i + 1), inputCell[i].startPos.x + 10, inputCell[i].startPos.y + 5, 45, BLACK);
  }

  // DrawText(TextFormat("FPS: %d", GetFPS()), 40, 160, 10, RED);
  // DrawText(TextFormat("Mouse at %d,%d", GetMouseX(), GetMouseY()), 40, 180,
  // 10, RED);

  EndDrawing();
}
