	.file	"c_6.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$20, -8(%rbp)
	movl	$30, -4(%rbp)
	cmpl	$0, -8(%rbp)
	je	.L2
	cmpl	$0, -4(%rbp)
	je	.L2
	movl	$22, -8(%rbp)
	movl	$33, -8(%rbp)
.L2:
	cmpl	$4, -8(%rbp)
	je	.L3
	movl	$5, -8(%rbp)
	movl	$6, -8(%rbp)
.L3:
	cmpl	$7, -8(%rbp)
	jle	.L4
	movl	$8, -8(%rbp)
	movl	$9, -8(%rbp)
.L4:
	cmpl	$9, -8(%rbp)
	jg	.L5
	movl	$11, -8(%rbp)
	movl	$12, -8(%rbp)
.L5:
	cmpl	$12, -8(%rbp)
	jle	.L6
	movl	$14, -8(%rbp)
	movl	$15, -8(%rbp)
.L6:
	cmpl	$16, -8(%rbp)
	jg	.L7
	movl	$17, -8(%rbp)
	movl	$18, -8(%rbp)
.L7:
	cmpl	$19, -8(%rbp)
	jne	.L8
	movl	$20, -8(%rbp)
	movl	$21, -8(%rbp)
	jmp	.L9
.L8:
	movl	$22, -8(%rbp)
	movl	$23, -8(%rbp)
.L9:
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
