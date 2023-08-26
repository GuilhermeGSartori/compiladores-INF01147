int main() {
    return 1;
}

/*** ASSEMBLY x86 ***

	.file	"c_0.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$1, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits


**********************/

/*** ANÁLISE ***
 * 1) Temos um header com o nome do arquvio -> .file<tab><"file">
 * 2) .text -> ?
 * 3) A função main, por estar no contexto global, é definida no segmento de dados (global) com o comando -> .glob<tab>main
 * 4) O tipo da função main (função) é definido com o comando -> .type<tab>main, @funcion
 *      - Isso indica que precisamos consumir a pilha de tabelas! Armazenar as tabelas e consumir o conteúdo dela para saber o conteúdo do seg de dados
 * 5) então entramos na label "main:", aqui começamos o seguimento de código, ou seja, é mais próximo do ILOC, que só são os códigos traduzidos
 *      - No ILOC, esse código ficaria assim:
 *          loadI 1  => r1
 *          //return r1
 *      - Ou seja, só traduzimos o seguimento de código, mas o assembly precisa do de dados, que se encontra nas tabelas
 * 6) LFB0 é uma label
 * 7) Comandos que começam com .cfi NÃO SÃO necessários para o nosso contexto, então, no fim, o código que importa é:

 		main:
		.LFB0:
			pushq	%rbp
			movq	%rsp, %rbp
			movl	$1, %eax
			popq	%rbp
			ret
.		LFE0:
			.size	main, .-main
			.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
			.section	.note.GNU-stack,"",@progbits
					
 * 8)   pushq   %rbp        ; Save address of previous stack frame    
	    movq    %rsp, %rbp  ; Address of current stack frame
        -> Isso é relevante para programas com funções distintas pois lida com stack de PC e etc... Não nos importa

 * 9) movl	$1, %eax coloca no registrador o literal 1
 * 10) popq	%rbp -> Pra mono-função não importa, só colocar antes do return
 * 11) ret retorna o valor em %eax
 * --> usar um registrador pra cada operação e tals, sempre que gerar um R novo, associa a um registrador
 * --> na hora de fazer return, o registrador em "loadI 1  => r1" vai ser sempre o eax

 * x) %eax é um registrador de 4 bytes (32 bits), que bate com nossa definição de inteiro!
 * x) Parece que a Intel nos fornece 32 registradores de uso geral para 32 bits, a moral é casar cada rX (r1, r2, r3..) com um desses registradores
 * x) parece que o registrador eax eh sempre o retornado
****************/