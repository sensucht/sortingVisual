/*
 * All the functions and code previously in main.c was moved to this header
 * for better modularization and organization of the program. Variables were all
 * put inside a struct so they could be better organized. Functions were created
 * for initialization, updating, drawing and cleanup of dynamically allocated
 * memory.
 */

#ifndef APP_H
#define APP_H

#include "raylib.h"
#include "sorting.h"
#include <stdbool.h>

typedef enum { MENU, SORTING } State;

typedef struct {
  State currentState;

  int screenWidth;
  int screenHeight;

  int size;
  int *visualArray;
  int *backgroundArray;
  Action *script;
  int totalActions;
  int actionIndex;
  int activeA;
  int activeB;
  int actionType;
  bool isAnimating;

  char inputText[5];
  int charCount;

  Rectangle textBox;
  Rectangle buttonBubble;
  Rectangle buttonSelection;
  Rectangle buttonInsertion;
  Rectangle buttonBack;

} AppContext;

void appInit(AppContext *app);
void appUpdate(AppContext *app);
void appDraw(AppContext *app);
void appCleanup(AppContext *app);

#endif // !APP_H
