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
    //int size = TABLE_SIZE;
    int size;
    int count;
    HashItem** lexemes;
    //HashTable* linked_table; its the "same table", but its used if the original table is full -> NAO PRECISA
    struct Scope* previous_scope;

    //ParameterList* parameters; // if nature is FUN, it can
                                     // when adding the arguments in the table, we should find a way to find the function itself in the previous table
                                     // where will we find the key???
                                     // after finding the content of the function, we should malloc the number of parameters for this array
                                     // and add in the respective order by the index the types of the created parameters
                                     // it can only malloc if the nature is FUN!
} Scope;

//Scope* scope_stack = NULL;

HashItem* createHashItem(TableContent* content);
void addInTable(TableContent* content, Scope* table);
void assertContentIsFUN(int nature);
void assertContentIsID(int nature);
TableContent* findInTableStack(SymbolKey* key, Scope* stack_top, int nature);
TableContent* findInTable(SymbolKey* key, Scope* table);
int hashFunction(SymbolKey* key);
Scope* createTable(Scope* current_scope); //will return the (now current) scope
void popTable(Scope* stack_top);
void invalidSemanticOperation();
void addParameterInList(int type, ParameterList** list);