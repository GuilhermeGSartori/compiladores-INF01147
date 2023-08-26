#include "assembly_gen_x64.h"

// como tudo vai ser usando int (32 bits), usar as operacoes de 32 bits! tipo movl e os regs de 32 bits
char* x64_32op_regs[REGS_N][10] =   {
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
                                        {"\%r15d"},
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
}