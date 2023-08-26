int a = 1;
int main() {
    return 0;
}

/*** ASSEMBLY x86 ***

	.file   "c_1.c"
	.text
	.globl	a
	.data
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	1
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
	movl	$0, %eax
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
 * 3) TODA ESTRTURA DE CÓDIGO É IGUAL AO EXEMPLO DO c_0.c, a única diferença é o segmento de dados!
 * 4) Ao definir uma global (seg. de dados) é definido com o seguinte comando: 
****************/