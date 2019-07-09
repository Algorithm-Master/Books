	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	_f                      ## -- Begin function f
	.p2align	4, 0x90
_f:                                     ## @f
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -8(%rbp)
	cmpl	$1, -8(%rbp)
	jne	LBB0_2
## %bb.1:
	movl	$1, -4(%rbp)
	jmp	LBB0_5
LBB0_2:
	cmpl	$2, -8(%rbp)
	jne	LBB0_4
## %bb.3:
	movl	$2, -4(%rbp)
	jmp	LBB0_5
LBB0_4:
	movl	-8(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %edi
	callq	_f
	movl	-8(%rbp), %edi
	subl	$2, %edi
	movl	%eax, -12(%rbp)         ## 4-byte Spill
	callq	_f
	movl	-12(%rbp), %edi         ## 4-byte Reload
	addl	%eax, %edi
	movl	%edi, -4(%rbp)
LBB0_5:
	movl	-4(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$7, %edi
	callq	_f
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %esi
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	movl	%eax, -20(%rbp)         ## 4-byte Spill
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$3, -16(%rbp)
	jge	LBB1_4
## %bb.2:                               ##   in Loop: Header=BB1_1 Depth=1
	movl	-16(%rbp), %eax
	addl	-12(%rbp), %eax
	movl	%eax, -12(%rbp)
## %bb.3:                               ##   in Loop: Header=BB1_1 Depth=1
	movl	-16(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
	jmp	LBB1_1
LBB1_4:
	movl	-4(%rbp), %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"test value = %d \n"


.subsections_via_symbols
