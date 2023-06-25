###
#Guilherme Girotto Sartori - 00274713 Marlize Ramos Batista - 00274703
###

etapa2: parser.tab.o lex.yy.o main.o
	gcc -o etapa2 parser.tab.o lex.yy.o main.o
main.o: main.c
	gcc -c main.c
parser.tab.o: parser.tab.c
	gcc -c parser.tab.c
parser.tab.c: parser.y
	bison -d parser.y
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex scanner.l 
lextype.o: lextype.c lextype.h
	gcc -c lextype.c
tree.o: tree.c tree.h lextype.h
	gcc -c tree.c
test_data_structure.o: test_data_structure.c
	gcc -c test_data_structure.c
clean:
	rm *.o lex.yy.c parser.tab.c etapa2

test1: lextype.o tree.o parser.tab.o lex.yy.o test_data_structure.o 
	gcc -o test1 parser.tab.o lex.yy.o lextype.o tree.o test_data_structure.o
