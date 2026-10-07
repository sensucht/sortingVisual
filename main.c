/*
 * Given an size input (up to 9 integer digits) from the user, and the selection
 * of one of the avaliable sorting algorithms, this program will generate an
 * array of said user given size by dynamic memory allocation. It will then
 * assign pseudo-random values (through stdlib.h and time.h functions) to each
 * item of the array. While the true sorting will happen behind the UI, in
 * miliseconds, the user will see an animation of the sorting algorithm's
 * process, slowed down to allow comprehension
 */
#include "arrayManager.h"
#include "graphics.h"
#include "raylib.h"
#include "sorting.h"
#include <stdlib.h>
#include <time.h>

typedef enum {
  MENU,
  SORTING
} State; // Defines two possible states for the program

int main() {
  //========================================
  // 1. INITIALIZATION AND WINDOW SETUP
  // =======================================
  // Seed random, InitWindow, SetTargetFPS and declares state variable

  srand(time(NULL));

  const int screenWidth = 1024;
  const int screenHeight = 768;
  InitWindow(screenWidth, screenHeight, "visualSort");
  SetTargetFPS(60);
  State currentState = MENU;

  int size = 0;
  int *visualArray = NULL;
  int *backgroundArray = NULL;
  Action *script = NULL;
  int totalActions = 0;
  int actionIndex = 0;
  int activeA = -1;
  int activeB = -1;
  int actionType = -1; // 0 = COMPARE, 1 = SWAP
  bool isAnimating = false;
  bool isSorting = false;

  char inputText[10] = "\0";
  int charCount = 0;

  //=========================================
  // 2. UI RECTANGLES
  //=========================================
  // Defines the user input text box, the sorting buttons and the return
  // buttons here so they are easy to tweak later.

  Rectangle textBox = {screenWidth / 2 - 100, screenHeight / 2 - 80, 200, 40};
  Rectangle buttonBubble = {screenWidth / 2 - 150, screenHeight / 2 + 80, 140,
                            40};
  Rectangle buttonSelection = {screenWidth / 2 + 10, screenHeight / 2 + 80, 140,
                               40};
  Rectangle buttonBack = {20, 20, 100, 30};

  //===================================================
  // 3. MAIN PROGRAM LOOP
  //===================================================

  while (!WindowShouldClose()) {
    Vector2 mousePoint = GetMousePosition();

    //=======================================================
    // 3.1 UPDATE PHASE
    //======================================================
    // Logic and user input

    if (currentState == MENU) {
      // -----Text box input-------
      int key = GetCharPressed();
      while (key > 0) {
        // Only accepts numeric inputs (ASCII 48-57) and prevents array overflow
        if ((key >= 48) && (key <= 57) && (charCount < 9)) {
          inputText[charCount] = (char)key;
          inputText[charCount + 1] = '\0';
          charCount++;
        }
        key = GetCharPressed();
      }

      if (IsKeyPressed(KEY_BACKSPACE) && charCount > 0) {
        // Allows for deleting text
        charCount--;
        inputText[charCount] = '\0';
      }

      // -------Button clicks and array generation------------

      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && charCount > 0) {
        size = atoi(inputText); // Transforms the user input (a string) into a
                                // integer, to allow the given size to be used
                                // in the defined functions

        if (CheckCollisionPointRec(mousePoint, buttonBubble)) {
          // If the mouse clicks the bubble sort button, executes bubble sort
          visualArray = arrayCreate(size);
          backgroundArray = arrayCreate(size);
          script = (Action *)malloc(size * size * sizeof(Action));

          arrayGenerateData(visualArray, size, 50, screenHeight - 100);
          arrayCopy(backgroundArray, visualArray, size);

          recordBubbleSort(backgroundArray, size, script, &totalActions);
          isAnimating = true;
          currentState = SORTING;
        }

        if (CheckCollisionPointRec(mousePoint, buttonSelection)) {
          // If the mouse clicks the selection sort button, executes selection
          // sort
          visualArray = arrayCreate(size);
          backgroundArray = arrayCreate(size);
          script = (Action *)malloc(size * size * sizeof(Action));

          arrayGenerateData(visualArray, size, 50, screenHeight - 100);
          arrayCopy(backgroundArray, visualArray, size);

          recordSelectionSort(backgroundArray, size, script, &totalActions);
          isAnimating = true;
          currentState = SORTING;
        }
      }
      //----------------Return button--------------
    } else if (currentState == SORTING) {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
          CheckCollisionPointRec(mousePoint, buttonBack)) {
        // If the mouse clicks the return button, frees the dinamically
        // allocated variables and returns to menu
        free(visualArray);
        free(backgroundArray);
        free(script);

        visualArray = NULL;
        backgroundArray = NULL;
        script = NULL;

        currentState = MENU;
        isAnimating = false;
        actionIndex = 0;
        totalActions = 0;
        charCount = 0;
        inputText[0] = '\0';
      }
      //--------------------------Animation playback--------------------------
      if (isAnimating && actionIndex < totalActions) {
        // The sorting has been executed in the background, the total number of
        // actions has been recorded in the total actions variable.
        Action current = script[actionIndex];
        activeA = current.indexA;
        activeB = current.indexB;
        actionType = current.type;

        if (actionType == 1) {
          int temp = visualArray[activeA]; // does the swapping visually
          visualArray[activeA] = visualArray[activeB];
          visualArray[activeB] = temp;
        }

        actionIndex++;
      } else if (actionIndex >= totalActions) {
        isAnimating = false;
        activeA = -1;
        activeB = -1;
      }
    }

    //==================================================
    // 3.2 DRAWING PHASE
    //==================================================
    BeginDrawing();
    ClearBackground(DARKPURPLE);

    if (currentState == MENU) {
      //-------------------Draw UI and text-------------------------------
      DrawText("Enter Array Size:", textBox.x, textBox.y - 30, 20, RAYWHITE);

      DrawRectangleRec(textBox, LIGHTGRAY);
      DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width,
                         (int)textBox.height, DARKGRAY);
      DrawText(inputText, (int)textBox.x + 10, (int)textBox.y + 10, 20, MAROON);

      Color buttonColor1 =
          CheckCollisionPointRec(mousePoint, buttonBubble) ? BLUE : DARKBLUE;
      DrawRectangleRec(buttonBubble, buttonColor1);
      DrawText("Bubble Sort", (int)buttonBubble.x + 15,
               (int)buttonBubble.y + 10, 20, WHITE);

      Color buttonColor2 =
          CheckCollisionPointRec(mousePoint, buttonSelection) ? BLUE : DARKBLUE;
      DrawRectangleRec(buttonSelection, buttonColor2);
      DrawText("Selection Sort", (int)buttonSelection.x + 5,
               (int)buttonSelection.y + 10, 18, WHITE);
    } else if (currentState == SORTING) {
      //---------------------Draws columns------------------------------
      drawColumns(visualArray, size, screenWidth, screenHeight, activeA,
                  activeB, actionType);
      Color backButtonC =
          CheckCollisionPointRec(mousePoint, buttonBack) ? LIGHTGRAY : GRAY;
      DrawRectangleRec(buttonBack, backButtonC);
      DrawRectangleLines((int)buttonBack.x, (int)buttonBack.y,
                         (int)buttonBack.width, (int)buttonBack.height,
                         DARKGRAY);
      DrawText("Return", (int)buttonBack.x + 25, (int)buttonBack.y + 8, 18,
               RAYWHITE);
    }
    EndDrawing();
  }

  //======================================================
  // 4. CLEANUP
  //=====================================================
  free(visualArray);
  free(backgroundArray);
  free(script);
  CloseWindow();
  return 0;
}
