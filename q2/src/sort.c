#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sort.h"
#include "thpool.h"

#define MAX 1000000
#define MAX_THREADS 4

double CLOCK() {
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int leftArr[n1], rightArr[n2];

    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArr[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArr[], if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

/* Function to perform merge sort on a subarray */
void merge_sort(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

/* Wrapper function for merge sort to be used with the thread pool */
void merge_sort_wrapper(void* arg) {
    merge_args* params = (merge_args*) arg;
    int* arr = params->array;
    int l = params ->left;
    int r = params->right;

    merge_sort(arr, l, r);

    free(arg); // Free the allocated memory for params
}

/* Function to perform parallel merge sort using the thread pool */
void parallel_merge_sort(threadpool* pool, int* arr, int n) {
    if (n <= 1) return;

    int m = n / 2;

    // Prepare parameters for the first half
    merge_args* params1 = (merge_args*) malloc(sizeof(merge_args));
    params1->array = arr;
    params1->left = 0;
    params1->right = m - 1;

    // Prepare parameters for the second half
    merge_args* params2 = (merge_args*) malloc(sizeof(merge_args));
    params2->array = arr;
    params2->left = m;
    params2->right = n - 1;

    // Add the two halves to the thread pool
    thpool_add_work(*pool, merge_sort_wrapper, (void *) params1);
    thpool_add_work(*pool, merge_sort_wrapper, (void *) params2);

    // Wait for all threads to finish
    thpool_wait(*pool);

    // Merge the two sorted halves
    merge(arr, 0, m - 1, n - 1);
}

int main(int argc, char** argv) {
    int sample_size = MAX, num_threads = MAX_THREADS;
    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0) {
            printf("Syntax: ./new-sort [# of Threads] [Sample-Size]\n");
            return 0;
        } else if (argc == 3) {
            int temp = atoi(argv[1]);
            if (temp > 128) {
                printf("Invalid Num of Threads: %d!\n", temp); 
                return 1;
            } else { 
                num_threads = temp; 
            }
            sample_size = atoi(argv[2]);
            if (sample_size < 0 || (sample_size * sizeof(int)) > SIZE_MAX) {
                sample_size = MAX;
            }
        } else {
            printf("Invalid Input!\n");
            return 2;
        }
    }

    int* arr = (int *) calloc(sample_size, sizeof(int));
    for(int i = 0; i < sample_size; i++) {
        *(arr + i) = (rand() % 10000);
    }

    // Initialize the thread pool with 2 threads
    threadpool pool = thpool_init(num_threads);
    if (pool == NULL) {
        fprintf(stderr, "Failed to initialize thread pool\n");
        return 1;
    }

    // benchmark
    double t1, t2, total;
    t1 = CLOCK();

    // Perform parallel merge sort
    parallel_merge_sort(&pool, arr, sample_size);

    t2 = CLOCK();
    // Destroy the thread pool
    thpool_destroy(pool);
    total = t2 - t1;
    // Print the sorted array
    // printf("Sorted array: \n");
    // for (int i = 0; i < sample_size; i++)
    //     printf("%d ", arr[i]);
    // printf("\n");
    printf("Latency: %0.4f ms\n", total);
    free(arr);
    return 0;
}