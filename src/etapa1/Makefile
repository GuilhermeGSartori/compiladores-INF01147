###
#Guilherme Girotto Sartori - 00274713 Marlize Ramos Batista - 00274703
###

etapa1: lex.yy.o main.o
	gcc -o etapa1 lex.yy.o main.o
main.o: main.c
	gcc -c main.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex scanner.l 
clean:
	rm *.o lex.yy.c etapa1
