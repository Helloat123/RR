all:
	#gcc -c genpcode.c -o genpcode.o
	lex -o rr.yy.c rr.l
	yacc -dtv rr.y -o rr.c
	#gcc -c rr.yy.c -o rr.yy.o
	#gcc rr.yy.o rr.c -o rr
	gcc genpcode.c rr.yy.c rr.c -o rr
debug:
	lex -o rr.yy.c rr.l
	yacc -dtv rr.y -o rr.c
	gcc genpcode.c rr.yy.c rr.c -o rr -Wall -g -Ddebug
clean:
	rm genpcode.o
	rm -f rr.yy.c
	rm -f rr.yy.o
	rm -f rr.c
	rm -f rr.h
	rm -f rr
	rm -f rr.output
