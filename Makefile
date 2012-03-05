# a comment
CC=g++

all:	run_genetic benchmarkWinningStrategy

run_genetic:	run_genetic.o context.o strategy.o robby.o strategyStore.o constants.h
	g++ run_genetic.cpp context.cpp strategy.cpp robby.cpp strategyStore.cpp -o run_genetic.exe

benchmarkWinningStrategy:	context.o strategy.o robby.o constants.h
	g++ -I/usr/include/ncurses benchmarkWinningStrategy.cpp context.cpp strategy.cpp robby.cpp -lncurses -o benchMark.exe 