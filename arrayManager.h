#ifndef ARRAYMANAGER_H
#define ARRAYMANAGER_H

int *arrayCreate(int size);
void arrayGenerateData(int *arr, int size, int minVal, int maxVal);
void arrayCopy(int *copy, int *src, int size);
void arrayFree(int *arr);

#endif // !ARRAYMANAGER_H
