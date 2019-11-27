CFLAGS=-c -std=c++1z -O3 # Compilation flags
LFLAGS=-fsanitize=address -g -lstdc++fs -lpthread # Linker flags
CC=g++ # Compiler

HEADERS=kmp_search.h # Headers

all: psearch

psearch: main.o kmp_search.o
	$(CC) main.o kmp_search.o $(LFLAGS) -o psearch

main.o: main.cpp $(HEADERS)
	$(CC) $(CFLAGS) main.cpp

kmp_search.o: kmp_search.cpp $(HEADERS)
	$(CC) $(CFLAGS) kmp_search.cpp

clean:
	rm -rf *.o psearch
