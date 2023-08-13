/* to do
- estrutura de dados para representar uma operação ILOC e os argumentos necessários para ela
- estrutura para manter uma lista de operações ILOC

- implementar uma função geradora de nomes de rótulos
- implementar uma função geradora de nomes de temporários (seguir padrão ILOC)

- traduzir as seguinetes construções da linguagem, considerando que existe apenas o tipo int:
		* expressões aritméticas com operações binárias (soma, subtração, multiplicação e divisão);
		* expressões lógicas (operadores relacionais e operadores lógicos);
		* comando de atribuição;
		* comandos de fluxo de controle (if com else opcional, while);

- calcular o endereço na declaração de variáveis locais com deslocamento a rfp
- calcular o endereço na declaração de variáveis globais com deslocamento a rbss

*/

#include "tac.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


CmdILOC* createCmd(char* command, char* register1, char* register2, char* register3, enum cmd_type type) {
	
	char ILOC[CMD_MAX_SIZE];

	strcpy(ILOC, command);

	if(type == MOST_LEFT) {
		strcat(ILOC, " ");
		strcat(ILOC, register1);
		strcat(ILOC, ", ");
		strcat(ILOC, register2);
		strcat(ILOC, " => ");
		strcat(ILOC, register3);
	}

	if(type == MOST_RIGHT) {
		strcat(ILOC, " ");
		strcat(ILOC, register1);
		strcat(ILOC, "  => ");
		strcat(ILOC, register2);
		if(register3 != NULL) {
			strcat(ILOC, ", ");
			strcat(ILOC, register3);
		}
	}

	CmdILOC* cmd = (CmdILOC*)malloc(sizeof(CmdILOC));
	strcpy(cmd->cmd, ILOC);

	return cmd;
}

CmdILOC* concatCode(CmdILOC * code1, CmdILOC* code2) {
	CmdILOC* concatened = (CmdILOC*)malloc(sizeof(CmdILOC));
	strcpy(concatened->cmd, code1->cmd);
	strcat(concatened->cmd, "\n");
	strcat(concatened->cmd, code2->cmd);
	return concatened;
}