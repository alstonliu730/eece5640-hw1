INCLUDES = -I "./src"
SRC = ./src/*.c	./src/platform/unix/*.c
PRIME = ./src/prime/*.c
PRIME_INC = -I "./src/prime"
CFLAGS = -std=c89

isbench: $(SRC)
	$(CC) -o $@ $(SRC) -O2 $(CFLAGS) $(INCLUDES)

isbench-dbg: $(SRC)
	$(CC) -o $@ $(SRC) -g $(CFLAGS) $(INCLUDES)

prime: $(PRIME)
	$(CC) -o $@ $(PRIME) -O0 $(PRIME) -lm

clean:
	rm -rf *.o isbench isbench-dbg isbench-dbg.dSYM	
