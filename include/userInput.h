#ifndef __USERINPUT_H__
#define __USERINPUT_H__

#include "raylib.h"
#include "customStruct.h"

void onMouseClick(Vector2 pos, cell grid[81], button solveButt, button clearButt, button clearAllButt, button inputCell[9]);
void onKeyPress(int key, cell grid[81]);
void cellInput(int value, cell grid[81]);
void finishGrid(cell grid[81]);
void genCopyGrid(cell grid[81]);

#endif
