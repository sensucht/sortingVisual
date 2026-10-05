#ifndef SORTING_H
#define SORTING_H

typedef struct {
  int type;   // 0 when COMPARE, 1 when SWAP
  int indexA; // First column involved
  int indexB; // Second column involved
} Action;

// O(n^2) algorithms
void recordBubbleSort(int *arr, int size, Action *script, int *actionCount);
void recordSelectionSort(int *arr, int size, Action *script, int *actionCount);
void recordInsertionSort(int *arr, int size, Action *script, int *actionCount);

// TBD: O (n log n) algorithms

#endif // !SORTING_H
