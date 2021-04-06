CC = gcc
CFLAGS = -O0 -static -g -I `pwd`/../GEM5Simulation/gem5/include/ `pwd`/../GEM5Simulation/gem5/util/m5/m5op_x86.S

all: step2 step2-PIM prepStep2 step3

step2: step2.c
	$(CC) $(CFLAGS) $^ -o $@

step2-PIM: step2-PIM.c
	$(CC) $(CFLAGS) $^ -o $@

prepStep2: prepStep2.c
	$(CC) $(CFLAGS) $^ -o $@

step3: step3.c
	$(CC) $(CFLAGS) -fopenmp $^ -o $@
