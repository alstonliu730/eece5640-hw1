/**/
#ifndef SORT_H
#define SORT_H

#include <stdint.h>
#include "thpool.h"

typedef struct {
    int* array;
    int left;
    int right;
} merge_args;

void merge(int arr[], int l, int m, int r);
void merge_sort(int arr[], int l, int r);
void merge_sort_wrapper(void* arg);
void parallel_merge_sort(threadpool* pool, int arr[], int n);

#endif /*SORT_H*/
