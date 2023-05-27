all:
	lex -o rr.yy.c rr.l
	yacc -dtv rr.y -o rr.c
	gcc genpcode.c rr.yy.c rr.c -o rr
	g++ ri.cpp -o ri
debug:
	lex -o rr.yy.c rr.l
	yacc -dtv rr.y -o rr.c
	gcc genpcode.c rr.yy.c rr.c -o rr -Wall -g -Ddebug
	g++ ri.cpp -o ri -g -Wall -Ddebug
clean:
	rm -f genpcode.o
	rm -f rr.yy.c
	rm -f rr.yy.o
	rm -f rr.c
	rm -f rr.h
	rm -f rr
	rm -f rr.output
	rm -f ri
	rm -f ri.log
