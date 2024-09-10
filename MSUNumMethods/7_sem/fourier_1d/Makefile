TARGET_MAIN = ref
TARGET_CONV = conv

OBJECTS_MAIN = main.o make_points.o
OBJECTS_CONV = converge.o make_points.o

CC = g++

CFLAGS = -c
#CFLAGS = -c -g
# CFLAGS = -std=c++11 -c -Wall -O3
# CFLAGS = -c -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align \
-Wformat-security -Wmissing-format-attribute -Wformat=1 \
-Wno-long-long -Wcast-align -Winline -Werror -pedantic -pedantic-errors \
-Wunused -Wuninitialized \
--param inline-unit-growth=1000000 --param max-inline-insns-single=10000000 \
--param large-function-growth=10000000 -O3 -fPIC


# красный шрифт
RED_FONT = \033[31m
STANDART_FORMAT = \033[0m


all: $(OBJECTS_MAIN)
	$(CC) $(OBJECTS_MAIN) -o $(TARGET_MAIN)
	@echo "$(STANDART_FORMAT)run with formula: $(RED_FONT)./ref"
	
conv: $(OBJECTS_CONV)
	$(CC) $(OBJECTS_CONV) -o $(TARGET_CONV)
	@echo "$(STANDART_FORMAT)run with formula: $(RED_FONT)./conv"



main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

make_points.o: make_points.cpp
	$(CC) $(CFLAGS) make_points.cpp
	
converge.o: converge.cpp
	$(CC) $(CFLAGS) converge.cpp

	
.PHONY: clean
clean:
	-rm -f $(OBJECTS_MAIN) $(TARGET_MAIN)
	-rm -f $(OBJECTS_CONV) $(TARGET_CONV)
