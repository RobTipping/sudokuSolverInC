#ifndef __CUSTOMSTRUCT_H__
#define __CUSTOMSTRUCT_H__

#include "raylib.h"

typedef struct cell {
  Vector2 startPos;
  Vector2 endPos;
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

#endif
