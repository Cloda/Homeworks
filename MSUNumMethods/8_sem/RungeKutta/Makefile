TARGET = main

CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRCS = main.c func.c scheme.c

HEADERS = func.h scheme.h
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.png
	rm -f *.txt
	
run: $(TARGET)
	./$(TARGET)

plot: $(TARGET)
	./$(TARGET)
