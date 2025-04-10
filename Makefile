# noashalom5@gmail.com

CC = clang++
CFLAGS = -Wall -Wextra -std=c++11
OFILES = main.o graph.o algorithms.o

Main: main run

main: $(OFILES)
	$(CC) $(CFLAGS) -o main $(OFILES)

main.o: main.cpp graph.hpp algorithms.hpp
	$(CC) $(CFLAGS) -c main.cpp

graph.o: graph.cpp graph.hpp
	$(CC) $(CFLAGS) -c graph.cpp

algorithms.o: algorithms.cpp algorithms.hpp graph.hpp
	$(CC) $(CFLAGS) -c algorithms.cpp

run: main
	./main

test_exe: test.o graph.o algorithms.o
	$(CC) $(CFLAGS) -o test test.o graph.o algorithms.o

test: test_exe
	./test

test.o: test.cpp graph.hpp algorithms.hpp doctest.hpp
	$(CC) $(CFLAGS) -c test.cpp

valgrind: main test_exe
	valgrind --leak-check=full --show-leak-kinds=all ./main
	valgrind --leak-check=full --show-leak-kinds=all ./test

clean:
	rm -f *.o main test

.PHONY: Main run clean valgrind
