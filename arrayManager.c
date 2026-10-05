#include "arrayManager.h"
#include <stdlib.h>

int *arrayCreate(
    int size) { // Creates a new array, of a size given by user Input
  int total = size * sizeof(int);
  int *newArray = (int *)malloc(total);

  return newArray;
}

void arrayGenerateData(int *arr, int size, int minVal,
                       int maxVal) { // Fills the previously created array with
                                     // pseudo-random numbers
  int i;

  for (i = 0; i < size; i++) {
    arr[i] =
        minVal + rand() % (maxVal - minVal +
                           1); // User defined range for pseudo-random numbers.
  }
}

void arrayFree(int *arr) { free(arr); }
