/*
 * This header handles the creation, copying
 * and pseudo-random data generation, taking user input
 * for the size variable and dinamically allocating data to
 * the pseudo-random array of said size.
 */

#ifndef ARRAYMANAGER_H
#define ARRAYMANAGER_H

int *arrayCreate(int size);
void arrayGenerateData(int *arr, int size, int minVal, int maxVal);
void arrayCopy(int *copy, int *src, int size);

#endif // !ARRAYMANAGER_H
