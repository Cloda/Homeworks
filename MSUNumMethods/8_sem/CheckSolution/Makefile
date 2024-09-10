TARGET_MAIN = ref

OBJECTS_MAIN = main.o

CC = g++

CFLAGS = -c
#CFLAGS = -c -g
# CFLAGS = -std=c++11 -c -Wall -O3

# красный шрифт
RED_FONT = \033[31m
STANDART_FORMAT = \033[0m


all: $(OBJECTS_MAIN)
	$(CC) $(OBJECTS_MAIN) -o $(TARGET_MAIN)
	@echo "$(STANDART_FORMAT)run with formula: $(RED_FONT)./ref"
	
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp


	
.PHONY: clean
clean:
	-rm -f $(OBJECTS_MAIN) $(TARGET_MAIN)
