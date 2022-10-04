	.file	"h1.c"
	.text
	.globl	hoho
	.type	hoho, @function
hoho:
.LFB23:
	.cfi_startproc
	endbr64
	movq	%rdi, %rax
	leaq	31(%rdi), %rdx
	testq	%rdi, %rdi
	js	.L3
.L2:
	sarq	$5, %rax
	ret
.L3:
	movq	%rdx, %rax
	jmp	.L2
	.cfi_endproc
.LFE23:
	.size	hoho, .-hoho
	.globl	hoho2
	.type	hoho2, @function
hoho2:
.LFB24:
	.cfi_startproc
	endbr64
	leaq	31(%rdi), %rax
	testq	%rdi, %rdi
	cmovns	%rdi, %rax
	sarq	$5, %rax
	ret
	.cfi_endproc
.LFE24:
	.size	hoho2, .-hoho2
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%ld\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB25:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	$2048, %edi
	call	hoho2
	movq	%rax, %rdx
	leaq	.LC0(%rip), %rbx
	movq	%rbx, %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movq	$-64, %rdi
	call	hoho2
	movq	%rax, %rdx
	movq	%rbx, %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$31, %edi
	call	hoho2
	movq	%rax, %rdx
	movq	%rbx, %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$32, %edi
	call	hoho2
	movq	%rax, %rdx
	movq	%rbx, %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$0, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE25:
	.size	main, .-main
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
