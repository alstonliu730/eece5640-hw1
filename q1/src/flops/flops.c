/*
File: flops.c
Author: Alston Liu
Date: 01-24-25
Description: A simple benchmark that does floating point operations using trig functions.
*/
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// initialize clock
double CLOCK() {
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  return (t.tv_sec * 1000) + (t.tv_nsec*1e-6);
}

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Please enter the number of loops.\n");
    return 1;
  }
  long loops = 0;
  if (argv[1] != NULL) {
    loops = atoi(argv[1]);
  } else {
    printf("Error occurred when reading input.\n");
    return 1;
  }

  double start, finish, total;

  // start the clock
  start = CLOCK();

  double num;
  // Floating point operation loop
  for(long i = 0; i < loops; i++) {
    num += sin(i) * cos(i);
  }

  // finish the clock
  finish = CLOCK();
  total = finish - start; //ms?

  // print out result
  double flops = (loops / (total / 1000));
  printf("Result: %lf\n", num);
  printf("Rate: %.2f FLOPS\n", flops);
  printf("Time: %4.2f ms\n", total);
  return 0;
}
