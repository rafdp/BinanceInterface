

.DEFAULT_GOAL := main

CC = g++
CFLAGS = -Wall -std=c++11 -I.
main: main.o QueryRequest.o BinanceInterfacer.o
	$(CC) $(CFLAGS) -o $@ $^ -lcurl

main.o: main.cpp
	$(CC) $(CFLAGS) -c $^

QueryRequest.o: QueryRequest.cpp
	$(CC) $(CFLAGS) -c $^

BinanceInterfacer.o: BinanceInterfacer.cpp
	$(CC) $(CFLAGS) -c $^

c:
	rm -rf *.o main
