/*
File: prime.h
Author: Alston Liu
Description: Header file for determining prime numbers to benchmark a CPU.
*/
#ifndef PRIME_H
#define PRIME_H
#include <stdint.h>

uint8_t isPrime(uint32_t n); //determines if the given int(32-bit unsigned) is a prime
uint32_t getPrimeNums(uint32_t n, uint32_t* result); // returns an arbitrary array of prime numbers

#endif /* PRIME_H */

