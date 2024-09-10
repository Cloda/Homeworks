TARGET_MAIN = ref

OBJECTS_MAIN = main.o integr_methods.o

CC = g++

CFLAGS = -c
# CFLAGS = -c -g
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

integr_methods.o: integr_methods.cpp
	$(CC) $(CFLAGS) integr_methods.cpp
	

	
.PHONY: clean
clean:
	-rm -f $(OBJECTS_MAIN) $(TARGET_MAIN) out_trig.txt out_res.txt gnu.txt *.png
