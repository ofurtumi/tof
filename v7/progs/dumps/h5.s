	.file	"h5.c"
	.text
	.globl	func
	.type	func, @function
func:
.LFB39:
	.cfi_startproc
	endbr64
	cmpl	$4, %edi
	jg	.L2
	cmpl	$3, %edi
	jge	.L3
	testl	%edi, %edi
	je	.L4
	cmpl	$2, %edi
	jne	.L7
.L4:
	leal	3(%rdi,%rdi), %eax
	ret
.L7:
	movl	%edi, %eax
	ret
.L2:
	cmpl	$5, %edi
	jne	.L8
	leal	0(,%rdi,8), %edx
	movl	$3, %edi
	movl	%edi, %eax
	subl	%edx, %eax
	ret
.L8:
	movl	%edi, %eax
	ret
.L3:
	leal	3(%rdi), %eax
	ret
	.cfi_endproc
.LFE39:
	.size	func, .-func
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB40:
	.cfi_startproc
	endbr64
	cmpl	$1, %edi
	jg	.L15
	movl	$0, %eax
	ret
.L15:
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movq	8(%rsi), %rdi
	movl	$10, %edx
	movl	$0, %esi
	call	strtol@PLT
	movl	%eax, %edi
	call	func
	movl	%eax, %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE40:
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
