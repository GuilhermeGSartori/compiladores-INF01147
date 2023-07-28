#include "tree.h"
//#include "lextype.h"

#define ERR_UNDECLARED 10 //2.2
#define ERR_DECLARED 11 //2.2
#define ERR_VARIABLE 20 //2.3
#define ERR_FUNCTION 21 //2.3


enum symbol_nature {
    LIT_SYMBOL,
    ID_SYMBOL,
    FUN_SYMBOL
};


typedef struct SymbolKey { char key_name[LABEL_MAX_SIZE]; } SymbolKey;

typedef struct KeyList {
    SymbolKey key;
    enum semantic_type type;
    struct KeyList* next;
} KeyList;

/* this should represent a line (symbol) in the table of a scope, every scope has a table in the stack
 * the attributes are the values of each collumn in the table.
 * The first collumn of the table should be the key to the rest of the line */
typedef struct TableContent {
    SymbolKey* key;
    int line;
    enum symbol_nature nature;
    enum semantic_type type;
    char value[LABEL_MAX_SIZE];

    KeyList* parameters;
} TableContent;


SymbolKey* mallocAndSetKeyName(char* value);

void setKeyName(SymbolKey* key, char* value);

char* getKeyName(TableContent* line);

TableContent* newContent(SymbolKey* key, char* lexeme_value, int line, enum symbol_nature nat, enum semantic_type type); 
// pega o contexto atual e tenta criar, se ja existe, retorna erro! -> usa findInCurrentTable

void updateContent(TableContent* line, char* lexeme_value, int line_num, enum semantic_type type); 

void updateContentType(TableContent* line, enum semantic_type type); 

void setParametersList(TableContent* content, KeyList* list);

void addKeyInList(char* name, KeyList** list, int type);

//atualiza o conteudo de dado lexema no contexto mais proximo (desce stack) -> usa findInTableStack e verifica semantica!

// atributos de NT sao usados para inferencia de tipos e tals... E controle de tabela atual? saber qual tabela to e etc
// ONDE FICA A PILHA DE HASH

// essa funcao no fim no fim, vai chamar a addElement da hash table
//void addToCurrentTable(TableContent* new_line); // tabela vai ser como? como sei que tenho uma tabela e pilha de tabelas? como eh essa pilha de tabela e o q eu de fato empilho?
                                           // outra struct? hash?  eh meio uma lista encadeada, mas o q tem em cada nodo da lista? eh a "hash" que via ter os simbolos dai
//enum boolean findInTableStack(SymbolKey key);   // vai descendo a stack de hash tables
//enum boolean findInCurrentTable(SymbolKey key); // procura na hash table atual (topo da stack)
