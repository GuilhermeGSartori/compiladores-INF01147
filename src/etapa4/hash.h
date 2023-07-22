/* The contexts shall be hash tables, when a new scope is created, a new hash table is created, then you add the elements (tableContents) in the HASH*/
#include "table_content.h"

#define TABLE_SIZE 32

typedef struct HashItem {
    SymbolKey* hash_key;
    TableContent* hash_content;
    HashItem* next;
} HashItem;

typedef struct HashTable {
    int height;
    int size;
    int count;
    HashItem** lexemes;
    //HashTable* linked_table; its the "same table", but its used if the original table is full -> NAO PRECISA
    Scope* previous_scope;
} Scope;


void addInTable(SymbolKey* key, Scope* table);
//void linkTables(Scope* table); -> NAO PRECISA!
void findInTable(SymbolKey* key, Scope* table);
int hashFunction(SymbolKey* key, int size);
Scope* createTable(int size, Scope* current_scope); //will return the (now current) scope