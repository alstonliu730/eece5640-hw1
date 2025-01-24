SRC = ./src
ISBENCH = -I "./src/isbench"
ISBENCH_SRC = $(SRC)/isbench/*.c $(SRC)/isbench/platform/unix/*.c
PRIME_SRC = $(SRC)/prime/*.c
PRIME = -I "./src/prime"
FLOPS_SRC = $(SRC)/flops/*.c
FLOPS = -I "./src/flops"
CFLAGS = -std=c89

isbench: $(ISBENCH_SRC)
	$(CC) -o $@ $(ISBENCH_SRC) -O2 $(CFLAGS) $(ISBENCH)

isbench-dbg: $(ISBENCH_SRC)
	$(CC) -o $@ $(ISBENCH_SRC) -g $(CFLAGS) $(ISBENCH)

prime: $(PRIME_SRC)
	$(CC) -lm -o $@ $(PRIME_SRC) -O0 $(PRIME)

prime-dbg: $(PRIME_SRC)
	$(CC) -lm -o $@ $(PRIME_SRC) -g $(PRIME)

flops: $(FLOPS_SRC)
	$(CC) -lm -o $@ $(FLOPS_SRC) -O0 $(FLOPS)

flops-dbg: $(FLOPS_SRC)
	$(CC) -lm -o $@ $(FLOPS_SRC) -g $(FLOPS)

clean:
	rm -rf *.o isbench isbench-dbg isbench-dbg.dSYM prime flops
