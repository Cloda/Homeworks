TARGETS = main_fourier main_sweep

CC = gcc
CFLAGS = -Wall -Wextra -O2

# Исходные файлы и заголовочные файлы для каждой программы
FOURIER_SRCS = main_fourier.c FourierMethod.c
SWEEP_SRCS = main_sweep.c SweepMethod.c FourierMethod.c

FOURIER_HEADERS = FourierMethod.h
SWEEP_HEADERS = SweepMethod.h FourierMethod.h

FOURIER_OBJS = $(FOURIER_SRCS:.c=.o)
SWEEP_OBJS = $(SWEEP_SRCS:.c=.o)

all: $(TARGETS)

main_fourier: $(FOURIER_OBJS)
	$(CC) $(CFLAGS) -o $@ $(FOURIER_OBJS) -lm

main_sweep: $(SWEEP_OBJS)
	$(CC) $(CFLAGS) -o $@ $(SWEEP_OBJS) -lm

%.o: %.c $(FOURIER_HEADERS) $(SWEEP_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGETS)
	rm -f *.png
	rm -f *.txt
	
runFourier: main_fourier
	@echo "Running main_fourier..."
	@./main_fourier

runSweep: main_sweep
	@echo "Running main_sweep..."
	@./main_sweep

.PHONY: all clean runFourier runSweep
