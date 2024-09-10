TARGETS = main

CC = g++
CFLAGS = -Wall -Wextra -O2

# Исходные файлы и заголовочные файлы для каждой программы
MAIN_SRCS = main.cpp func_and_algorithm.cpp

MAIN_HEADERS = func_and_algorithm.hpp

MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)

all: $(TARGETS)

main: $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJS) -lm

%.o: %.cpp $(MAIN_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGETS)
	rm -f *.png
	rm -f *.txt


run: main
	@echo "Running main..."
	@./main

.PHONY: all clean run
