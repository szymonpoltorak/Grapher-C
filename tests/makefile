RIGHTS = chmod +x test.sh
RTEST = cd .. && ./tests/test.sh
GRAPH = cd .. && make -s grapher
DEL = cd .. && make clean

all: test

test: grapher
	$(RIGHTS)
	$(RTEST)
	$(DEL)

grapher:
	$(GRAPH)