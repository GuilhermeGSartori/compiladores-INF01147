	.file	"input"
	.text
	.comm	a,4,4
	.comm	b,4,4
	.comm	c,4,4
	.globl	main
	.type	main, @function
main:
.LFB0:
	loadI 0  => r1
	//return r1
