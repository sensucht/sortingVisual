/*
 * Given an size input (up to 500 columns) from the user, and the selection
 * of one of the avaliable sorting algorithms, this program will generate an
 * array of said user given size by dynamic memory allocation. It will then
 * assign pseudo-random values (through stdlib.h and time.h functions) to each
 * item of the array. While the true sorting will happen behind the UI, in
 * miliseconds, the user will see an animation of the sorting algorithm's
 * process, slowed down to allow comprehension
 */
#include "../include/app.h"
#include <stdlib.h>
#include <time.h>

int main() {
  //========================================
  // 1. INITIALIZATION AND WINDOW SETUP
  // =======================================
  // Seed random, InitWindow, SetTargetFPS and declares intiializtion variables,
  // along with the UI rectangles.

  srand(time(NULL));
  AppContext app = {0};
  appInit(&app);
  InitWindow(app.screenWidth, app.screenHeight, "sortingVisual");
  SetTargetFPS(60);

  //===================================================
  // 2. MAIN PROGRAM LOOP
  //===================================================

  while (!WindowShouldClose()) {
    //=======================================================
    // 3.1 UPDATE PHASE
    //======================================================
    // Logic and user input
    appUpdate(&app);
    //==================================================
    // 3.2 DRAWING PHASE
    //==================================================
    appDraw(&app);
  }
  //======================================================
  // 4. CLEANUP
  //=====================================================
  appCleanup(&app);
  CloseWindow();
  return 0;
}
