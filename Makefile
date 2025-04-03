CC = clang++
CFLAGS = -Wall -Wextra -std=c++11
OFILES = main.o graph.o algorithms.o

all: main run

main: $(OFILES)
	$(CC) $(CFLAGS) -o main $(OFILES)

main.o: main.cpp graph.hpp algorithms.hpp
	$(CC) $(CFLAGS) -c main.cpp

graph.o: graph.cpp graph.hpp
	$(CC) $(CFLAGS) -c graph.cpp

algorithms.o: algorithms.cpp algorithms.hpp
	$(CC) $(CFLAGS) -c algorithms.cpp

run: main
	./main

clean:
	rm -f *.o main

.PHONY: all run clean 
