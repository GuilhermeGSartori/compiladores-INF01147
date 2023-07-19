#include "table_content.h"

typedef symbolKey char[LABEL_MAX_SIZE]

enum symbol_nature {
    LIT_SYMBOL,
    ID_SYMBOL,
    FUN_SYMBOL
};

/* this should represent a line (symbol) in the table of a scope, every scope has a table in the stack
 * the attributes are the values of each collumn in the table.
 * The first collumn of the table should be the key to the rest of the line */
typedef struct tableContent {
    int line;
    enum symbol_nature nature;
    enum lex_type type;
    char value[LABEL_MAX_SIZE];
} tableContent;

addToCurrentTable(tableContent* new_line); // tabela vai ser como? como sei que tenho uma tabela e pilha de tabelas? como eh essa pilha de tabela e o q eu de fato empilho?
                                           // outra struct? hash?  eh meio uma lista encadeada, mas o q tem em cada nodo da lista? eh a "hash" que via ter os simbolos dai
findInTableStack(symbolKey key);
findInCUrrentTable(symbolKey key);
