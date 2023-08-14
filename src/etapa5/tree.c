#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int labelCount = 0;
int tempCount = 0;
char label[10];
char temp[10];
extern void exporta (void *arvore);

Node* createLexTypeNode(LexType* lex_value) { 
   
    Node* new_node;
    new_node = (Node*) calloc(1, sizeof(Node));

    strcpy(new_node->label, lex_value->value);
    new_node->lexical_value = lex_value;
    new_node->n_sons = 0;
    new_node->sons = NULL;

    new_node->code = (CmdILOC*)malloc(sizeof(CmdILOC));
    strcpy(new_node->code->cmd, "undefined");
    new_node->code->next = NULL;
    strcpy(new_node->temp, "undefined");
    
    return new_node;
}

Node* createNode(char* value) {

    Node* new_node;
    new_node = (Node*) calloc(1, sizeof(Node));

    strcpy(new_node->label, value);
    new_node->lexical_value = NULL;
    new_node->n_sons = 0;
    new_node->sons = NULL;

    new_node->code = (CmdILOC*)malloc(sizeof(CmdILOC));
    strcpy(new_node->code->cmd, "undefined");
    new_node->code->next = NULL;
    strcpy(new_node->temp, "undefined");

    return new_node;
}

void addSon(Node* father, Node* son) { // O(n)
 
    if(son != NULL) {
        if(father->n_sons == 0) 
            father->sons = malloc(sizeof(struct astNode)); 
        else 
	        father->sons = realloc(father->sons, ((father->n_sons)+1) * sizeof(struct astNode)); //O(n)

        father->sons[father->n_sons] = son; 

        father->n_sons++;
    }
}

void updateLabel(Node* node) {
    if(strcmp(node->label, "if") == 0) // label is "if"
        strcpy(node->label, "if-else");
    else if(node->lexical_value != NULL) {
        if(node->lexical_value->type == LEX_ID) {
	        char dummy[LABEL_MAX_SIZE];
	        strcpy(dummy, "call ");
	        strcat(dummy, node->label);
	        strcpy(node->label, dummy);
	    }
    }
}

int isAttr(Node* node) {
    if(strcmp(node->label, "<=") == 0)
        return 1;
    else
	return 0;
}

void printEdges(Node* father) {
    int n_kids = father->n_sons;
    int i = 0;

    while(n_kids > 0) {
        printf("%p, %p\n", father, father->sons[i]);
	i++;
	n_kids--;
    }

    n_kids = father->n_sons;
    i = 0;

    while(n_kids > 0) {
        printEdges(father->sons[i]);
	i++;
	n_kids--;
    }
 
}

void printNodes(Node* father) {
    int n_kids = father->n_sons;
    int i = 0;

    if(strcmp(father->label, "if-else") == 0) // father->label is "if-else"
        printf("%p [label=\"if\"];\n", father);
    else
        printf("%p [label=\"%s\"];\n", father, father->label);

    while(n_kids > 0) {
        printNodes(father->sons[i]);
        i++;
        n_kids--;
    }
}

void printILOC(Node* father) {
    CmdILOC* commands = father->code;

    while(commands != NULL) {
        printf("%s\n", commands->cmd);
        commands = commands->next;
    }
}

void exporta(void *arvore) {
    Node *father = (Node*) arvore;
    
    if(arvore != NULL) {
        printEdges(arvore);
        printf("\n\n");
        printNodes(arvore);
        printf("\n\n");
        printILOC(arvore);
    }

}

void printKids(Node* father, int height) {
 
    int n_kids = father->n_sons;
    int i = 0;
    printf("height: %d\n", height);
    height++;
    printf("current node: %s\n\n", father->label);
    while(n_kids > 0) {
        printKids(father->sons[i], height);
	i++;
	n_kids--;
    }
}

int getType(Node* node){
	
	return node->type;
}

void setType(Node* node, enum semantic_type type) {
 
    node->type = type;
}

int inferType(enum semantic_type type1, enum semantic_type type2){
	
	if(type1 == type2){
		return type1;
	} else if(((type1 == TYPE_INT) && (type2 == TYPE_FLOAT)) || ((type1 == TYPE_FLOAT) && (type2 == TYPE_INT))){
		return TYPE_FLOAT;
	} else if(((type1 == TYPE_INT) && (type2 == TYPE_BOOL)) || ((type1 == TYPE_BOOL) && (type2 == TYPE_INT))){
		return TYPE_INT;
	} else if(((type1 == TYPE_FLOAT) && (type2 == TYPE_BOOL)) || ((type1 == TYPE_BOOL) && (type2 == TYPE_FLOAT))){
		return TYPE_FLOAT;
	} else if(type1 == TYPE_UNDEFINED){
		return type2;
	} else if(type2 == TYPE_UNDEFINED){
		return type1;
	}
	
}

char* labelGenerator(){
	
	char id[3] = "L";
	labelCount++;
	
	snprintf(label, 10, "%s%d", id, labelCount);
	printf("Label generator %s\n", label);
	
	return label;
}

char* tempGenerator(){
	
	char id[3] = "r";
	tempCount++;
	
	snprintf(temp, 10, "%s%d", id, tempCount);
	//printf("Temp generator %s\n", temp);
	
	return temp;
}

void setTemp(Node* node, char* temp) {
    strcpy(node->temp, temp);
}

void setCode(Node* node, char* code) {
    strcpy(node->code->cmd, code);
}