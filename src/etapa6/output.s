	.file	"input"
	.text
	.comm	a,4,4
	.comm	b,4,4
	.comm	c,4,4
	.globl	main
	.type	main, @function
main:
.LFB0:
	loadI 1  => r1
	loadI 1  => r2
	add r1, r2 => r3
	storeAI r3  => rfp, 0
	loadAI rfp, 0 => r4
	//return r4
