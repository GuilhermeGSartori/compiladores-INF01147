#include "tree.h"

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
    char value[LABEL_MAX_SIZE];
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

void updateContent(TableContent* line, char* lexeme_value, int line_num, enum semantic_type type); 

void updateContentType(TableContent* line, enum semantic_type type); 

void setParametersList(TableContent* content, KeyList* list);

void addKeyInList(char* name, KeyList** list, int type, char* value);

void checkParameters(KeyList* parameters, KeyList* list);
