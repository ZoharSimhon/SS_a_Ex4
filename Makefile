all: main
main: edges.c graph.c nodes.c main.c graph.h
	gcc -Wall -g -o graph edges.c graph.c nodes.c main.c


clean:
	rm -f *.o graph