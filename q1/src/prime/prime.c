/*
File: prime.c
Author: Alston Liu
Date: 01-23-25
Description: Determines all the prime number and prints it out. It also benchmarks the time it takes to do this.
*/
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "prime.h"

// initialize clock
double CLOCK() {
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  return (t.tv_sec * 1000) + (t.tv_nsec*1e-6);
}

/**
 * Determines if the given number is a prime number
 * 
 */
uint8_t isPrime(uint32_t n) {
  uint32_t i, temp;
  double squared = sqrt(n);
  for(i = 2; i <= ((uint32_t) squared); i++) {
    if(n % i == 0) { return 0; }
  }
  return 1;
}

/**
 * 
 */
uint32_t getPrimeNums(uint32_t n, uint32_t* result) {
  uint32_t len = 0;
  // iterate through integers from 1 to the given num
  for(uint32_t i = 1; i <= n; i++) {
    if (isPrime(i)) {
      *(result + len) = i;
      len++;
    }
  }

  return len;
}

// main function
int main(int argc, char **argv) {
  if (argc < 2) {
    printf("No input! Please enter the number of numbers to test to.\n");
    return 1;
  }

  uint32_t num = (uint32_t) atoi(argv[1]);
  // check if input is a valid number
  if (num <= 0) {
    printf("Invalid input!\n");
    return 1;
  }

  // check if interactive mode is toggled
  uint8_t interactive = 0;
  if (argv[2]) {
    printf("interactive mode\n");
    interactive = (strcmp(argv[2], "-i") == 0);
  }

  // create a dynamically allocated array w/ length of half of the given number
  uint32_t* result = (uint32_t*) calloc(num / 2, sizeof(uint32_t));

  // start the clock
  double start, finish, total;
  start = CLOCK();

  // benchmark prime numbers
  uint32_t len = getPrimeNums(num, result);

  // end the benchmark clock
  finish = CLOCK();
  total = finish - start;


  // print result
  if (interactive) {
    for (uint32_t i = 0; i < len; i++) {
      if(i % 10 == 0) {
        printf("\n");
      }
      printf("%d ", result[i]);
    }
    printf("\n");
  }
  // print number of prime numbers found
  printf("Found %d prime numbers\n", len);

  // print benchmark result
  printf("Time to find prime numbers between 1 and %d: %4.2f ms\n", num, total);

  // exiting 
  free(result);
  return 0;
}
