CCX=g++
CXXFLAGS=-g

OBJS =  main.o producto.o

all: ${OBJS}
	$(CCX) $(CXXFLAGS) -o hash ${OBJS}
	rm  *.o
