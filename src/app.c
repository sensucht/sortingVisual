#include "../include/app.h"
#include "../include/arrayManager.h"
#include "../include/graphics.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

void appInit(AppContext *app) {
  // Initializes variables to their default state.

  //----------Screen size constants and app state (MENU or
  // SORTING)--------------
  app->screenWidth = 1024;
  app->screenHeight = 768;
  app->currentState = MENU;

  //---------------------Array and animation state related
  // variables----------------
  app->size = 0;
  app->visualArray = NULL;
  app->backgroundArray = NULL;
  app->script = NULL;
  app->totalActions = 0;
  app->actionIndex = 0;
  app->activeA = -1;
  app->activeB = -1;
  app->actionType = -1;
  app->isAnimating = false;

  //-----------------Text input related variables----------------
  app->inputText[0] = '\0';
  app->charCount = 0;

  //------------------------UI Rectangles---------------------------------
  app->textBox = (Rectangle){app->screenWidth / 2 - 100,
                             app->screenHeight / 2 - 80, 200, 40};
  app->buttonBack = (Rectangle){20, 20, 100, 30};
  app->buttonBubble = (Rectangle){app->screenWidth / 2 - 150,
                                  app->screenHeight / 2 + 80, 140, 40};
  app->buttonSelection = (Rectangle){app->screenWidth / 2 + 10,
                                     app->screenHeight / 2 + 80, 140, 40};
  app->buttonInsertion = (Rectangle){app->screenWidth / 2 - 70,
                                     app->screenHeight / 2 + 130, 140, 40};
}

void appUpdate(AppContext *app) {
  Vector2 mousePoint = GetMousePosition();

  if (app->currentState == MENU) {
    // -----Text box input-------
    int key = GetCharPressed();
    while (key > 0) {
      // Only accepts numeric inputs (ASCII 48-57) and prevents array overflow
      if ((key >= 48) && (key <= 57) && (app->charCount < 3)) {
        app->inputText[app->charCount] = (char)key;
        app->inputText[app->charCount + 1] = '\0';
        app->charCount++;
      }
      key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && app->charCount > 0) {
      // Allows for deleting text
      app->charCount--;
      app->inputText[app->charCount] = '\0';
    }

    // -------Button clicks and array generation------------

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && app->charCount > 0 &&
        atoi(app->inputText) > 0) {
      app->size =
          atoi(app->inputText); // Transforms the user input (a string) into a
                                // integer, to allow the given size to be used
                                // in the defined functions

      int maxSize = 500;
      if (app->size >
          maxSize) { // Caps number of columns to 500, since the visualizer
                     // stops rendering them correctly after this point.
        app->size = maxSize;
      }

      if (CheckCollisionPointRec(mousePoint, app->buttonBubble)) {
        // If the mouse clicks the bubble sort button, executes bubble sort
        app->visualArray = arrayCreate(app->size);
        app->backgroundArray = arrayCreate(app->size);
        size_t scriptSize = (size_t)app->size * app->size * sizeof(Action);
        app->script = malloc(scriptSize);

        if (app->script == NULL) { // Checks if allocation succeeded
          fprintf(stderr, "Error: Memory allocation failed.\n");

          // Resets state of the variables
          free(app->visualArray);
          free(app->backgroundArray);
          app->visualArray = NULL;
          app->backgroundArray = NULL;
          app->charCount = 0;
          app->inputText[0] = '\0';

          return;
        }

        arrayGenerateData(app->visualArray, app->size, 50,
                          app->screenHeight - 100);
        arrayCopy(app->backgroundArray, app->visualArray, app->size);

        recordBubbleSort(app->backgroundArray, app->size, app->script,
                         &app->totalActions);
        app->isAnimating = true;
        app->currentState = SORTING;
      }

      if (CheckCollisionPointRec(mousePoint, app->buttonSelection)) {
        // If the mouse clicks the selection sort button, executes selection
        // sort
        app->visualArray = arrayCreate(app->size);
        app->backgroundArray = arrayCreate(app->size);
        size_t scriptSize = (size_t)app->size * app->size * sizeof(Action);
        app->script = malloc(scriptSize);

        if (app->script == NULL) { // Checks if allocation succeeded.
          fprintf(stderr, "Error: Memory allocation failed.\n");

          // Resets state of the variables
          free(app->visualArray);
          free(app->backgroundArray);
          app->visualArray = NULL;
          app->backgroundArray = NULL;
          app->charCount = 0;
          app->inputText[0] = '\0';

          return;
        }

        arrayGenerateData(app->visualArray, app->size, 50,
                          app->screenHeight - 100);
        arrayCopy(app->backgroundArray, app->visualArray, app->size);

        recordSelectionSort(app->backgroundArray, app->size, app->script,
                            &app->totalActions);
        app->isAnimating = true;
        app->currentState = SORTING;
      }

      if (CheckCollisionPointRec(mousePoint, app->buttonInsertion)) {
        // If the mouse clicks the Insertion sort button, executes Insertion
        // Sort.
        app->visualArray = arrayCreate(app->size);
        app->backgroundArray = arrayCreate(app->size);
        size_t scriptSize = (size_t)app->size * app->size * sizeof(Action);
        app->script = malloc(scriptSize);

        if (app->script == NULL) { //   Checks if allocation succeeded.
          fprintf(stderr, "Error: Memory allocation failed.\n");

          // Resets state of the variables
          free(app->visualArray);
          free(app->backgroundArray);
          app->visualArray = NULL;
          app->backgroundArray = NULL;
          app->charCount = 0;
          app->inputText[0] = '\0';

          return;
        }

        arrayGenerateData(app->visualArray, app->size, 50,
                          app->screenHeight - 100);
        arrayCopy(app->backgroundArray, app->visualArray, app->size);

        recordInsertionSort(app->backgroundArray, app->size, app->script,
                            &app->totalActions);
        app->isAnimating = true;
        app->currentState = SORTING;
      }
    }
    //----------------Return button--------------
  } else if (app->currentState == SORTING) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(mousePoint, app->buttonBack)) {
      // If the mouse clicks the return button, frees the dinamically
      // allocated variables and returns to menu
      free(app->visualArray);
      free(app->backgroundArray);
      free(app->script);

      app->visualArray = NULL;
      app->backgroundArray = NULL;
      app->script = NULL;

      app->currentState = MENU;
      app->isAnimating = false;
      app->actionIndex = 0;
      app->totalActions = 0;
      app->charCount = 0;
      app->inputText[0] = '\0';
    }
    //--------------------------Animation playback--------------------------
    if (app->isAnimating && app->actionIndex < app->totalActions) {
      // The sorting has been executed in the background, the total number of
      // actions has been recorded in the total actions variable.
      Action current = app->script[app->actionIndex];
      app->activeA = current.indexA;
      app->activeB = current.indexB;
      app->actionType = current.type;

      if (app->actionType == 1) {
        int temp = app->visualArray[app->activeA]; // does the swapping visually
        app->visualArray[app->activeA] = app->visualArray[app->activeB];
        app->visualArray[app->activeB] = temp;
      }

      app->actionIndex++;
    } else if (app->actionIndex >= app->totalActions) {
      app->isAnimating = false;
      app->activeA = -1;
      app->activeB = -1;
    }
  }
}

void appDraw(AppContext *app) {
  // Draws the buttons and columns

  Vector2 mousePoint = GetMousePosition();

  BeginDrawing();
  ClearBackground(DARKPURPLE);
  if (app->currentState == MENU) {
    //-------------------Draw UI and text-------------------------------
    DrawText("Enter Array Size:", app->textBox.x, app->textBox.y - 30, 20,
             RAYWHITE);

    DrawRectangleRec(app->textBox, LIGHTGRAY);
    DrawRectangleLines((int)app->textBox.x, (int)app->textBox.y,
                       (int)app->textBox.width, (int)app->textBox.height,
                       DARKGRAY);
    DrawText(app->inputText, (int)app->textBox.x + 10, (int)app->textBox.y + 10,
             20, MAROON);

    Color buttonColor1 =
        CheckCollisionPointRec(mousePoint, app->buttonBubble) ? BLUE : DARKBLUE;
    DrawRectangleRec(app->buttonBubble, buttonColor1);
    DrawText("Bubble Sort", (int)app->buttonBubble.x + 15,
             (int)app->buttonBubble.y + 10, 20, WHITE);

    Color buttonColor2 =
        CheckCollisionPointRec(mousePoint, app->buttonSelection) ? BLUE
                                                                 : DARKBLUE;
    DrawRectangleRec(app->buttonSelection, buttonColor2);
    DrawText("Selection Sort", (int)app->buttonSelection.x + 5,
             (int)app->buttonSelection.y + 10, 18, WHITE);

    Color buttonColor3 =
        CheckCollisionPointRec(mousePoint, app->buttonInsertion) ? BLUE
                                                                 : DARKBLUE;
    DrawRectangleRec(app->buttonInsertion, buttonColor3);
    DrawText("Insertion Sort", (int)app->buttonInsertion.x + 5,
             (int)app->buttonInsertion.y + 10, 18, WHITE);

  } else if (app->currentState == SORTING) {
    //---------------------Draws columns------------------------------
    drawColumns(app->visualArray, app->size, app->screenWidth,
                app->screenHeight, app->activeA, app->activeB, app->actionType);
    Color backButtonC =
        CheckCollisionPointRec(mousePoint, app->buttonBack) ? LIGHTGRAY : GRAY;
    DrawRectangleRec(app->buttonBack, backButtonC);
    DrawRectangleLines((int)app->buttonBack.x, (int)app->buttonBack.y,
                       (int)app->buttonBack.width, (int)app->buttonBack.height,
                       DARKGRAY);
    DrawText("Return", (int)app->buttonBack.x + 25, (int)app->buttonBack.y + 8,
             18, RAYWHITE);
  }
  EndDrawing();
}

void appCleanup(AppContext *app) {
  // Frees the dinamically allocated memory of the variables used in the
  // execution of the program
  free(app->visualArray);
  free(app->backgroundArray);
  free(app->script);
}
