CC = gcc
SRC = ./src/*.c
SORT = -I "./src/"
NEW_SORT = ./src/new-sort.c ./src/thpool.*

sort: $(SRC)
	$(CC) -lpthread -o $@ $(SRC) -O0 $(SORT)

new-sort: $(NEW_SORT)
	$(CC) -lpthread -o $@ $(NEW_SORT)

sort-dbg: $(SRC)
	$(CC) -lpthread -o $@ $(SRC) -g $(SORT) 

clean:
	rm -rf sort sort-dbg
