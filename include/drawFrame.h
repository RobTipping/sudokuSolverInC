#ifndef __DRAWFRAME_H__
#define __DRAWFRAME_H__

#include "customStruct.h"


void initTextures(cell grid[81], button* solveButt, button* clearButt, button* clearAllButt, button inputCell[9]);
void deInitTextures(button solveButt, button clearButt, button clearAllButt);
void updateDrawFrame(cell grid[81], button solveButt, button clearButt, button clearAllButt, button inputCell[9]);

#endif
