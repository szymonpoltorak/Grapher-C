FLAGS = -Wall -pedantic -Wextra
CCC = cc -c
CCO = cc -o
MV = -mv *.o bin/
MD = -mkdir bin
DEL = -rm bin/*.o grapher

all: grapher

.PHONY: clean all

grapher: main.o alloc.o readGraph.o genGraph.o utils.o
	$(CCO) $@ $^
	$(MD)
	$(MV) 

main.o: src/main.c src/alloc.h src/readGraph.h
	$(CCC) $< $(FLAGS)

alloc.o: src/alloc.c src/alloc.h
	$(CCC) $< $(FLAGS)

readGraph.o: src/readGraph.c src/readGraph.h
	$(CCC) $< $(FLAGS)

genGraph.o: src/genGraph.c src/genGraph.h
	$(CCC) $< $(FLAGS)

utils.o: src/utils.c src/utils.h
	$(CCC) $< $(FLAGS)

clean:
	$(DEL)