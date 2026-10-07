#include "arrayManager.h"
#include <stdlib.h>

int *arrayCreate(int size) { // Creates a new array, of a size given by user
                             // Input, by dinamically allocating memory
  int total = size * sizeof(int);
  int *newArray = (int *)malloc(total);

  return newArray;
}

void arrayGenerateData(int *arr, int size, int minVal,
                       int maxVal) { // Fills the previously created array with
                                     // pseudo-random numbers through a for loop
  int i;

  for (i = 0; i < size; i++) {
    arr[i] =
        minVal + rand() % (maxVal - minVal +
                           1); // User defined range for pseudo-random numbers.
  }
}

void arrayCopy(int *dest, int *src, int size) {
  int i;
  // Copies an source array to a destination array, which will be used
  // to draw the animations later.
  for (i = 0; i < size; i++) {
    dest[i] = src[i];
  }
}
