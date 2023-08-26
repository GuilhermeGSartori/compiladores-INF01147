// Fazer um map aqui de funções ILOC para funções x86

// Esforço vai ser em basicamente fazer a engenharia reversa, descobrir como mapear, então:
// entender como assembly (dados e código) eh gerado a partir de um .c em x64
// adaptar tabela global (segmento de dados) para assembly
// adaptar tabelas local da main para assembly (ou nao? eh run time isso? heap e pilha e tals)
// mapear comandos ILOC para assembly em segmento de dados

#define REGS_N 15

#include "hash.h"



void generateAsm();