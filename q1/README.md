# Question 1
Created by vashpan
Copied from git@github.com:vashpan/isbench.git

This is his description of his benchmark files:
A very simple (and naive) integer benchmark aimed at maximum portability across multiple OSes and independence on any system-specific code.

You may ask: **why?**

I was wondering - how fast current computers are? How many 386s would be required to make a job that our Core i7 can do in a second? Properly measuring performance is not a simple task, a lot of things decides about that. CPU is one, but we also have a compiler that can produce better optimized code.

The idea is to create a very simple benchmark that will be able to run on multiple, both modern and retro platforms. It would also allow to compare raw performance of code optimizations performed by various compilers on the same platforms. 

It benchmarks only CPU single-threaded integer performance. Floating point tests doesn't make much sense since older CPUs often didn't even had an FPU, or it was very slow compared to integer unit. 

## Build
There are three targets in the Makefile
- isbench
- isbench-dbg
- clean

## Run
To run, just use ./isbench executable file


