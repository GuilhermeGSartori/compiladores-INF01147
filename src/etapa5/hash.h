/* The contexts shall be hash tables, when a new scope is created, a new hash table is created, then you add the elements (tableContents) in the HASH*/
#include "table_content.h"
#include <stdlib.h>

#define TABLE_SIZE 32

typedef struct HashItem {
    TableContent* hash_content;
    struct HashItem* next;
} HashItem;

typedef struct Scope {
    int height;
    int size;
    int count;
    HashItem** lexemes;

    struct Scope* previous_scope;

} Scope;


HashItem* createHashItem(TableContent* content);
void addInTable(TableContent* content, Scope* table, int line, int* local_offset, int* global_offset);
void assertContentIsFUN(int nature, int line);
void assertContentIsID(int nature, int line);
TableContent* findInTableStack(SymbolKey* key, Scope* stack_top, int nature, int line);
TableContent* findInTable(SymbolKey* key, Scope* table);
int hashFunction(SymbolKey* key);
Scope* createTable(Scope* current_scope); //will return the (now current) scope
Scope* popTable(Scope* stack_top);