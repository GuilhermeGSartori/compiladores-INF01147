	.file	"c_6.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$0, -4(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L2
	movl	$2, -4(%rbp)
	movl	$3, -4(%rbp)
.L2:
	cmpl	$4, -4(%rbp)
	je	.L3
	movl	$5, -4(%rbp)
	movl	$6, -4(%rbp)
.L3:
	cmpl	$7, -4(%rbp)
	jle	.L4
	movl	$8, -4(%rbp)
	movl	$9, -4(%rbp)
.L4:
	cmpl	$9, -4(%rbp)
	jg	.L5
	movl	$11, -4(%rbp)
	movl	$12, -4(%rbp)
.L5:
	cmpl	$12, -4(%rbp)
	jle	.L6
	movl	$14, -4(%rbp)
	movl	$15, -4(%rbp)
.L6:
	cmpl	$16, -4(%rbp)
	jg	.L7
	movl	$17, -4(%rbp)
	movl	$18, -4(%rbp)
.L7:
	cmpl	$19, -4(%rbp)
	jne	.L8
	movl	$20, -4(%rbp)
	movl	$21, -4(%rbp)
	jmp	.L9
.L8:
	movl	$22, -4(%rbp)
	movl	$23, -4(%rbp)
.L9:
	movl	$0, %eax
	popq	%rbp
	ret
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
