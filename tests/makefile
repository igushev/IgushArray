CC=g++
INC=-I./ -I../src
CFLAGS=-c -Wall
BIN=IgushArray

all: IgushArray

IgushArray: test_pack.o stab_test_pack.o perf_test_pack.o fixed_deque_stab.o igush_array_stab.o igush_array_perf.o main.o
	$(CC) $(INC) -Wall test_pack.o stab_test_pack.o perf_test_pack.o fixed_deque_stab.o igush_array_stab.o igush_array_perf.o main.o -o $(BIN)

test_pack.o: test_pack.h test_pack.C
	$(CC) $(INC) $(CFLAGS) test_pack.C

stab_test_pack.o: stab_test_pack.h stab_test_pack.C
	$(CC) $(INC) $(CFLAGS) stab_test_pack.C

perf_test_pack.o: perf_test_pack.h perf_test_pack.C
	$(CC) $(INC) $(CFLAGS) perf_test_pack.C

fixed_deque_stab.o: fixed_deque_stab.h fixed_deque_stab.C
	$(CC) $(INC) $(CFLAGS) fixed_deque_stab.C

igush_array_stab.o: igush_array_stab.h igush_array_stab.C
	$(CC) $(INC) $(CFLAGS) igush_array_stab.C

igush_array_perf.o: igush_array_perf.h igush_array_perf.C
	$(CC) $(INC) $(CFLAGS) igush_array_perf.C

main.o: main.C
	$(CC) $(INC) $(CFLAGS) main.C

clean:
	rm -rf *.o $(BIN)
