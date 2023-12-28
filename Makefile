CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2 -march=native

.PHONY: clean

clean_test_passenger:
	rm -f test_passenger test_passenger.o
	
clean_test_train:
	rm -f test_train test_train.o
	
clean_test_station:
	rm -f test_station test_station.o
	
clean_sim:
	rm -f sim sim.o

test_passenger: passenger.h passenger.c test_passenger.c
	$(CC) $(CFLAGS) $^ -o $@

test_train: train.h train.c test_train.c
	$(CC) $(CFLAGS) $^ -o $@

test_station: passenger.h passenger.c station.h station.c test_station.c
	$(CC) $(CFLAGS) $^ -o $@
	
sim: passenger.h passenger.c train.h train.c station.h station.c ttc.h ttc.c sim.c
	$(CC) $(CFLAGS) $^ -o $@