	.file	"h4.c"
# GNU C17 (Ubuntu 11.2.0-19ubuntu1) version 11.2.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.2.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O2 -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.p2align 4
	.globl	fact
	.type	fact, @function
fact:
.LFB0:
	.cfi_startproc
	endbr64	
# h4.c:2:     if (n <= 1)
	movl	$1, %eax	#, <retval>
	cmpq	$1, %rdi	#, n
	jle	.L1	#,
	.p2align 4,,10
	.p2align 3
.L2:
	movq	%rdi, %rdx	# n, n
# h4.c:5:         return n * fact(n-1);
	subq	$1, %rdi	#, n
	imulq	%rdx, %rax	# n, <retval>
# h4.c:2:     if (n <= 1)
	cmpq	$1, %rdi	#, n
	jne	.L2	#,
.L1:
# h4.c:6: }
	ret	
	.cfi_endproc
.LFE0:
	.size	fact, .-fact
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
