#include "sorting.h"
#include <stdbool.h>

void recordBubbleSort(int *arr, int size, Action *script, int *actionCount) {
  bool swapped;
  int i, j;
  int temp;

  for (i = 0; i < size - 1; i++) {
    swapped = false;

    for (j = 0; j < size - i; j++) {

      script[*actionCount].type = 0; // COMPARE
      script[*actionCount].indexA = j;
      script[*actionCount].indexB = j + 1;
      (*actionCount)++;

      if (arr[j] > arr[j + 1]) {
        script[*actionCount].type = 1; // SWAP
        script[*actionCount].indexA = j;
        script[*actionCount].indexB = j + 1;
        (*actionCount)++;

        // Actually does the swapping indicated by .type earlier

        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;

        swapped = true;
      }
    }

    // We assume that, if a whole round returned no swapping, our array is fully
    // sorted
    if (!swapped) {
      break;
    }
  }
}

void recordSelectionSort(int *arr, int size, Action *script, int *actionCount) {
  int i, j;
  int temp;
  int smallest;

  for (i = 0; i < size - 1; i++) {
    smallest = i;

    for (j = 0; j < size; j++) {
      script[*actionCount].type = 0; // COMPARE
      script[*actionCount].indexA = smallest;
      script[*actionCount].indexB = j;
      (*actionCount)++;

      if (arr[j] < arr[smallest]) {
        smallest = j;
      }
    }

    if (smallest != i) {
      script[*actionCount].type = 1; // SWAP
      script[*actionCount].indexA = i;
      script[*actionCount].indexB = smallest;
      (*actionCount)++;

      // Actually does the swapping
      temp = arr[i];
      arr[i] = arr[smallest];
      arr[smallest] = temp;
    }
  }
}
