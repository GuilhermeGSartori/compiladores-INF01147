	.file	"c_6.c"
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
	movl	$20, -12(%rbp)
	movl	$300, -8(%rbp)
	movl	-8(%rbp), %eax
	addl	$300, %eax
	movl	%eax, -4(%rbp)
	cmpl	$0, -12(%rbp)
	je	.L2
	cmpl	$0, -8(%rbp)
	je	.L2
	movl	$22, -12(%rbp)
	movl	$33, -12(%rbp)
.L2:
	cmpl	$4, -12(%rbp)
	je	.L3
	movl	$5, -12(%rbp)
	movl	$6, -12(%rbp)
.L3:
	cmpl	$7, -12(%rbp)
	jle	.L4
	movl	$8, -12(%rbp)
	movl	$9, -12(%rbp)
.L4:
	cmpl	$9, -12(%rbp)
	jg	.L5
	movl	$11, -12(%rbp)
	movl	$12, -12(%rbp)
.L5:
	cmpl	$12, -12(%rbp)
	jle	.L6
	movl	$14, -12(%rbp)
	movl	$15, -12(%rbp)
.L6:
	cmpl	$16, -12(%rbp)
	jg	.L7
	movl	$17, -12(%rbp)
	movl	$18, -12(%rbp)
.L7:
	cmpl	$19, -12(%rbp)
	jne	.L8
	movl	$20, -12(%rbp)
	movl	$21, -12(%rbp)
	jmp	.L9
.L8:
	movl	$22, -12(%rbp)
	movl	$23, -12(%rbp)
.L9:
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
