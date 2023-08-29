#include "assembly_gen_x64.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;
Scope *global_scope = NULL;
char ILOCCode[CMD_MAX_SIZE];
int num_of_main_vars = 0;

// como tudo vai ser usando int (32 bits), usar as operacoes de 32 bits! tipo movl e os regs de 32 bits
char x64_32op_regs[REGS_N][10] =   {
                                        {"\%eax"}, 
                                        {"\%ebx"}, 
                                        {"\%ecx"},
                                        {"\%edx"},
                                        {"\%r8d"},
                                        {"\%r9d"},
                                        {"\%r10d"},
                                        {"\%r11d"},
                                        {"\%r12d"},
                                        {"\%r13d"},
                                        {"\%r14d"},
                                        {"\%r15d"}
                                    };
char x64_ret_reg[10] = "\%eax";

void generateAsm() {

    file = fopen("output.s", "w");

    if(file == NULL)
    {
        printf("Error!\n");   
        exit(1);             
    }

    fprintf(file, "%s", "\t.file\t\"input\"\n\t.text\n");

    for(int i = 0; i < TABLE_SIZE; i++) {
        HashItem* itens = global_scope->lexemes[i];
        while(itens != NULL) {
            if(itens->hash_content->nature == ID_SYMBOL)
                fprintf(file, "\t.comm\t%s,4,4\n", itens->hash_content->key->key_name);
            itens = itens->next;
        }
    }

    fprintf(file, "%s", "\t.globl\tmain\n\t.type\tmain, @function\n");

    fprintf(file, "%s", "main:\n");
    fprintf(file, "%s", ".LFB0:\n");

    fprintf(file, "\tpushq\t%srbp\n", "\%");
    fprintf(file, "\tmovq\t%srsp, %srbp\n", "\%", "\%");

    char code_lines[CMD_MAX_SIZE][CMD_MAX_SIZE]; // too big?
    char* pch = NULL;
    pch = strtok(ILOCCode, "\n");
    int i = 0;
    while (pch != NULL)
    {
        strcpy(code_lines[i], pch);
        pch = strtok(NULL, "\n");
        i++;
    }
    strcpy(code_lines[i], "!end!");

    i = 0;
    while(strcmp(code_lines[i], "!end!") != 0) {
		translateCode(code_lines[i]);
        i++;
    }

    fclose(file);
}

void translateCode(char* line){
	char line_separated[10][10];
	char* pch = NULL;
	char origin[10];
    pch = strtok(line, " ");
    int i = 0;

    while (pch != NULL)
    {
        strcpy(line_separated[i], pch);
        pch = strtok(NULL, " ");
        i++;
    }
	
	if(strcmp(line_separated[0], "L") == 0){
		memmove(line_separated[0], line_separated[0]+1, strlen(line_separated[0]));
		int label_number = atoi(line_separated[0]);
		fprintf(file, ".L%d:\n", label_number);
		
	} else if(strcmp(line_separated[0], "loadI") == 0){
		memmove(line_separated[3], line_separated[3]+1, strlen(line_separated[3]));
		int register_number = (atoi(line_separated[3])-1)%REGS_N;

		fprintf(file, "\tmovl\t$%s, %s\n", line_separated[1], x64_32op_regs[register_number]);

	} else if(strcmp(line_separated[0], "storeAI") == 0){
        memmove(line_separated[1], line_separated[1]+1, strlen(line_separated[1]));
        int register_number = (atoi(line_separated[1])-1)%REGS_N;
        fprintf(file, "\tmovl\t%s, ", x64_32op_regs[register_number]);
        if(strcmp(line_separated[3], "rbss") == 0) {
            char RAIVA[5] = {"\%"};
            fprintf(file, "%s(%s", searchOffset(atoi(line_separated[5])), RAIVA);
            fprintf(file, "rip)\n");
        } else if (strcmp(line_separated[3], "rfp") == 0) {
			int desvio_maximo = num_of_main_vars * 4;
			int offset = atoi(line_separated[5]) - desvio_maximo;
			char RAIVA[5] = {"\%"};
            fprintf(file, "%d(%s", offset, RAIVA);
            fprintf(file, "rbp)\n");
		}

	} else if(strcmp(line_separated[0], "loadAI") == 0){
		memmove(line_separated[5], line_separated[5]+1, strlen(line_separated[5]));
		int register_number = (atoi(line_separated[5])-1)%REGS_N;
		fprintf(file, "\tmovl\t");
		if(strcmp(line_separated[1], "rbss") == 0) {
            char RAIVA[5] = {"\%"};
            fprintf(file, "%s(%s", searchOffset(atoi(line_separated[3])), RAIVA);
            fprintf(file, "rip), %s\n", x64_32op_regs[register_number]);
        } else if (strcmp(line_separated[1], "rfp") == 0) {
			int desvio_maximo = num_of_main_vars * 4;
			int offset = atoi(line_separated[3]) - desvio_maximo;
			char RAIVA[5] = {"\%"};
			fprintf(file, "%d(%s", offset, RAIVA);
            fprintf(file, "rbp), %s\n", x64_32op_regs[register_number]);
		}

	} else if(strcmp(line_separated[0], "add") == 0){
        memmove(line_separated[1], line_separated[1]+1, strlen(line_separated[1]));
        memmove(line_separated[3], line_separated[3]+1, strlen(line_separated[3]));
        memmove(line_separated[5], line_separated[5]+1, strlen(line_separated[5]));
		int register_number1 = (atoi(line_separated[1])-1)%REGS_N;
        int register_number2 = (atoi(line_separated[3])-1)%REGS_N;
        int register_number3 = (atoi(line_separated[5])-1)%REGS_N;

        fprintf(file, "\taddl\t%s, %s\n", x64_32op_regs[register_number1], x64_32op_regs[register_number2]);
        //addl edx, esi
        fprintf(file, "\tmovl\t%s, %s\n", x64_32op_regs[register_number2], x64_32op_regs[register_number3]);
        //movl esi, edi

	} else if(strcmp(line_separated[0], "sub") == 0){
		memmove(line_separated[1], line_separated[1]+1, strlen(line_separated[1]));
        memmove(line_separated[3], line_separated[3]+1, strlen(line_separated[3]));
        memmove(line_separated[5], line_separated[5]+1, strlen(line_separated[5]));
		int register_number1 = (atoi(line_separated[1])-1)%REGS_N;;
        int register_number2 = (atoi(line_separated[3])-1)%REGS_N;;
        int register_number3 = (atoi(line_separated[5])-1)%REGS_N;;

        fprintf(file, "\tsubl\t%s, %s\n", x64_32op_regs[register_number2], x64_32op_regs[register_number1]);
        //subl edx, esi
        fprintf(file, "\tmovl\t%s, %s\n", x64_32op_regs[register_number1], x64_32op_regs[register_number3]);
        //movl esi, edi

	} else if(strcmp(line_separated[0], "mult") == 0){
		memmove(line_separated[1], line_separated[1]+1, strlen(line_separated[1]));
        memmove(line_separated[3], line_separated[3]+1, strlen(line_separated[3]));
        memmove(line_separated[5], line_separated[5]+1, strlen(line_separated[5]));
		int register_number1 = (atoi(line_separated[1])-1)%REGS_N;
        int register_number2 = (atoi(line_separated[3])-1)%REGS_N;
        int register_number3 = (atoi(line_separated[5])-1)%REGS_N;

        fprintf(file, "\timull\t%s, %s\n", x64_32op_regs[register_number1], x64_32op_regs[register_number2]);
        //imull edx, esi
        fprintf(file, "\tmovl\t%s, %s\n", x64_32op_regs[register_number2], x64_32op_regs[register_number3]);
        //movl esi, edi

	} else if(strcmp(line_separated[0], "div") == 0){
		//todo

	} else if(strcmp(line_separated[0], "//return") == 0){
		memmove(line_separated[1], line_separated[1]+1, strlen(line_separated[1]));
        int register_number = (atoi(line_separated[1])-1)%REGS_N;
        char RAIVA[5] = {"\%"};
        fprintf(file, "\tmovl\t%s, %s\n", x64_32op_regs[register_number], x64_ret_reg);
        fprintf(file, "\tpopq	%srbp\n", RAIVA);
        fprintf(file, "\tret\n");
	}
		
}

char* searchOffset(int offset) {

    for(int i = 0; i < TABLE_SIZE; i++) {
        HashItem* itens = global_scope->lexemes[i];
        while(itens != NULL) {
            if(itens->hash_content->nature == ID_SYMBOL && atoi(itens->hash_content->offset) == offset)
                return itens->hash_content->key->key_name;
            itens = itens->next;
        }
    }
}