###
#Guilherme Girotto Sartori - 00274713 Marlize Ramos Batista - 00274703
###

etapa5: lextype.o tree.o table_content.o hash.o parser.tab.o lex.yy.o main.o tac.o
	gcc -o etapa5 parser.tab.o lex.yy.o lextype.o tree.o table_content.o hash.o tac.o main.o

test_ds: lextype.o tree.o table_content.o hash.o test_ds.o
	gcc -o test_ds lextype.o tree.o table_content.o hash.o test_ds.o

main.o: main.c
	gcc -c main.c
parser.tab.o: parser.tab.c
	gcc -c parser.tab.c
parser.tab.c: parser.y hash.h
	bison -d parser.y
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex scanner.l 
lextype.o: lextype.c lextype.h lextype.c
	gcc -c lextype.c
tree.o: tree.c tree.h lextype.h tree.c
	gcc -c tree.c
tac.o: tac.c tac.h
	gcc -c tac.c
table_content.o: table_content.h tree.h table_content.c
	gcc -c table_content.c
hash.o: table_content.h hash.h hash.c
	gcc -c hash.c
clean:
	rm *.o lex.yy.c parser.tab.c etapa5
