//#include "tree.h"
#include "lextype.h"

enum boolean {
    FALSE = 0,
    TRUE = 1
};

enum symbol_nature {
    LIT_SYMBOL,
    ID_SYMBOL,
    FUN_SYMBOL
};


typedef struct SymbolKey { char key[LABEL_MAX_SIZE]; };

/* this should represent a line (symbol) in the table of a scope, every scope has a table in the stack
 * the attributes are the values of each collumn in the table.
 * The first collumn of the table should be the key to the rest of the line */
typedef struct TableContent {
    SymbolKey* key;
    int line;
    enum symbol_nature nature;
    enum lex_type type;
    char value[LABEL_MAX_SIZE];
} TableContent;

void addToCurrentTable(TableContent* new_line); // tabela vai ser como? como sei que tenho uma tabela e pilha de tabelas? como eh essa pilha de tabela e o q eu de fato empilho?
                                           // outra struct? hash?  eh meio uma lista encadeada, mas o q tem em cada nodo da lista? eh a "hash" que via ter os simbolos dai
enum boolean findInTableStack(SymbolKey key);
enum boolean findInCurrentTable(SymbolKey key);
