#OPTIONS= -DDEBUG_BENCHMARK
SERVER = 10.133.141.167 
OPTIONS = -g

compile:
		g++ $(OPTIONS) $(shell pkg-config --cflags hiredis) benchmark.cpp -o benchmark   -L$(PWD) $(shell pkg-config --libs hiredis) 

run:
		taskset 0x01 ./benchmark $(ITR) $(SERVER)
