CCX=g++
CXXFLAGS=-g

OBJS =  m.o producto.o catalogo.o

all: ${OBJS}
	$(CCX) $(CXXFLAGS) -o catalogo ${OBJS}
	rm  *.o
