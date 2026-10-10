#include "arrayManager.h"
#include <stdio.h>
#include <stdlib.h>

int *arrayCreate(int size) { // Creates a new array, of a size given by user
                             // Input, by dinamically allocating memory
  if (size <= 0) {           // Validates user input
    fprintf(stderr, "Error: Array size must be greater than 0\n");
    return NULL;
  }

  size_t total = (size_t)size * sizeof(int);
  int *newArray = malloc(total);

  if (newArray == NULL) { // Checks if allocation actually succeeded
    fprintf(stderr, "Error: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  return newArray;
}

void arrayGenerateData(int *arr, int size, int minVal,
                       int maxVal) { // Fills the previously created array with
                                     // pseudo-random numbers through a for loop
  if (arr == NULL)
    return; // prevents segfault

  int i;

  if (minVal > maxVal) { // Validates user input to prevent modulo by zero
    int temp = minVal;
    minVal = maxVal;
    maxVal = temp;
  }

  for (i = 0; i < size; i++) {
    arr[i] =
        minVal + rand() % (maxVal - minVal +
                           1); // User defined range for pseudo-random numbers.
  }
}

void arrayCopy(int *dest, int *src, int size) {
  if (dest == NULL || src == NULL)
    return; // prevents segfault

  int i;
  // Copies an source array to a destination array, which will be used
  // to draw the animations later.
  for (i = 0; i < size; i++) {
    dest[i] = src[i];
  }
}
