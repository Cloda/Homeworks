TARGET_ONE= one
TARGET_TWO = two
TARGET_THREE = three


OBJECTS_ONE = task_1.o _lib.o
OBJECTS_TWO = task_2.o _lib.o
OBJECTS_THREE = task_3.o _lib.o


CC = g++

# CFLAGS = -c
CFLAGS = -c -g
#CFLAGS = -std=c++11 -c -Wall -O3
# CFLAGS = -c -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align \
-Wformat-security -Wmissing-format-attribute -Wformat=1 \
-Wno-long-long -Wcast-align -Winline -Werror -pedantic -pedantic-errors \
-Wunused -Wuninitialized \
--param inline-unit-growth=1000000 --param max-inline-insns-single=10000000 \
--param large-function-growth=10000000 -O3 -fPIC


# красный шрифт
RED_FONT = \033[31m
STANDART_FORMAT = \033[0m


one: $(OBJECTS_ONE)
	$(CC) $(OBJECTS_ONE) -o $(TARGET_ONE)
	@echo "$(STANDART_FORMAT)run with formula: $(RED_FONT)./one"

two: $(OBJECTS_TWO)
	$(CC) $(OBJECTS_TWO) -o $(TARGET_TWO)
	@echo "$(STANDART_FORMAT)run with formula: $(RED_FONT)./two"

three: $(OBJECTS_THREE)
	$(CC) $(OBJECTS_THREE) -o $(TARGET_THREE)
	@echo "$(STANDART_FORMAT)run with formula: $(RED_FONT)./three"
	

task_1.o: task_1.cpp
	$(CC) $(CFLAGS) task_1.cpp
	
task_2.o: task_2.cpp
	$(CC) $(CFLAGS) task_2.cpp

task_3.o: task_3.cpp
	$(CC) $(CFLAGS) task_3.cpp

_lib.o: _lib.cpp
	$(CC) $(CFLAGS) _lib.cpp
	

.PHONY: clean
clean:
	-rm -f $(OBJECTS_ONE) $(TARGET_ONE) $(OBJECTS_TWO) $(TARGET_TWO) $(OBJECTS_THREE) $(TARGET_THREE)  out.txt gnu.txt *.png



