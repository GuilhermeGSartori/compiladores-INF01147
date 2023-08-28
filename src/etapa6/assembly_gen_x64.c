#include "assembly_gen_x64.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;
Scope *global_scope = NULL;
char ILOCCode[CMD_MAX_SIZE];

// como tudo vai ser usando int (32 bits), usar as operacoes de 32 bits! tipo movl e os regs de 32 bits
char x64_32op_regs[REGS_N][10] =   {
                                        {"\%ebx"}, 
                                        {"\%ecx"},
                                        {"\%edx"},
                                        {"\%esi"},
                                        {"\%edi"},
                                        {"\%ebp"},
                                        {"\%esp"},
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
    // if x64?
    // pegar a global onde tá o código ILOC já em vetor de strings
    // ou seja, antes dessa função, já criar o vetor de strings (global) e preencher com o código ILOC
    // também já pega a tabela global e separa em algum lugar global
    // pega o global com ILOC e global com tabela global
    // cria arquivo .s de saida
    // pega a tabela e escreve o segmento de dados no .s
    // escreve todos os headers e coisas interessantes no .s até a main, .LFB0, push %rbp, mvq %rsp, %rbp
    // loop passando por esse vetor
    // analisando comando por comando e suas possiveis combinacoes
    // vai escrevendo segmento de codigo
    // escreve final do .s
    // gg

    file = fopen("output.s", "w");

    //printf("height: %d\n", global_scope->height);

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

    //quebrar esse ILOCCode em um array de strings e dai fazer a traducao
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
        //printf("%d: %s\n", i, code_lines[i]);
        fprintf(file, "\t%s\n", code_lines[i]);
		translateCode(code_lines[i]);
        i++;
        // AQUI FAZER TODA ANALISE DE TRADUCAO DE LINHA POR LINHA
    }

    //fprintf(file, "\n%s\n", ILOCCode);
    //fprintf(file, "\n\n%s\n", x64_32op_regs[0]);

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
	
	if(strcmp(line_separated[0], "loadI") == 0){
		memmove(line_separated[3], line_separated[3]+1, strlen(line_separated[3]));
		//printf("separated: %s\n", line_separated[3]);
		int register_number = atoi(line_separated[3]);
		//printf("register number: %d\n", register_number);
		fprintf(file, "\tmovl\t$%s, (%s)\n", line_separated[1], x64_32op_regs[register_number-1]);
	}
	
}