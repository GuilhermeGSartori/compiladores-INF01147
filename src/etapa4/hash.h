/* The contexts shall be hash tables, when a new scope is created, a new hash table is created, then you add the elements (tableContents) in the HASH*/
#include "table_content.h"

#define TABLE_SIZE 32

typedef struct HashItem {
    SymbolKey* hash_key;
    TableContent* hash_content;
    struct HashItem* next;
} HashItem;

typedef struct Scope {
    int height;
    //int size = TABLE_SIZE;
    int size;
    int count;
    HashItem** lexemes;
    //HashTable* linked_table; its the "same table", but its used if the original table is full -> NAO PRECISA
    struct Scope* previous_scope;
} Scope;


void addInTable(SymbolKey* key, TableContent* content, Scope* table);
//void linkTables(Scope* table); -> NAO PRECISA!
TableContent* findInTable(SymbolKey* key, Scope* table);
int hashFunction(SymbolKey* key);
Scope* createTable(Scope* current_scope); //will return the (now current) scope