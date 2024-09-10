TARGET = ref

OBJECTS = main.o make_points.o gauss.o

CC = g++


CFLAGS = -std=c++11 -c -Wall -O3
# CFLAGS = -c -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align \
-Wformat-security -Wmissing-format-attribute -Wformat=1 \
-Wno-long-long -Wcast-align -Winline -Werror -pedantic -pedantic-errors \
-Wunused -Wuninitialized \
--param inline-unit-growth=1000000 --param max-inline-insns-single=10000000 \
--param large-function-growth=10000000 -O3 -fPIC


# красный шрифт
RED_FONT = \033[31m
STANDART_FORMAT = \033[0m

all: $(TARGET)
	@echo "$(STANDART_FORMAT)run with formula: $(RED_FONT)./ref"
	

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
	
	
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
	
	
make_points.o: make_points.cpp
	$(CC) $(CFLAGS) make_points.cpp
	
	
gauss.o: gauss.cpp
	$(CC) $(CFLAGS) gauss.cpp
	
	
.PHONY: clean
clean:
	-rm -f $(OBJECTS) $(TARGET)