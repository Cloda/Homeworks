TARGET = ref

OBJECTS = main.o classMatrix.o algorithm_.o

CC = g++

CFLAGS = -std=c++14 -c -Wall -Weffc++ -Wextra -O3

# красный шрифт
RED_FONT = \033[31m
STANDART_FORMAT = \033[0m

all: $(TARGET)
	@echo "$(STANDART_FORMAT)run with formula: $(RED_FONT)./ref <n> <p> <r> <s>"
	@echo "$(STANDART_FORMAT)run with file:    $(RED_FONT)./ref <n> <p> <r> 0 <filename> $(STANDART_FORMAT)"
	

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -lm -lpthread -o $(TARGET)
	
	
main.o: main.cpp classMatrix.cpp algorithm_.cpp
	$(CC) $(CFLAGS) main.cpp
	
	
classMatrix.o: classMatrix.cpp
	$(CC) $(CFLAGS) classMatrix.cpp
	
	
algorithm_.o: algorithm_.cpp
	$(CC) $(CFLAGS) algorithm_.cpp
	
	
.PHONY: clean
clean:
	-rm -f $(OBJECTS) $(TARGET)