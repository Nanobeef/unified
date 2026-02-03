	.file	"main.c"
	.text
.Ltext0:
	.file 0 "/home/ic/unified" "main.c"
	.globl	f32x2_set1
	.type	f32x2_set1, @function
f32x2_set1:
.LFB509:
	.file 1 "f32x2.c"
	.loc 1 4 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movss	%xmm0, -20(%rbp)
	.loc 1 4 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 5 8
	movss	-20(%rbp), %xmm0
	movss	%xmm0, -16(%rbp)
	movss	-20(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	.loc 1 6 9
	movq	-16(%rbp), %rax
	.loc 1 7 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE509:
	.size	f32x2_set1, .-f32x2_set1
	.globl	f32x2_set
	.type	f32x2_set, @function
f32x2_set:
.LFB510:
	.loc 1 10 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movss	%xmm0, -20(%rbp)
	movss	%xmm1, -24(%rbp)
	.loc 1 10 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 11 8
	movss	-20(%rbp), %xmm0
	movss	%xmm0, -16(%rbp)
	movss	-24(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	.loc 1 12 9
	movq	-16(%rbp), %rax
	.loc 1 13 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L6
	call	__stack_chk_fail@PLT
.L6:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE510:
	.size	f32x2_set, .-f32x2_set
	.globl	f32x2_load
	.type	f32x2_load, @function
f32x2_load:
.LFB511:
	.loc 1 16 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	.loc 1 16 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 18 2
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	.loc 1 19 9
	movq	-16(%rbp), %rax
	.loc 1 20 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L9
	call	__stack_chk_fail@PLT
.L9:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE511:
	.size	f32x2_load, .-f32x2_load
	.globl	f32x2_scatter
	.type	f32x2_scatter, @function
f32x2_scatter:
.LFB512:
	.loc 1 23 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%xmm0, -24(%rbp)
	.loc 1 24 8
	movss	-24(%rbp), %xmm0
	.loc 1 24 5
	movq	-8(%rbp), %rax
	movss	%xmm0, (%rax)
	.loc 1 25 8
	movss	-20(%rbp), %xmm0
	.loc 1 25 5
	movq	-16(%rbp), %rax
	movss	%xmm0, (%rax)
	.loc 1 26 1
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE512:
	.size	f32x2_scatter, .-f32x2_scatter
	.globl	f32x2_add
	.type	f32x2_add, @function
f32x2_add:
.LFB513:
	.loc 1 29 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	.loc 1 29 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 31 12
	movss	-24(%rbp), %xmm1
	.loc 1 31 19
	movss	-32(%rbp), %xmm0
	.loc 1 31 15
	addss	%xmm1, %xmm0
	.loc 1 31 8
	movss	%xmm0, -16(%rbp)
	.loc 1 32 12
	movss	-20(%rbp), %xmm1
	.loc 1 32 19
	movss	-28(%rbp), %xmm0
	.loc 1 32 15
	addss	%xmm1, %xmm0
	.loc 1 32 8
	movss	%xmm0, -12(%rbp)
	.loc 1 33 9
	movq	-16(%rbp), %rax
	.loc 1 34 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L13
	call	__stack_chk_fail@PLT
.L13:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE513:
	.size	f32x2_add, .-f32x2_add
	.globl	f32x2_add1
	.type	f32x2_add1, @function
f32x2_add1:
.LFB514:
	.loc 1 36 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	movss	%xmm1, -28(%rbp)
	.loc 1 36 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 38 12
	movss	-24(%rbp), %xmm0
	.loc 1 38 15
	addss	-28(%rbp), %xmm0
	.loc 1 38 8
	movss	%xmm0, -16(%rbp)
	.loc 1 39 12
	movss	-20(%rbp), %xmm0
	.loc 1 39 15
	addss	-28(%rbp), %xmm0
	.loc 1 39 8
	movss	%xmm0, -12(%rbp)
	.loc 1 40 9
	movq	-16(%rbp), %rax
	.loc 1 41 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L16
	call	__stack_chk_fail@PLT
.L16:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE514:
	.size	f32x2_add1, .-f32x2_add1
	.globl	f32x2_sub
	.type	f32x2_sub, @function
f32x2_sub:
.LFB515:
	.loc 1 44 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	.loc 1 44 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 46 12
	movss	-24(%rbp), %xmm0
	.loc 1 46 19
	movss	-32(%rbp), %xmm1
	.loc 1 46 15
	subss	%xmm1, %xmm0
	.loc 1 46 8
	movss	%xmm0, -16(%rbp)
	.loc 1 47 12
	movss	-20(%rbp), %xmm0
	.loc 1 47 19
	movss	-28(%rbp), %xmm1
	.loc 1 47 15
	subss	%xmm1, %xmm0
	.loc 1 47 8
	movss	%xmm0, -12(%rbp)
	.loc 1 48 9
	movq	-16(%rbp), %rax
	.loc 1 49 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L19
	call	__stack_chk_fail@PLT
.L19:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE515:
	.size	f32x2_sub, .-f32x2_sub
	.globl	f32x2_sub1
	.type	f32x2_sub1, @function
f32x2_sub1:
.LFB516:
	.loc 1 51 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	movss	%xmm1, -28(%rbp)
	.loc 1 51 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 53 12
	movss	-24(%rbp), %xmm0
	.loc 1 53 15
	subss	-28(%rbp), %xmm0
	.loc 1 53 8
	movss	%xmm0, -16(%rbp)
	.loc 1 54 12
	movss	-20(%rbp), %xmm0
	.loc 1 54 15
	subss	-28(%rbp), %xmm0
	.loc 1 54 8
	movss	%xmm0, -12(%rbp)
	.loc 1 55 9
	movq	-16(%rbp), %rax
	.loc 1 56 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L22
	call	__stack_chk_fail@PLT
.L22:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE516:
	.size	f32x2_sub1, .-f32x2_sub1
	.globl	f32x2_1sub
	.type	f32x2_1sub, @function
f32x2_1sub:
.LFB517:
	.loc 1 59 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movss	%xmm0, -20(%rbp)
	movq	%xmm1, -28(%rbp)
	.loc 1 59 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 61 16
	movss	-28(%rbp), %xmm1
	.loc 1 61 12
	movss	-20(%rbp), %xmm0
	subss	%xmm1, %xmm0
	.loc 1 61 8
	movss	%xmm0, -16(%rbp)
	.loc 1 62 16
	movss	-24(%rbp), %xmm1
	.loc 1 62 12
	movss	-20(%rbp), %xmm0
	subss	%xmm1, %xmm0
	.loc 1 62 8
	movss	%xmm0, -12(%rbp)
	.loc 1 63 9
	movq	-16(%rbp), %rax
	.loc 1 64 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L25
	call	__stack_chk_fail@PLT
.L25:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE517:
	.size	f32x2_1sub, .-f32x2_1sub
	.globl	f32x2_mul
	.type	f32x2_mul, @function
f32x2_mul:
.LFB518:
	.loc 1 67 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	.loc 1 67 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 69 12
	movss	-24(%rbp), %xmm1
	.loc 1 69 19
	movss	-32(%rbp), %xmm0
	.loc 1 69 15
	mulss	%xmm1, %xmm0
	.loc 1 69 8
	movss	%xmm0, -16(%rbp)
	.loc 1 70 12
	movss	-20(%rbp), %xmm1
	.loc 1 70 19
	movss	-28(%rbp), %xmm0
	.loc 1 70 15
	mulss	%xmm1, %xmm0
	.loc 1 70 8
	movss	%xmm0, -12(%rbp)
	.loc 1 71 9
	movq	-16(%rbp), %rax
	.loc 1 72 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L28
	call	__stack_chk_fail@PLT
.L28:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE518:
	.size	f32x2_mul, .-f32x2_mul
	.globl	f32x2_mul1
	.type	f32x2_mul1, @function
f32x2_mul1:
.LFB519:
	.loc 1 74 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	movss	%xmm1, -28(%rbp)
	.loc 1 74 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 76 12
	movss	-24(%rbp), %xmm0
	.loc 1 76 15
	mulss	-28(%rbp), %xmm0
	.loc 1 76 8
	movss	%xmm0, -16(%rbp)
	.loc 1 77 12
	movss	-20(%rbp), %xmm0
	.loc 1 77 15
	mulss	-28(%rbp), %xmm0
	.loc 1 77 8
	movss	%xmm0, -12(%rbp)
	.loc 1 78 9
	movq	-16(%rbp), %rax
	.loc 1 79 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L31
	call	__stack_chk_fail@PLT
.L31:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE519:
	.size	f32x2_mul1, .-f32x2_mul1
	.globl	f32x2_div
	.type	f32x2_div, @function
f32x2_div:
.LFB520:
	.loc 1 82 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	.loc 1 82 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 84 12
	movss	-24(%rbp), %xmm0
	.loc 1 84 19
	movss	-32(%rbp), %xmm1
	.loc 1 84 15
	divss	%xmm1, %xmm0
	.loc 1 84 8
	movss	%xmm0, -16(%rbp)
	.loc 1 85 12
	movss	-20(%rbp), %xmm0
	.loc 1 85 19
	movss	-28(%rbp), %xmm1
	.loc 1 85 15
	divss	%xmm1, %xmm0
	.loc 1 85 8
	movss	%xmm0, -12(%rbp)
	.loc 1 86 9
	movq	-16(%rbp), %rax
	.loc 1 87 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L34
	call	__stack_chk_fail@PLT
.L34:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE520:
	.size	f32x2_div, .-f32x2_div
	.globl	f32x2_div1
	.type	f32x2_div1, @function
f32x2_div1:
.LFB521:
	.loc 1 90 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	movss	%xmm1, -28(%rbp)
	.loc 1 90 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 92 12
	movss	-24(%rbp), %xmm0
	.loc 1 92 15
	divss	-28(%rbp), %xmm0
	.loc 1 92 8
	movss	%xmm0, -16(%rbp)
	.loc 1 93 12
	movss	-20(%rbp), %xmm0
	.loc 1 93 15
	divss	-28(%rbp), %xmm0
	.loc 1 93 8
	movss	%xmm0, -12(%rbp)
	.loc 1 94 9
	movq	-16(%rbp), %rax
	.loc 1 95 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L37
	call	__stack_chk_fail@PLT
.L37:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE521:
	.size	f32x2_div1, .-f32x2_div1
	.globl	f32x2_1div
	.type	f32x2_1div, @function
f32x2_1div:
.LFB522:
	.loc 1 97 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movss	%xmm0, -20(%rbp)
	movq	%xmm1, -28(%rbp)
	.loc 1 97 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 99 16
	movss	-28(%rbp), %xmm1
	.loc 1 99 12
	movss	-20(%rbp), %xmm0
	divss	%xmm1, %xmm0
	.loc 1 99 8
	movss	%xmm0, -16(%rbp)
	.loc 1 100 16
	movss	-24(%rbp), %xmm1
	.loc 1 100 12
	movss	-20(%rbp), %xmm0
	divss	%xmm1, %xmm0
	.loc 1 100 8
	movss	%xmm0, -12(%rbp)
	.loc 1 101 9
	movq	-16(%rbp), %rax
	.loc 1 102 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L40
	call	__stack_chk_fail@PLT
.L40:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE522:
	.size	f32x2_1div, .-f32x2_1div
	.globl	f32x2_sqrt
	.type	f32x2_sqrt, @function
f32x2_sqrt:
.LFB523:
	.loc 1 105 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	.loc 1 105 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 107 17
	movl	-24(%rbp), %eax
	.loc 1 107 10
	movd	%eax, %xmm0
	call	sqrtf@PLT
	movd	%xmm0, %eax
	.loc 1 107 8 discriminator 1
	movl	%eax, -16(%rbp)
	.loc 1 108 17
	movl	-20(%rbp), %eax
	.loc 1 108 10
	movd	%eax, %xmm0
	call	sqrtf@PLT
	movd	%xmm0, %eax
	.loc 1 108 8 discriminator 1
	movl	%eax, -12(%rbp)
	.loc 1 109 9
	movq	-16(%rbp), %rax
	.loc 1 110 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L43
	call	__stack_chk_fail@PLT
.L43:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE523:
	.size	f32x2_sqrt, .-f32x2_sqrt
	.globl	f32x2_rsqrt
	.type	f32x2_rsqrt, @function
f32x2_rsqrt:
.LFB524:
	.loc 1 113 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	.loc 1 113 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 115 24
	movl	-24(%rbp), %eax
	.loc 1 115 17
	movd	%eax, %xmm0
	call	sqrtf@PLT
	movaps	%xmm0, %xmm1
	.loc 1 115 15 discriminator 1
	movss	.LC0(%rip), %xmm0
	divss	%xmm1, %xmm0
	.loc 1 115 8 discriminator 1
	movss	%xmm0, -16(%rbp)
	.loc 1 116 24
	movl	-20(%rbp), %eax
	.loc 1 116 17
	movd	%eax, %xmm0
	call	sqrtf@PLT
	movaps	%xmm0, %xmm1
	.loc 1 116 15 discriminator 1
	movss	.LC0(%rip), %xmm0
	divss	%xmm1, %xmm0
	.loc 1 116 8 discriminator 1
	movss	%xmm0, -12(%rbp)
	.loc 1 117 9
	movq	-16(%rbp), %rax
	.loc 1 118 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L46
	call	__stack_chk_fail@PLT
.L46:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE524:
	.size	f32x2_rsqrt, .-f32x2_rsqrt
	.globl	f32x2_abs
	.type	f32x2_abs, @function
f32x2_abs:
.LFB525:
	.loc 1 121 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	.loc 1 121 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 123 17
	movss	-24(%rbp), %xmm0
	.loc 1 123 10
	movss	.LC1(%rip), %xmm1
	andps	%xmm1, %xmm0
	.loc 1 123 8
	movss	%xmm0, -16(%rbp)
	.loc 1 124 17
	movss	-20(%rbp), %xmm0
	.loc 1 124 10
	movss	.LC1(%rip), %xmm1
	andps	%xmm1, %xmm0
	.loc 1 124 8
	movss	%xmm0, -12(%rbp)
	.loc 1 125 9
	movq	-16(%rbp), %rax
	.loc 1 126 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L49
	call	__stack_chk_fail@PLT
.L49:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE525:
	.size	f32x2_abs, .-f32x2_abs
	.globl	f32x2_length_squared
	.type	f32x2_length_squared, @function
f32x2_length_squared:
.LFB526:
	.loc 1 129 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%xmm0, -24(%rbp)
	.loc 1 130 13
	movss	-24(%rbp), %xmm1
	.loc 1 130 19
	movss	-24(%rbp), %xmm0
	.loc 1 130 16
	mulss	%xmm0, %xmm1
	.loc 1 130 25
	movss	-20(%rbp), %xmm2
	.loc 1 130 31
	movss	-20(%rbp), %xmm0
	.loc 1 130 28
	mulss	%xmm2, %xmm0
	.loc 1 130 6
	addss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	.loc 1 131 9
	movss	-4(%rbp), %xmm0
	.loc 1 132 1
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE526:
	.size	f32x2_length_squared, .-f32x2_length_squared
	.globl	f32x2_length
	.type	f32x2_length, @function
f32x2_length:
.LFB527:
	.loc 1 135 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	.loc 1 136 18
	movq	-24(%rbp), %rax
	movq	%rax, %xmm0
	call	f32x2_length_squared
	movd	%xmm0, %eax
	.loc 1 136 12 discriminator 1
	movd	%eax, %xmm0
	call	sqrtf@PLT
	movd	%xmm0, %eax
	movl	%eax, -4(%rbp)
	.loc 1 137 9
	movss	-4(%rbp), %xmm0
	.loc 1 138 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE527:
	.size	f32x2_length, .-f32x2_length
	.globl	f32x2_unit
	.type	f32x2_unit, @function
f32x2_unit:
.LFB528:
	.loc 1 141 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%xmm0, -40(%rbp)
	.loc 1 141 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 142 15
	movq	-40(%rbp), %rax
	movq	%rax, %xmm0
	call	f32x2_length
	movd	%xmm0, %eax
	.loc 1 142 15 is_stmt 0 discriminator 1
	movd	%eax, %xmm0
	call	f32x2_set1
	movq	%xmm0, %rax
	movq	%rax, -24(%rbp)
	.loc 1 143 14 is_stmt 1
	movq	-24(%rbp), %xmm0
	movq	-40(%rbp), %rax
	movdqa	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	f32x2_div
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	.loc 1 144 9
	movq	-16(%rbp), %rax
	.loc 1 145 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L56
	call	__stack_chk_fail@PLT
.L56:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE528:
	.size	f32x2_unit, .-f32x2_unit
	.globl	f32x2_distance
	.type	f32x2_distance, @function
f32x2_distance:
.LFB529:
	.loc 1 148 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%xmm0, -40(%rbp)
	movq	%xmm1, -48(%rbp)
	.loc 1 148 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 149 14
	movq	-40(%rbp), %xmm0
	movq	-48(%rbp), %rax
	movdqa	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	f32x2_sub
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	.loc 1 150 12
	movq	-16(%rbp), %rax
	movq	%rax, %xmm0
	call	f32x2_length
	movd	%xmm0, %eax
	movl	%eax, -20(%rbp)
	.loc 1 151 9
	movss	-20(%rbp), %xmm0
	.loc 1 152 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L59
	call	__stack_chk_fail@PLT
.L59:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE529:
	.size	f32x2_distance, .-f32x2_distance
	.globl	f32_lerp
	.type	f32_lerp, @function
f32_lerp:
.LFB530:
	.loc 1 155 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	%xmm0, -4(%rbp)
	movss	%xmm1, -8(%rbp)
	movss	%xmm2, -12(%rbp)
	.loc 1 156 11
	movss	-8(%rbp), %xmm0
	subss	-4(%rbp), %xmm0
	.loc 1 156 14
	mulss	-12(%rbp), %xmm0
	.loc 1 156 16
	addss	-4(%rbp), %xmm0
	.loc 1 157 1
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE530:
	.size	f32_lerp, .-f32_lerp
	.globl	f32x2_lerp
	.type	f32x2_lerp, @function
f32x2_lerp:
.LFB531:
	.loc 1 160 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	movss	%xmm2, -36(%rbp)
	.loc 1 160 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 162 10
	movss	-32(%rbp), %xmm0
	movl	-24(%rbp), %eax
	movss	-36(%rbp), %xmm1
	movaps	%xmm1, %xmm2
	movaps	%xmm0, %xmm1
	movd	%eax, %xmm0
	call	f32_lerp
	movd	%xmm0, %eax
	.loc 1 162 8 discriminator 1
	movl	%eax, -16(%rbp)
	.loc 1 163 10
	movss	-28(%rbp), %xmm0
	movl	-20(%rbp), %eax
	movss	-36(%rbp), %xmm1
	movaps	%xmm1, %xmm2
	movaps	%xmm0, %xmm1
	movd	%eax, %xmm0
	call	f32_lerp
	movd	%xmm0, %eax
	.loc 1 163 8 discriminator 1
	movl	%eax, -12(%rbp)
	.loc 1 164 9
	movq	-16(%rbp), %rax
	.loc 1 165 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L64
	call	__stack_chk_fail@PLT
.L64:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE531:
	.size	f32x2_lerp, .-f32x2_lerp
	.globl	f32x2_angle
	.type	f32x2_angle, @function
f32x2_angle:
.LFB532:
	.loc 1 168 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	.loc 1 169 25
	movss	-24(%rbp), %xmm0
	.loc 1 169 20
	movl	-20(%rbp), %eax
	.loc 1 169 12
	movaps	%xmm0, %xmm1
	movd	%eax, %xmm0
	call	atan2f@PLT
	movd	%xmm0, %eax
	movl	%eax, -4(%rbp)
	.loc 1 170 9
	movss	-4(%rbp), %xmm0
	.loc 1 171 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE532:
	.size	f32x2_angle, .-f32x2_angle
	.globl	f32x2_trunc
	.type	f32x2_trunc, @function
f32x2_trunc:
.LFB533:
	.loc 1 174 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%xmm0, -40(%rbp)
	movss	%xmm1, -44(%rbp)
	.loc 1 174 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 175 15
	movq	-40(%rbp), %rax
	movq	%rax, %xmm0
	call	f32x2_length_squared
	movd	%xmm0, %eax
	movl	%eax, -28(%rbp)
	.loc 1 176 22
	movss	-44(%rbp), %xmm0
	mulss	%xmm0, %xmm0
	.loc 1 176 4
	comiss	-28(%rbp), %xmm0
	jb	.L74
	.loc 1 177 10
	movq	-40(%rbp), %rax
	jmp	.L71
.L74:
	.loc 1 178 12
	movl	-28(%rbp), %eax
	movd	%eax, %xmm0
	call	sqrtf@PLT
	movd	%xmm0, %eax
	movl	%eax, -24(%rbp)
	.loc 1 179 6
	movss	-44(%rbp), %xmm0
	divss	-24(%rbp), %xmm0
	movss	%xmm0, -20(%rbp)
	.loc 1 180 14
	movss	-20(%rbp), %xmm0
	movq	-40(%rbp), %rax
	movaps	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	f32x2_mul1
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	.loc 1 181 9
	movq	-16(%rbp), %rax
.L71:
	.loc 1 182 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L72
	call	__stack_chk_fail@PLT
.L72:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE533:
	.size	f32x2_trunc, .-f32x2_trunc
	.globl	f32x2_dot
	.type	f32x2_dot, @function
f32x2_dot:
.LFB534:
	.loc 1 185 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	.loc 1 186 14
	movss	-24(%rbp), %xmm1
	.loc 1 186 21
	movss	-32(%rbp), %xmm0
	.loc 1 186 17
	mulss	%xmm0, %xmm1
	.loc 1 186 28
	movss	-20(%rbp), %xmm2
	.loc 1 186 35
	movss	-28(%rbp), %xmm0
	.loc 1 186 31
	mulss	%xmm2, %xmm0
	.loc 1 186 6
	addss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	.loc 1 187 9
	movss	-4(%rbp), %xmm0
	.loc 1 188 1
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE534:
	.size	f32x2_dot, .-f32x2_dot
	.globl	f32x2_cross
	.type	f32x2_cross, @function
f32x2_cross:
.LFB535:
	.loc 1 191 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	.loc 1 192 14
	movss	-24(%rbp), %xmm1
	.loc 1 192 21
	movss	-28(%rbp), %xmm0
	.loc 1 192 17
	mulss	%xmm1, %xmm0
	.loc 1 192 28
	movss	-20(%rbp), %xmm2
	.loc 1 192 35
	movss	-32(%rbp), %xmm1
	.loc 1 192 31
	mulss	%xmm2, %xmm1
	.loc 1 192 6
	subss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	.loc 1 193 9
	movss	-4(%rbp), %xmm0
	.loc 1 194 1
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE535:
	.size	f32x2_cross, .-f32x2_cross
	.globl	f32x2_perp_cw
	.type	f32x2_perp_cw, @function
f32x2_perp_cw:
.LFB536:
	.loc 1 197 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	.loc 1 197 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 199 12
	movss	-20(%rbp), %xmm0
	.loc 1 199 10
	movss	.LC2(%rip), %xmm1
	xorps	%xmm1, %xmm0
	.loc 1 199 8
	movss	%xmm0, -16(%rbp)
	.loc 1 200 11
	movss	-24(%rbp), %xmm0
	.loc 1 200 8
	movss	%xmm0, -12(%rbp)
	.loc 1 201 9
	movq	-16(%rbp), %rax
	.loc 1 202 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L81
	call	__stack_chk_fail@PLT
.L81:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE536:
	.size	f32x2_perp_cw, .-f32x2_perp_cw
	.globl	f32x2_perp_ccw
	.type	f32x2_perp_ccw, @function
f32x2_perp_ccw:
.LFB537:
	.loc 1 204 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	.loc 1 204 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 206 11
	movss	-20(%rbp), %xmm0
	.loc 1 206 8
	movss	%xmm0, -16(%rbp)
	.loc 1 207 12
	movss	-24(%rbp), %xmm0
	.loc 1 207 10
	movss	.LC2(%rip), %xmm1
	xorps	%xmm1, %xmm0
	.loc 1 207 8
	movss	%xmm0, -12(%rbp)
	.loc 1 208 9
	movq	-16(%rbp), %rax
	.loc 1 209 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L84
	call	__stack_chk_fail@PLT
.L84:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE537:
	.size	f32x2_perp_ccw, .-f32x2_perp_ccw
	.globl	f32x2_unit_perp
	.type	f32x2_unit_perp, @function
f32x2_unit_perp:
.LFB538:
	.loc 1 212 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, -24(%rbp)
	.loc 1 212 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 214 8
	movq	-24(%rbp), %rax
	movq	%rax, %xmm0
	call	f32x2_unit
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	.loc 1 215 8
	movq	-16(%rbp), %rax
	movq	%rax, %xmm0
	call	f32x2_perp_ccw
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	.loc 1 216 9
	movq	-16(%rbp), %rax
	.loc 1 217 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L87
	call	__stack_chk_fail@PLT
.L87:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE538:
	.size	f32x2_unit_perp, .-f32x2_unit_perp
	.globl	f32x2_reflect
	.type	f32x2_reflect, @function
f32x2_reflect:
.LFB539:
	.loc 1 220 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%xmm0, -40(%rbp)
	movq	%xmm1, -48(%rbp)
	.loc 1 220 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 221 12
	movq	-48(%rbp), %xmm0
	movq	-40(%rbp), %rax
	movdqa	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	f32x2_dot
	movd	%xmm0, %eax
	movl	%eax, -20(%rbp)
	.loc 1 223 18
	movss	-40(%rbp), %xmm1
	.loc 1 223 28
	movss	-20(%rbp), %xmm0
	movaps	%xmm0, %xmm2
	addss	%xmm0, %xmm2
	.loc 1 223 42
	movss	-48(%rbp), %xmm0
	.loc 1 223 34
	mulss	%xmm0, %xmm2
	.loc 1 223 21
	subss	%xmm2, %xmm1
	movaps	%xmm1, %xmm0
	.loc 1 223 8
	movss	%xmm0, -16(%rbp)
	.loc 1 224 18
	movss	-36(%rbp), %xmm1
	.loc 1 224 28
	movss	-20(%rbp), %xmm0
	movaps	%xmm0, %xmm2
	addss	%xmm0, %xmm2
	.loc 1 224 42
	movss	-44(%rbp), %xmm0
	.loc 1 224 34
	mulss	%xmm0, %xmm2
	.loc 1 224 21
	subss	%xmm2, %xmm1
	movaps	%xmm1, %xmm0
	.loc 1 224 8
	movss	%xmm0, -12(%rbp)
	.loc 1 225 9
	movq	-16(%rbp), %rax
	.loc 1 226 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L90
	call	__stack_chk_fail@PLT
.L90:
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE539:
	.size	f32x2_reflect, .-f32x2_reflect
	.globl	f64x2_set1
	.type	f64x2_set1, @function
f64x2_set1:
.LFB540:
	.file 2 "f64x2.c"
	.loc 2 3 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movsd	%xmm0, -56(%rbp)
	.loc 2 3 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movsd	-56(%rbp), %xmm0
	movsd	%xmm0, -40(%rbp)
.LBB40:
.LBB41:
	.file 3 "/usr/lib/gcc/x86_64-pc-linux-gnu/15.2.1/include/emmintrin.h"
	.loc 3 76 10
	movsd	-40(%rbp), %xmm0
	unpcklpd	%xmm0, %xmm0
.LBE41:
.LBE40:
	.loc 2 6 6 discriminator 1
	movaps	%xmm0, -32(%rbp)
	.loc 2 10 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 11 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L94
	call	__stack_chk_fail@PLT
.L94:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE540:
	.size	f64x2_set1, .-f64x2_set1
	.globl	f64x2_set
	.type	f64x2_set, @function
f64x2_set:
.LFB541:
	.loc 2 14 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movsd	%xmm0, -56(%rbp)
	movsd	%xmm1, -64(%rbp)
	.loc 2 14 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movsd	-64(%rbp), %xmm0
	movsd	%xmm0, -48(%rbp)
	movsd	-56(%rbp), %xmm0
	movsd	%xmm0, -40(%rbp)
.LBB42:
.LBB43:
	.loc 3 89 10
	movsd	-48(%rbp), %xmm1
	movsd	-40(%rbp), %xmm0
	unpcklpd	%xmm1, %xmm0
.LBE43:
.LBE42:
	.loc 2 17 6 discriminator 1
	movaps	%xmm0, -32(%rbp)
	.loc 2 21 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 22 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L98
	call	__stack_chk_fail@PLT
.L98:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE541:
	.size	f64x2_set, .-f64x2_set
	.globl	f64x2_load
	.type	f64x2_load, @function
f64x2_load:
.LFB542:
	.loc 2 25 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	.loc 2 25 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-56(%rbp), %rax
	movq	%rax, -40(%rbp)
.LBB44:
.LBB45:
	.loc 3 128 10
	movq	-40(%rbp), %rax
	movapd	(%rax), %xmm0
.LBE45:
.LBE44:
	.loc 2 28 8 discriminator 1
	movaps	%xmm0, -32(%rbp)
	.loc 2 32 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 33 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L102
	call	__stack_chk_fail@PLT
.L102:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE542:
	.size	f64x2_load, .-f64x2_load
	.globl	f64x2_scatter
	.type	f64x2_scatter, @function
f64x2_scatter:
.LFB543:
	.loc 2 36 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	.loc 2 37 8
	movsd	-32(%rbp), %xmm0
	.loc 2 37 5
	movq	-8(%rbp), %rax
	movsd	%xmm0, (%rax)
	.loc 2 38 8
	movsd	-24(%rbp), %xmm0
	.loc 2 38 5
	movq	-16(%rbp), %rax
	movsd	%xmm0, (%rax)
	.loc 2 39 1
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE543:
	.size	f64x2_scatter, .-f64x2_scatter
	.globl	f64x2_add
	.type	f64x2_add, @function
f64x2_add:
.LFB544:
	.loc 2 42 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movq	%xmm2, %rax
	movdqa	%xmm3, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	.loc 2 42 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 45 10
	movapd	-96(%rbp), %xmm0
	movapd	-80(%rbp), %xmm1
	movaps	%xmm1, -64(%rbp)
	movaps	%xmm0, -48(%rbp)
.LBB46:
.LBB47:
	.loc 3 252 10
	movapd	-64(%rbp), %xmm0
	addpd	-48(%rbp), %xmm0
.LBE47:
.LBE46:
	.loc 2 45 8 discriminator 1
	movaps	%xmm0, -32(%rbp)
	.loc 2 50 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 51 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L107
	call	__stack_chk_fail@PLT
.L107:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE544:
	.size	f64x2_add, .-f64x2_add
	.globl	f64x2_add1
	.type	f64x2_add1, @function
f64x2_add1:
.LFB545:
	.loc 2 53 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movsd	%xmm2, -88(%rbp)
	.loc 2 53 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 56 27
	movq	-88(%rbp), %rax
	movq	%rax, %xmm0
	call	f64x2_set1
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	.loc 2 56 10 discriminator 1
	movq	%rax, %xmm0
	movq	%rdx, %xmm1
	punpcklqdq	%xmm1, %xmm0
	movapd	%xmm0, %xmm1
	movapd	-80(%rbp), %xmm0
	movaps	%xmm0, -64(%rbp)
	movaps	%xmm1, -48(%rbp)
.LBB48:
.LBB49:
	.loc 3 252 10
	movapd	-64(%rbp), %xmm0
	addpd	-48(%rbp), %xmm0
.LBE49:
.LBE48:
	.loc 2 56 8 discriminator 2
	movaps	%xmm0, -32(%rbp)
	.loc 2 61 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 62 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L111
	call	__stack_chk_fail@PLT
.L111:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE545:
	.size	f64x2_add1, .-f64x2_add1
	.globl	f64x2_sub
	.type	f64x2_sub, @function
f64x2_sub:
.LFB546:
	.loc 2 65 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movq	%xmm2, %rax
	movdqa	%xmm3, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	.loc 2 65 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 68 10
	movapd	-96(%rbp), %xmm0
	movapd	-80(%rbp), %xmm1
	movaps	%xmm1, -64(%rbp)
	movaps	%xmm0, -48(%rbp)
.LBB50:
.LBB51:
	.loc 3 264 10
	movapd	-64(%rbp), %xmm0
	subpd	-48(%rbp), %xmm0
.LBE51:
.LBE50:
	.loc 2 68 8 discriminator 1
	movaps	%xmm0, -32(%rbp)
	.loc 2 73 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 74 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L115
	call	__stack_chk_fail@PLT
.L115:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE546:
	.size	f64x2_sub, .-f64x2_sub
	.globl	f64x2_sub1
	.type	f64x2_sub1, @function
f64x2_sub1:
.LFB547:
	.loc 2 76 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movsd	%xmm2, -88(%rbp)
	.loc 2 76 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 79 27
	movq	-88(%rbp), %rax
	movq	%rax, %xmm0
	call	f64x2_set1
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	.loc 2 79 10 discriminator 1
	movq	%rax, %xmm0
	movq	%rdx, %xmm1
	punpcklqdq	%xmm1, %xmm0
	movapd	%xmm0, %xmm1
	movapd	-80(%rbp), %xmm0
	movaps	%xmm0, -64(%rbp)
	movaps	%xmm1, -48(%rbp)
.LBB52:
.LBB53:
	.loc 3 264 10
	movapd	-64(%rbp), %xmm0
	subpd	-48(%rbp), %xmm0
.LBE53:
.LBE52:
	.loc 2 79 8 discriminator 2
	movaps	%xmm0, -32(%rbp)
	.loc 2 84 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 85 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L119
	call	__stack_chk_fail@PLT
.L119:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE547:
	.size	f64x2_sub1, .-f64x2_sub1
	.globl	f64x2_1sub
	.type	f64x2_1sub, @function
f64x2_1sub:
.LFB548:
	.loc 2 88 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movsd	%xmm0, -72(%rbp)
	movq	%xmm1, %rax
	movdqa	%xmm2, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	.loc 2 88 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 91 10
	movapd	-96(%rbp), %xmm3
	movaps	%xmm3, -112(%rbp)
	.loc 2 91 21
	movq	-72(%rbp), %rax
	movq	%rax, %xmm0
	call	f64x2_set1
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	.loc 2 91 10 discriminator 1
	movq	%rax, %xmm0
	movq	%rdx, %xmm1
	punpcklqdq	%xmm1, %xmm0
	movaps	%xmm0, -64(%rbp)
	movapd	-112(%rbp), %xmm3
	movaps	%xmm3, -48(%rbp)
.LBB54:
.LBB55:
	.loc 3 264 10
	movapd	-64(%rbp), %xmm0
	subpd	-48(%rbp), %xmm0
.LBE55:
.LBE54:
	.loc 2 91 8 discriminator 2
	movaps	%xmm0, -32(%rbp)
	.loc 2 96 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 97 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L123
	call	__stack_chk_fail@PLT
.L123:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE548:
	.size	f64x2_1sub, .-f64x2_1sub
	.globl	f64x2_mul
	.type	f64x2_mul, @function
f64x2_mul:
.LFB549:
	.loc 2 100 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movq	%xmm2, %rax
	movdqa	%xmm3, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	.loc 2 100 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 103 10
	movapd	-96(%rbp), %xmm0
	movapd	-80(%rbp), %xmm1
	movaps	%xmm1, -64(%rbp)
	movaps	%xmm0, -48(%rbp)
.LBB56:
.LBB57:
	.loc 3 276 10
	movapd	-64(%rbp), %xmm0
	mulpd	-48(%rbp), %xmm0
.LBE57:
.LBE56:
	.loc 2 103 8 discriminator 1
	movaps	%xmm0, -32(%rbp)
	.loc 2 108 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 109 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L127
	call	__stack_chk_fail@PLT
.L127:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE549:
	.size	f64x2_mul, .-f64x2_mul
	.globl	f64x2_mul1
	.type	f64x2_mul1, @function
f64x2_mul1:
.LFB550:
	.loc 2 111 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movsd	%xmm2, -88(%rbp)
	.loc 2 111 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 114 27
	movq	-88(%rbp), %rax
	movq	%rax, %xmm0
	call	f64x2_set1
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	.loc 2 114 10 discriminator 1
	movq	%rax, %xmm0
	movq	%rdx, %xmm1
	punpcklqdq	%xmm1, %xmm0
	movapd	%xmm0, %xmm1
	movapd	-80(%rbp), %xmm0
	movaps	%xmm0, -64(%rbp)
	movaps	%xmm1, -48(%rbp)
.LBB58:
.LBB59:
	.loc 3 276 10
	movapd	-64(%rbp), %xmm0
	mulpd	-48(%rbp), %xmm0
.LBE59:
.LBE58:
	.loc 2 114 8 discriminator 2
	movaps	%xmm0, -32(%rbp)
	.loc 2 119 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 120 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L131
	call	__stack_chk_fail@PLT
.L131:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE550:
	.size	f64x2_mul1, .-f64x2_mul1
	.globl	f64x2_div
	.type	f64x2_div, @function
f64x2_div:
.LFB551:
	.loc 2 123 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movq	%xmm2, %rax
	movdqa	%xmm3, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	.loc 2 123 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 126 10
	movapd	-96(%rbp), %xmm0
	movapd	-80(%rbp), %xmm1
	movaps	%xmm1, -64(%rbp)
	movaps	%xmm0, -48(%rbp)
.LBB60:
.LBB61:
	.loc 3 288 10
	movapd	-64(%rbp), %xmm0
	divpd	-48(%rbp), %xmm0
.LBE61:
.LBE60:
	.loc 2 126 8 discriminator 1
	movaps	%xmm0, -32(%rbp)
	.loc 2 131 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 132 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L135
	call	__stack_chk_fail@PLT
.L135:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE551:
	.size	f64x2_div, .-f64x2_div
	.globl	f64x2_div1
	.type	f64x2_div1, @function
f64x2_div1:
.LFB552:
	.loc 2 135 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movsd	%xmm2, -88(%rbp)
	.loc 2 135 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 138 27
	movq	-88(%rbp), %rax
	movq	%rax, %xmm0
	call	f64x2_set1
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	.loc 2 138 10 discriminator 1
	movq	%rax, %xmm0
	movq	%rdx, %xmm1
	punpcklqdq	%xmm1, %xmm0
	movapd	%xmm0, %xmm1
	movapd	-80(%rbp), %xmm0
	movaps	%xmm0, -64(%rbp)
	movaps	%xmm1, -48(%rbp)
.LBB62:
.LBB63:
	.loc 3 288 10
	movapd	-64(%rbp), %xmm0
	divpd	-48(%rbp), %xmm0
.LBE63:
.LBE62:
	.loc 2 138 8 discriminator 2
	movaps	%xmm0, -32(%rbp)
	.loc 2 143 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 144 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L139
	call	__stack_chk_fail@PLT
.L139:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE552:
	.size	f64x2_div1, .-f64x2_div1
	.globl	f64x2_1div
	.type	f64x2_1div, @function
f64x2_1div:
.LFB553:
	.loc 2 146 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movsd	%xmm0, -72(%rbp)
	movq	%xmm1, %rax
	movdqa	%xmm2, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	.loc 2 146 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 149 10
	movapd	-96(%rbp), %xmm3
	movaps	%xmm3, -112(%rbp)
	.loc 2 149 21
	movq	-72(%rbp), %rax
	movq	%rax, %xmm0
	call	f64x2_set1
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	.loc 2 149 10 discriminator 1
	movq	%rax, %xmm0
	movq	%rdx, %xmm1
	punpcklqdq	%xmm1, %xmm0
	movaps	%xmm0, -64(%rbp)
	movapd	-112(%rbp), %xmm3
	movaps	%xmm3, -48(%rbp)
.LBB64:
.LBB65:
	.loc 3 288 10
	movapd	-64(%rbp), %xmm0
	divpd	-48(%rbp), %xmm0
.LBE65:
.LBE64:
	.loc 2 149 8 discriminator 2
	movaps	%xmm0, -32(%rbp)
	.loc 2 154 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 155 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L143
	call	__stack_chk_fail@PLT
.L143:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE553:
	.size	f64x2_1div, .-f64x2_1div
	.globl	f64x2_sqrt
	.type	f64x2_sqrt, @function
f64x2_sqrt:
.LFB554:
	.loc 2 158 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	.loc 2 158 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 161 10
	movapd	-64(%rbp), %xmm0
	movaps	%xmm0, -48(%rbp)
.LBB66:
.LBB67:
	.loc 3 300 19
	sqrtpd	-48(%rbp), %xmm0
	.loc 3 300 10
	nop
.LBE67:
.LBE66:
	.loc 2 161 8 discriminator 1
	movaps	%xmm0, -32(%rbp)
	.loc 2 166 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 167 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L147
	call	__stack_chk_fail@PLT
.L147:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE554:
	.size	f64x2_sqrt, .-f64x2_sqrt
	.globl	f64x2_rsqrt
	.type	f64x2_rsqrt, @function
f64x2_rsqrt:
.LFB555:
	.loc 2 170 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -112(%rbp)
	movq	%rdx, -104(%rbp)
	.loc 2 170 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 173 10
	movapd	-112(%rbp), %xmm0
	movaps	%xmm0, -48(%rbp)
.LBB68:
.LBB69:
	.loc 3 300 19
	sqrtpd	-48(%rbp), %xmm0
	.loc 3 300 10
	nop
	movsd	.LC3(%rip), %xmm1
	movsd	%xmm1, -88(%rbp)
.LBE69:
.LBE68:
.LBB70:
.LBB71:
	.loc 3 76 10
	movsd	-88(%rbp), %xmm1
	unpcklpd	%xmm1, %xmm1
	movaps	%xmm1, -80(%rbp)
	movaps	%xmm0, -64(%rbp)
.LBE71:
.LBE70:
.LBB72:
.LBB73:
	.loc 3 288 10
	movapd	-80(%rbp), %xmm0
	divpd	-64(%rbp), %xmm0
.LBE73:
.LBE72:
	.loc 2 173 8 discriminator 3
	movaps	%xmm0, -32(%rbp)
	.loc 2 178 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 179 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L153
	call	__stack_chk_fail@PLT
.L153:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE555:
	.size	f64x2_rsqrt, .-f64x2_rsqrt
	.globl	f64x2_abs
	.type	f64x2_abs, @function
f64x2_abs:
.LFB556:
	.loc 2 182 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 2 182 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 185 16
	movsd	-48(%rbp), %xmm0
	.loc 2 185 10
	movq	.LC4(%rip), %xmm1
	andpd	%xmm1, %xmm0
	.loc 2 185 8
	movsd	%xmm0, -32(%rbp)
	.loc 2 186 16
	movsd	-40(%rbp), %xmm0
	.loc 2 186 10
	movq	.LC4(%rip), %xmm1
	andpd	%xmm1, %xmm0
	.loc 2 186 8
	movsd	%xmm0, -24(%rbp)
	.loc 2 187 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 188 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L156
	call	__stack_chk_fail@PLT
.L156:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE556:
	.size	f64x2_abs, .-f64x2_abs
	.globl	f64x2_length_squared
	.type	f64x2_length_squared, @function
f64x2_length_squared:
.LFB557:
	.loc 2 191 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	.loc 2 193 8
	movapd	-64(%rbp), %xmm0
	movapd	-64(%rbp), %xmm1
	movaps	%xmm1, -32(%rbp)
	movaps	%xmm0, -16(%rbp)
.LBB74:
.LBB75:
	.loc 3 276 10
	movapd	-32(%rbp), %xmm0
	mulpd	-16(%rbp), %xmm0
.LBE75:
.LBE74:
	.loc 2 193 6 discriminator 1
	movaps	%xmm0, -64(%rbp)
	.loc 2 194 13
	movsd	-64(%rbp), %xmm1
	.loc 2 194 19
	movsd	-56(%rbp), %xmm0
	.loc 2 194 6
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -40(%rbp)
	.loc 2 198 9
	movsd	-40(%rbp), %xmm0
	.loc 2 199 1
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE557:
	.size	f64x2_length_squared, .-f64x2_length_squared
	.globl	f64x2_length
	.type	f64x2_length, @function
f64x2_length:
.LFB558:
	.loc 2 202 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	.loc 2 204 8
	movapd	-64(%rbp), %xmm0
	movapd	-64(%rbp), %xmm1
	movaps	%xmm1, -32(%rbp)
	movaps	%xmm0, -16(%rbp)
.LBB76:
.LBB77:
	.loc 3 276 10
	movapd	-32(%rbp), %xmm0
	mulpd	-16(%rbp), %xmm0
.LBE77:
.LBE76:
	.loc 2 204 6 discriminator 1
	movaps	%xmm0, -64(%rbp)
	.loc 2 205 18
	movsd	-64(%rbp), %xmm1
	.loc 2 205 24
	movsd	-56(%rbp), %xmm0
	.loc 2 205 21
	addsd	%xmm0, %xmm1
	movq	%xmm1, %rax
	.loc 2 205 12
	movq	%rax, %xmm0
	call	sqrt@PLT
	movq	%xmm0, %rax
	movq	%rax, -40(%rbp)
	.loc 2 209 9
	movsd	-40(%rbp), %xmm0
	.loc 2 210 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE558:
	.size	f64x2_length, .-f64x2_length
	.globl	f64x2_unit
	.type	f64x2_unit, @function
f64x2_unit:
.LFB559:
	.loc 2 213 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	.loc 2 213 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 214 15
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %xmm1
	movq	%rax, %xmm0
	call	f64x2_length
	movq	%xmm0, %rax
	.loc 2 214 15 is_stmt 0 discriminator 1
	movq	%rax, %xmm0
	call	f64x2_set1
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -48(%rbp)
	movq	%xmm0, -40(%rbp)
	.loc 2 215 14 is_stmt 1
	movq	-48(%rbp), %xmm2
	movq	-40(%rbp), %xmm0
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %xmm1
	movdqa	%xmm0, %xmm3
	movq	%rax, %xmm0
	call	f64x2_div
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -32(%rbp)
	movq	%xmm0, -24(%rbp)
	.loc 2 216 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 217 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L165
	call	__stack_chk_fail@PLT
.L165:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE559:
	.size	f64x2_unit, .-f64x2_unit
	.globl	f64x2_distance
	.type	f64x2_distance, @function
f64x2_distance:
.LFB560:
	.loc 2 220 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%xmm2, %rax
	movdqa	%xmm3, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	.loc 2 220 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 221 14
	movq	-64(%rbp), %xmm2
	movq	-56(%rbp), %xmm0
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %xmm1
	movdqa	%xmm0, %xmm3
	movq	%rax, %xmm0
	call	f64x2_sub
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -32(%rbp)
	movq	%xmm0, -24(%rbp)
	.loc 2 222 12
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %xmm1
	movq	%rax, %xmm0
	call	f64x2_length
	movq	%xmm0, %rax
	movq	%rax, -40(%rbp)
	.loc 2 223 9
	movsd	-40(%rbp), %xmm0
	.loc 2 224 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L168
	call	__stack_chk_fail@PLT
.L168:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE560:
	.size	f64x2_distance, .-f64x2_distance
	.globl	f64_lerp
	.type	f64_lerp, @function
f64_lerp:
.LFB561:
	.loc 2 227 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movsd	%xmm0, -8(%rbp)
	movsd	%xmm1, -16(%rbp)
	movsd	%xmm2, -24(%rbp)
	.loc 2 228 11
	movsd	-16(%rbp), %xmm0
	subsd	-8(%rbp), %xmm0
	.loc 2 228 14
	mulsd	-24(%rbp), %xmm0
	.loc 2 228 16
	addsd	-8(%rbp), %xmm0
	.loc 2 229 1
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE561:
	.size	f64_lerp, .-f64_lerp
	.globl	f64x2_lerp
	.type	f64x2_lerp, @function
f64x2_lerp:
.LFB562:
	.loc 2 232 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%xmm2, %rax
	movdqa	%xmm3, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movsd	%xmm4, -72(%rbp)
	.loc 2 232 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 235 7
	movq	-48(%rbp), %xmm2
	movq	-40(%rbp), %xmm0
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %xmm1
	movdqa	%xmm0, %xmm3
	movq	%rax, %xmm0
	call	f64x2_sub
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -64(%rbp)
	movq	%xmm0, -56(%rbp)
	.loc 2 236 7
	movsd	-72(%rbp), %xmm0
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %xmm1
	movapd	%xmm0, %xmm2
	movq	%rax, %xmm0
	call	f64x2_mul1
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -64(%rbp)
	movq	%xmm0, -56(%rbp)
	.loc 2 237 8
	movq	-64(%rbp), %xmm2
	movq	-56(%rbp), %xmm0
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %xmm1
	movdqa	%xmm0, %xmm3
	movq	%rax, %xmm0
	call	f64x2_add
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -32(%rbp)
	movq	%xmm0, -24(%rbp)
	.loc 2 242 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 243 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L173
	call	__stack_chk_fail@PLT
.L173:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE562:
	.size	f64x2_lerp, .-f64x2_lerp
	.globl	f64x2_angle
	.type	f64x2_angle, @function
f64x2_angle:
.LFB563:
	.loc 2 246 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	.loc 2 247 24
	movsd	-32(%rbp), %xmm0
	.loc 2 247 19
	movq	-24(%rbp), %rax
	.loc 2 247 12
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	atan2@PLT
	movq	%xmm0, %rax
	movq	%rax, -8(%rbp)
	.loc 2 248 9
	movsd	-8(%rbp), %xmm0
	.loc 2 249 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE563:
	.size	f64x2_angle, .-f64x2_angle
	.globl	f64x2_trunc
	.type	f64x2_trunc, @function
f64x2_trunc:
.LFB564:
	.loc 2 252 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movsd	%xmm2, -88(%rbp)
	.loc 2 252 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 253 15
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %xmm1
	movq	%rax, %xmm0
	call	f64x2_length_squared
	movq	%xmm0, %rax
	movq	%rax, -56(%rbp)
	.loc 2 254 22
	movsd	-88(%rbp), %xmm0
	mulsd	%xmm0, %xmm0
	.loc 2 254 4
	comisd	-56(%rbp), %xmm0
	jb	.L183
	.loc 2 255 10
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	jmp	.L180
.L183:
	.loc 2 256 12
	pxor	%xmm3, %xmm3
	cvtsd2ss	-56(%rbp), %xmm3
	movd	%xmm3, %eax
	movd	%eax, %xmm0
	call	sqrtf@PLT
	.loc 2 256 6 discriminator 1
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -48(%rbp)
	.loc 2 257 6
	movsd	-88(%rbp), %xmm0
	divsd	-48(%rbp), %xmm0
	movsd	%xmm0, -40(%rbp)
	.loc 2 258 14
	movsd	-40(%rbp), %xmm0
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %xmm1
	movapd	%xmm0, %xmm2
	movq	%rax, %xmm0
	call	f64x2_mul1
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -32(%rbp)
	movq	%xmm0, -24(%rbp)
	.loc 2 259 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
.L180:
	.loc 2 260 1
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L181
	call	__stack_chk_fail@PLT
.L181:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE564:
	.size	f64x2_trunc, .-f64x2_trunc
	.globl	f64x2_dot
	.type	f64x2_dot, @function
f64x2_dot:
.LFB565:
	.loc 2 263 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%xmm2, %rax
	movdqa	%xmm3, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 2 265 7
	movq	-48(%rbp), %xmm2
	movq	-40(%rbp), %xmm0
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %xmm1
	movdqa	%xmm0, %xmm3
	movq	%rax, %xmm0
	call	f64x2_mul
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -32(%rbp)
	movq	%xmm0, -24(%rbp)
	.loc 2 266 14
	movsd	-32(%rbp), %xmm1
	.loc 2 266 21
	movsd	-24(%rbp), %xmm0
	.loc 2 266 6
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	.loc 2 270 9
	movsd	-8(%rbp), %xmm0
	.loc 2 271 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE565:
	.size	f64x2_dot, .-f64x2_dot
	.globl	f64x2_cross
	.type	f64x2_cross, @function
f64x2_cross:
.LFB566:
	.loc 2 274 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%xmm2, %rax
	movdqa	%xmm3, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 2 275 14
	movsd	-32(%rbp), %xmm1
	.loc 2 275 21
	movsd	-40(%rbp), %xmm0
	.loc 2 275 17
	mulsd	%xmm1, %xmm0
	.loc 2 275 28
	movsd	-24(%rbp), %xmm2
	.loc 2 275 35
	movsd	-48(%rbp), %xmm1
	.loc 2 275 31
	mulsd	%xmm2, %xmm1
	.loc 2 275 6
	subsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	.loc 2 276 9
	movsd	-8(%rbp), %xmm0
	.loc 2 277 1
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE566:
	.size	f64x2_cross, .-f64x2_cross
	.globl	f64x2_perp_cw
	.type	f64x2_perp_cw, @function
f64x2_perp_cw:
.LFB567:
	.loc 2 280 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 2 280 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 282 12
	movsd	-40(%rbp), %xmm0
	.loc 2 282 10
	movq	.LC5(%rip), %xmm1
	xorpd	%xmm1, %xmm0
	.loc 2 282 8
	movsd	%xmm0, -32(%rbp)
	.loc 2 283 11
	movsd	-48(%rbp), %xmm0
	.loc 2 283 8
	movsd	%xmm0, -24(%rbp)
	.loc 2 284 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 285 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L190
	call	__stack_chk_fail@PLT
.L190:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE567:
	.size	f64x2_perp_cw, .-f64x2_perp_cw
	.globl	f64x2_perp_ccw
	.type	f64x2_perp_ccw, @function
f64x2_perp_ccw:
.LFB568:
	.loc 2 287 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 2 287 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 289 11
	movsd	-40(%rbp), %xmm0
	.loc 2 289 8
	movsd	%xmm0, -32(%rbp)
	.loc 2 290 12
	movsd	-48(%rbp), %xmm0
	.loc 2 290 10
	movq	.LC5(%rip), %xmm1
	xorpd	%xmm1, %xmm0
	.loc 2 290 8
	movsd	%xmm0, -24(%rbp)
	.loc 2 291 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 292 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L193
	call	__stack_chk_fail@PLT
.L193:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE568:
	.size	f64x2_perp_ccw, .-f64x2_perp_ccw
	.globl	f64x2_unit_perp
	.type	f64x2_unit_perp, @function
f64x2_unit_perp:
.LFB569:
	.loc 2 295 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 2 295 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 297 8
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %xmm1
	movq	%rax, %xmm0
	call	f64x2_unit
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -32(%rbp)
	movq	%xmm0, -24(%rbp)
	.loc 2 298 8
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %xmm1
	movq	%rax, %xmm0
	call	f64x2_perp_ccw
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -32(%rbp)
	movq	%xmm0, -24(%rbp)
	.loc 2 299 9
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 300 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L196
	call	__stack_chk_fail@PLT
.L196:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE569:
	.size	f64x2_unit_perp, .-f64x2_unit_perp
	.section	.rodata
	.align 8
.LC6:
	.string	"TODO: Test f64x2_reflect for correctness"
	.text
	.globl	f64x2_reflect
	.type	f64x2_reflect, @function
f64x2_reflect:
.LFB570:
	.loc 2 303 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%xmm2, %rax
	movdqa	%xmm3, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	.loc 2 303 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 2 304 2
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	.loc 2 306 26
	movq	-80(%rbp), %xmm2
	movq	-72(%rbp), %xmm0
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %xmm1
	movdqa	%xmm0, %xmm3
	movq	%rax, %xmm0
	call	f64x2_dot
	.loc 2 306 15 discriminator 1
	addsd	%xmm0, %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	call	f64x2_set1
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -48(%rbp)
	movq	%xmm0, -40(%rbp)
	.loc 2 307 14
	movq	-80(%rbp), %xmm2
	movq	-72(%rbp), %xmm0
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %xmm1
	movdqa	%xmm0, %xmm3
	movq	%rax, %xmm0
	call	f64x2_mul
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, %rax
	movl	$0, %edx
	movq	%xmm0, %rdx
	.loc 2 307 14 is_stmt 0 discriminator 1
	movq	%rax, %xmm2
	movq	%rdx, %xmm0
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %xmm1
	movdqa	%xmm0, %xmm3
	movq	%rax, %xmm0
	call	f64x2_sub
	movq	%xmm0, %rax
	movdqa	%xmm1, %xmm0
	movq	%rax, -32(%rbp)
	movq	%xmm0, -24(%rbp)
	.loc 2 317 9 is_stmt 1
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rcx
	movq	%rdx, %xmm1
	.loc 2 318 1
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L199
	call	__stack_chk_fail@PLT
.L199:
	movq	%rcx, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE570:
	.size	f64x2_reflect, .-f64x2_reflect
	.globl	get_time_ns
	.type	get_time_ns, @function
get_time_ns:
.LFB571:
	.file 4 "main.c"
	.loc 4 10 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	.loc 4 10 1
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 4 12 2
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	clock_gettime@PLT
	.loc 4 13 16
	movq	-24(%rbp), %rax
	.loc 4 13 9
	movq	%rax, %rdx
	.loc 4 13 34
	movq	-32(%rbp), %rax
	.loc 4 13 42
	imulq	$1000000000, %rax, %rax
	.loc 4 13 25
	addq	%rdx, %rax
	.loc 4 14 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L202
	call	__stack_chk_fail@PLT
.L202:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE571:
	.size	get_time_ns, .-get_time_ns
	.section	.rodata
.LC7:
	.string	"%lu\n"
	.text
	.globl	string8_alloc
	.type	string8_alloc, @function
string8_alloc:
.LFB572:
	.loc 4 34 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	.loc 4 35 18
	movq	-40(%rbp), %rax
	addq	$15, %rax
	.loc 4 35 6
	andq	$-16, %rax
	movq	%rax, -24(%rbp)
	.loc 4 36 2
	movq	-40(%rbp), %rax
	leaq	.LC7(%rip), %rdx
	movq	%rax, %rsi
	movq	%rdx, %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 4 37 10
	movq	-40(%rbp), %rax
	movq	%rax, -16(%rbp)
	.loc 4 39 11
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	malloc@PLT
	.loc 4 37 10
	movq	%rax, -8(%rbp)
	.loc 4 41 9
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	.loc 4 42 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE572:
	.size	string8_alloc, .-string8_alloc
	.globl	main
	.type	main, @function
main:
.LFB573:
	.loc 4 46 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	.loc 4 48 14
	movl	$5, %edi
	call	string8_alloc
	movq	%rax, -16(%rbp)
	movq	%rdx, -8(%rbp)
	.loc 4 53 9
	movl	$0, %eax
	.loc 4 54 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE573:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	1065353216
	.align 16
.LC1:
	.long	2147483647
	.long	0
	.long	0
	.long	0
	.align 16
.LC2:
	.long	-2147483648
	.long	0
	.long	0
	.long	0
	.align 8
.LC3:
	.long	0
	.long	1072693248
	.align 16
.LC4:
	.long	-1
	.long	2147483647
	.long	0
	.long	0
	.align 16
.LC5:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.text
.Letext0:
	.file 5 "/usr/include/bits/types.h"
	.file 6 "/usr/include/bits/types/clockid_t.h"
	.file 7 "/usr/include/bits/stdint-intn.h"
	.file 8 "/usr/include/bits/types/struct_timespec.h"
	.file 9 "/usr/include/bits/stdint-uintn.h"
	.file 10 "base.h"
	.file 11 "f32x2.h"
	.file 12 "f64x2.h"
	.file 13 "/usr/include/stdlib.h"
	.file 14 "/usr/include/stdio.h"
	.file 15 "/usr/include/time.h"
	.file 16 "/usr/include/bits/mathcalls.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x1abf
	.value	0x5
	.byte	0x1
	.byte	0x8
	.long	.Ldebug_abbrev0
	.uleb128 0x26
	.long	.LASF122
	.byte	0x1d
	.byte	0x3
	.long	0x31647
	.long	.LASF0
	.long	.LASF1
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x7
	.byte	0x8
	.byte	0x7
	.long	.LASF2
	.uleb128 0x7
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x27
	.byte	0x8
	.uleb128 0x7
	.byte	0x1
	.byte	0x8
	.long	.LASF4
	.uleb128 0x7
	.byte	0x2
	.byte	0x7
	.long	.LASF5
	.uleb128 0x7
	.byte	0x1
	.byte	0x6
	.long	.LASF6
	.uleb128 0x6
	.long	.LASF8
	.byte	0x5
	.byte	0x26
	.byte	0x17
	.long	0x43
	.uleb128 0x7
	.byte	0x2
	.byte	0x5
	.long	.LASF7
	.uleb128 0x6
	.long	.LASF9
	.byte	0x5
	.byte	0x29
	.byte	0x14
	.long	0x77
	.uleb128 0x28
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x7
	.byte	0x8
	.byte	0x5
	.long	.LASF10
	.uleb128 0x6
	.long	.LASF11
	.byte	0x5
	.byte	0x2d
	.byte	0x1b
	.long	0x33
	.uleb128 0x6
	.long	.LASF12
	.byte	0x5
	.byte	0xa0
	.byte	0x1a
	.long	0x7e
	.uleb128 0x6
	.long	.LASF13
	.byte	0x5
	.byte	0xa9
	.byte	0x1d
	.long	0x77
	.uleb128 0x6
	.long	.LASF14
	.byte	0x5
	.byte	0xc5
	.byte	0x21
	.long	0x7e
	.uleb128 0x7
	.byte	0x1
	.byte	0x6
	.long	.LASF15
	.uleb128 0x16
	.long	0xb5
	.uleb128 0xa
	.long	0xbc
	.uleb128 0x7
	.byte	0x8
	.byte	0x5
	.long	.LASF16
	.uleb128 0x6
	.long	.LASF17
	.byte	0x6
	.byte	0x7
	.byte	0x15
	.long	0x9d
	.uleb128 0x6
	.long	.LASF18
	.byte	0x7
	.byte	0x1a
	.byte	0x13
	.long	0x6b
	.uleb128 0x1c
	.long	.LASF30
	.byte	0x8
	.byte	0xb
	.byte	0x8
	.long	0x10c
	.uleb128 0x17
	.long	.LASF19
	.byte	0x8
	.byte	0x10
	.byte	0xc
	.long	0x91
	.byte	0
	.uleb128 0x17
	.long	.LASF20
	.byte	0x8
	.byte	0x15
	.byte	0x15
	.long	0xa9
	.byte	0x8
	.byte	0
	.uleb128 0x7
	.byte	0x8
	.byte	0x7
	.long	.LASF21
	.uleb128 0x6
	.long	.LASF22
	.byte	0x9
	.byte	0x18
	.byte	0x13
	.long	0x58
	.uleb128 0x6
	.long	.LASF23
	.byte	0x9
	.byte	0x1b
	.byte	0x14
	.long	0x85
	.uleb128 0x7
	.byte	0x4
	.byte	0x4
	.long	.LASF24
	.uleb128 0x7
	.byte	0x8
	.byte	0x4
	.long	.LASF25
	.uleb128 0x16
	.long	0x132
	.uleb128 0x13
	.string	"s32"
	.byte	0xa
	.byte	0x11
	.long	0xd9
	.uleb128 0x13
	.string	"u8"
	.byte	0xd
	.byte	0x11
	.long	0x113
	.uleb128 0x13
	.string	"u64"
	.byte	0x10
	.byte	0x12
	.long	0x11f
	.uleb128 0x13
	.string	"f32"
	.byte	0x15
	.byte	0xf
	.long	0x12b
	.uleb128 0x16
	.long	0x15e
	.uleb128 0x13
	.string	"f64"
	.byte	0x16
	.byte	0x10
	.long	0x132
	.uleb128 0x16
	.long	0x16e
	.uleb128 0x7
	.byte	0x4
	.byte	0x4
	.long	.LASF24
	.uleb128 0x6
	.long	.LASF26
	.byte	0x3
	.byte	0x28
	.byte	0x10
	.long	0x191
	.uleb128 0x1d
	.long	0x132
	.long	0x19c
	.uleb128 0x1e
	.byte	0
	.uleb128 0x6
	.long	.LASF27
	.byte	0x3
	.byte	0x36
	.byte	0x10
	.long	0x1a8
	.uleb128 0x1d
	.long	0x132
	.long	0x1b3
	.uleb128 0x1e
	.byte	0
	.uleb128 0x7
	.byte	0x8
	.byte	0x4
	.long	.LASF25
	.uleb128 0xc
	.byte	0x8
	.byte	0xb
	.byte	0x3
	.long	0x1ce
	.uleb128 0x8
	.string	"s"
	.byte	0xb
	.byte	0x3
	.byte	0xd
	.long	0x1ce
	.byte	0
	.byte	0
	.uleb128 0x1f
	.long	0x15e
	.long	0x1dd
	.uleb128 0x20
	.long	0x33
	.byte	0
	.uleb128 0xc
	.byte	0x8
	.byte	0xb
	.byte	0x4
	.long	0x1fc
	.uleb128 0x8
	.string	"x"
	.byte	0xb
	.byte	0x4
	.byte	0xd
	.long	0x15e
	.byte	0
	.uleb128 0x8
	.string	"y"
	.byte	0xb
	.byte	0x4
	.byte	0xf
	.long	0x15e
	.byte	0x4
	.byte	0
	.uleb128 0xc
	.byte	0x8
	.byte	0xb
	.byte	0x5
	.long	0x21b
	.uleb128 0x8
	.string	"a"
	.byte	0xb
	.byte	0x5
	.byte	0xd
	.long	0x15e
	.byte	0
	.uleb128 0x8
	.string	"b"
	.byte	0xb
	.byte	0x5
	.byte	0xf
	.long	0x15e
	.byte	0x4
	.byte	0
	.uleb128 0x21
	.long	.LASF28
	.byte	0x8
	.byte	0xb
	.byte	0x2
	.long	0x237
	.uleb128 0xd
	.long	0x1ba
	.uleb128 0xd
	.long	0x1dd
	.uleb128 0xd
	.long	0x1fc
	.byte	0
	.uleb128 0x6
	.long	.LASF28
	.byte	0xb
	.byte	0x6
	.byte	0x2
	.long	0x21b
	.uleb128 0xc
	.byte	0x10
	.byte	0xc
	.byte	0x7
	.long	0x257
	.uleb128 0x8
	.string	"s"
	.byte	0xc
	.byte	0x7
	.byte	0xd
	.long	0x257
	.byte	0
	.byte	0
	.uleb128 0x1f
	.long	0x16e
	.long	0x266
	.uleb128 0x20
	.long	0x33
	.byte	0
	.uleb128 0xc
	.byte	0x10
	.byte	0xc
	.byte	0x8
	.long	0x285
	.uleb128 0x8
	.string	"x"
	.byte	0xc
	.byte	0x8
	.byte	0xd
	.long	0x16e
	.byte	0
	.uleb128 0x8
	.string	"y"
	.byte	0xc
	.byte	0x8
	.byte	0xf
	.long	0x16e
	.byte	0x8
	.byte	0
	.uleb128 0xc
	.byte	0x10
	.byte	0xc
	.byte	0x9
	.long	0x2a4
	.uleb128 0x8
	.string	"a"
	.byte	0xc
	.byte	0x9
	.byte	0xd
	.long	0x16e
	.byte	0
	.uleb128 0x8
	.string	"b"
	.byte	0xc
	.byte	0x9
	.byte	0xf
	.long	0x16e
	.byte	0x8
	.byte	0
	.uleb128 0xc
	.byte	0x10
	.byte	0xc
	.byte	0xb
	.long	0x2b8
	.uleb128 0x8
	.string	"v"
	.byte	0xc
	.byte	0xb
	.byte	0x11
	.long	0x19c
	.byte	0
	.byte	0
	.uleb128 0x21
	.long	.LASF29
	.byte	0x10
	.byte	0xc
	.byte	0x6
	.long	0x2d9
	.uleb128 0xd
	.long	0x243
	.uleb128 0xd
	.long	0x266
	.uleb128 0xd
	.long	0x285
	.uleb128 0xd
	.long	0x2a4
	.byte	0
	.uleb128 0x6
	.long	.LASF29
	.byte	0xc
	.byte	0xd
	.byte	0x2
	.long	0x2b8
	.uleb128 0x1c
	.long	.LASF31
	.byte	0x4
	.byte	0x11
	.byte	0x10
	.long	0x30c
	.uleb128 0x17
	.long	.LASF32
	.byte	0x4
	.byte	0x12
	.byte	0x6
	.long	0x153
	.byte	0
	.uleb128 0x17
	.long	.LASF33
	.byte	0x4
	.byte	0x13
	.byte	0x6
	.long	0x30c
	.byte	0x8
	.byte	0
	.uleb128 0xa
	.long	0x149
	.uleb128 0x6
	.long	.LASF31
	.byte	0x4
	.byte	0x14
	.byte	0x2
	.long	0x2e5
	.uleb128 0x1a
	.long	.LASF34
	.byte	0xd
	.value	0x2a0
	.byte	0xe
	.long	0x41
	.long	0x334
	.uleb128 0x9
	.long	0x33
	.byte	0
	.uleb128 0x1a
	.long	.LASF35
	.byte	0xe
	.value	0x16e
	.byte	0xc
	.long	0x77
	.long	0x34c
	.uleb128 0x9
	.long	0xc1
	.uleb128 0x29
	.byte	0
	.uleb128 0x1a
	.long	.LASF36
	.byte	0xf
	.value	0x120
	.byte	0xc
	.long	0x77
	.long	0x368
	.uleb128 0x9
	.long	0xcd
	.uleb128 0x9
	.long	0x368
	.byte	0
	.uleb128 0xa
	.long	0xe5
	.uleb128 0x18
	.long	.LASF37
	.byte	0x3b
	.long	0x132
	.long	0x386
	.uleb128 0x9
	.long	0x132
	.uleb128 0x9
	.long	0x132
	.byte	0
	.uleb128 0x18
	.long	.LASF38
	.byte	0xb4
	.long	0x132
	.long	0x39a
	.uleb128 0x9
	.long	0x132
	.byte	0
	.uleb128 0x18
	.long	.LASF39
	.byte	0x3b
	.long	0x12b
	.long	0x3b3
	.uleb128 0x9
	.long	0x12b
	.uleb128 0x9
	.long	0x12b
	.byte	0
	.uleb128 0x18
	.long	.LASF40
	.byte	0xb4
	.long	0x12b
	.long	0x3c7
	.uleb128 0x9
	.long	0x12b
	.byte	0
	.uleb128 0x3
	.long	.LASF41
	.byte	0x4
	.byte	0x2d
	.byte	0x5
	.long	0x13e
	.quad	.LFB573
	.quad	.LFE573-.LFB573
	.uleb128 0x1
	.byte	0x9c
	.long	0x3f7
	.uleb128 0x2
	.string	"a"
	.byte	0x4
	.byte	0x30
	.byte	0xa
	.long	0x311
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF42
	.byte	0x4
	.byte	0x21
	.byte	0x9
	.long	0x311
	.quad	.LFB572
	.quad	.LFE572-.LFB572
	.uleb128 0x1
	.byte	0x9c
	.long	0x447
	.uleb128 0x14
	.long	.LASF32
	.byte	0x4
	.byte	0x21
	.byte	0x1b
	.long	0x153
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x10
	.long	.LASF43
	.byte	0x4
	.byte	0x23
	.byte	0x6
	.long	0x153
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"str"
	.byte	0x4
	.byte	0x25
	.byte	0xa
	.long	0x311
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF44
	.byte	0x4
	.byte	0x9
	.byte	0x5
	.long	0x153
	.quad	.LFB571
	.quad	.LFE571-.LFB571
	.uleb128 0x1
	.byte	0x9c
	.long	0x478
	.uleb128 0x2
	.string	"ts"
	.byte	0x4
	.byte	0xb
	.byte	0x12
	.long	0xe5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x15
	.long	.LASF45
	.value	0x12e
	.byte	0x7
	.long	0x2d9
	.quad	.LFB570
	.quad	.LFE570-.LFB570
	.uleb128 0x1
	.byte	0x9c
	.long	0x4d5
	.uleb128 0x22
	.long	.LASF46
	.byte	0x1b
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x22
	.long	.LASF47
	.byte	0x2b
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x23
	.long	.LASF48
	.value	0x132
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0xb
	.string	"dst"
	.value	0x133
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x15
	.long	.LASF49
	.value	0x126
	.byte	0x7
	.long	0x2d9
	.quad	.LFB569
	.quad	.LFE569-.LFB569
	.uleb128 0x1
	.byte	0x9c
	.long	0x514
	.uleb128 0xe
	.string	"v"
	.value	0x126
	.byte	0x1d
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0xb
	.string	"dst"
	.value	0x128
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x15
	.long	.LASF50
	.value	0x11e
	.byte	0x7
	.long	0x2d9
	.quad	.LFB568
	.quad	.LFE568-.LFB568
	.uleb128 0x1
	.byte	0x9c
	.long	0x553
	.uleb128 0xe
	.string	"v"
	.value	0x11e
	.byte	0x1c
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0xb
	.string	"dst"
	.value	0x120
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x15
	.long	.LASF51
	.value	0x117
	.byte	0x7
	.long	0x2d9
	.quad	.LFB567
	.quad	.LFE567-.LFB567
	.uleb128 0x1
	.byte	0x9c
	.long	0x592
	.uleb128 0xe
	.string	"v"
	.value	0x117
	.byte	0x1b
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0xb
	.string	"dst"
	.value	0x119
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x2a
	.long	.LASF52
	.byte	0x2
	.value	0x111
	.byte	0x5
	.long	0x16e
	.quad	.LFB566
	.quad	.LFE566-.LFB566
	.uleb128 0x1
	.byte	0x9c
	.long	0x5e1
	.uleb128 0xe
	.string	"v0"
	.value	0x111
	.byte	0x17
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0xe
	.string	"v1"
	.value	0x111
	.byte	0x21
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0xb
	.string	"dst"
	.value	0x113
	.byte	0x6
	.long	0x16e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x15
	.long	.LASF53
	.value	0x106
	.byte	0x5
	.long	0x16e
	.quad	.LFB565
	.quad	.LFE565-.LFB565
	.uleb128 0x1
	.byte	0x9c
	.long	0x62f
	.uleb128 0xe
	.string	"v0"
	.value	0x106
	.byte	0x15
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0xe
	.string	"v1"
	.value	0x106
	.byte	0x1f
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0xb
	.string	"dst"
	.value	0x10a
	.byte	0x6
	.long	0x16e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x3
	.long	.LASF54
	.byte	0x2
	.byte	0xfb
	.byte	0x7
	.long	0x2d9
	.quad	.LFB564
	.quad	.LFE564-.LFB564
	.uleb128 0x1
	.byte	0x9c
	.long	0x6ad
	.uleb128 0x1
	.string	"v"
	.byte	0x2
	.byte	0xfb
	.byte	0x19
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x14
	.long	.LASF55
	.byte	0x2
	.byte	0xfb
	.byte	0x20
	.long	0x16e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -104
	.uleb128 0x10
	.long	.LASF56
	.byte	0x2
	.byte	0xfd
	.byte	0x6
	.long	0x16e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0xb
	.string	"mag"
	.value	0x100
	.byte	0x6
	.long	0x16e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x23
	.long	.LASF57
	.value	0x101
	.byte	0x6
	.long	0x16e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0xb
	.string	"dst"
	.value	0x102
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x3
	.long	.LASF58
	.byte	0x2
	.byte	0xf5
	.byte	0x5
	.long	0x16e
	.quad	.LFB563
	.quad	.LFE563-.LFB563
	.uleb128 0x1
	.byte	0x9c
	.long	0x6ec
	.uleb128 0x1
	.string	"v"
	.byte	0x2
	.byte	0xf5
	.byte	0x17
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0xf7
	.byte	0x6
	.long	0x16e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x3
	.long	.LASF59
	.byte	0x2
	.byte	0xe7
	.byte	0x7
	.long	0x2d9
	.quad	.LFB562
	.quad	.LFE562-.LFB562
	.uleb128 0x1
	.byte	0x9c
	.long	0x749
	.uleb128 0x1
	.string	"v0"
	.byte	0x2
	.byte	0xe7
	.byte	0x18
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x1
	.string	"v1"
	.byte	0x2
	.byte	0xe7
	.byte	0x22
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x1
	.string	"t"
	.byte	0x2
	.byte	0xe7
	.byte	0x2a
	.long	0x16e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0xe9
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x11
	.long	.LASF60
	.byte	0x2
	.byte	0xe2
	.long	0x16e
	.quad	.LFB561
	.quad	.LFE561-.LFB561
	.uleb128 0x1
	.byte	0x9c
	.long	0x792
	.uleb128 0x1
	.string	"a"
	.byte	0x2
	.byte	0xe2
	.byte	0x12
	.long	0x16e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1
	.string	"b"
	.byte	0x2
	.byte	0xe2
	.byte	0x19
	.long	0x16e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1
	.string	"t"
	.byte	0x2
	.byte	0xe2
	.byte	0x20
	.long	0x16e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0x3
	.long	.LASF61
	.byte	0x2
	.byte	0xdb
	.byte	0x5
	.long	0x16e
	.quad	.LFB560
	.quad	.LFE560-.LFB560
	.uleb128 0x1
	.byte	0x9c
	.long	0x7f1
	.uleb128 0x1
	.string	"v0"
	.byte	0x2
	.byte	0xdb
	.byte	0x1a
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x1
	.string	"v1"
	.byte	0x2
	.byte	0xdb
	.byte	0x24
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x2
	.string	"dif"
	.byte	0x2
	.byte	0xdd
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0xde
	.byte	0x6
	.long	0x16e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.byte	0
	.uleb128 0x3
	.long	.LASF62
	.byte	0x2
	.byte	0xd4
	.byte	0x7
	.long	0x2d9
	.quad	.LFB559
	.quad	.LFE559-.LFB559
	.uleb128 0x1
	.byte	0x9c
	.long	0x840
	.uleb128 0x1
	.string	"v"
	.byte	0x2
	.byte	0xd4
	.byte	0x18
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x10
	.long	.LASF63
	.byte	0x2
	.byte	0xd6
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0xd7
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x3
	.long	.LASF64
	.byte	0x2
	.byte	0xc9
	.byte	0x5
	.long	0x16e
	.quad	.LFB558
	.quad	.LFE558-.LFB558
	.uleb128 0x1
	.byte	0x9c
	.long	0x8a8
	.uleb128 0x1
	.string	"v"
	.byte	0x2
	.byte	0xc9
	.byte	0x18
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0xcd
	.byte	0x6
	.long	0x16e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x5
	.long	0x19f0
	.quad	.LBB76
	.quad	.LBE76-.LBB76
	.byte	0xcc
	.byte	0x8
	.uleb128 0x4
	.long	0x19ff
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x4
	.long	0x1a0b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.byte	0
	.uleb128 0x11
	.long	.LASF65
	.byte	0x2
	.byte	0xbe
	.long	0x16e
	.quad	.LFB557
	.quad	.LFE557-.LFB557
	.uleb128 0x1
	.byte	0x9c
	.long	0x90f
	.uleb128 0x1
	.string	"v"
	.byte	0x2
	.byte	0xbe
	.byte	0x20
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0xc2
	.byte	0x6
	.long	0x16e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x5
	.long	0x19f0
	.quad	.LBB74
	.quad	.LBE74-.LBB74
	.byte	0xc1
	.byte	0x8
	.uleb128 0x4
	.long	0x19ff
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x4
	.long	0x1a0b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.byte	0
	.uleb128 0x3
	.long	.LASF66
	.byte	0x2
	.byte	0xb5
	.byte	0x7
	.long	0x2d9
	.quad	.LFB556
	.quad	.LFE556-.LFB556
	.uleb128 0x1
	.byte	0x9c
	.long	0x94e
	.uleb128 0x1
	.string	"v"
	.byte	0x2
	.byte	0xb5
	.byte	0x17
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0xb7
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x3
	.long	.LASF67
	.byte	0x2
	.byte	0xa9
	.byte	0x7
	.long	0x2d9
	.quad	.LFB555
	.quad	.LFE555-.LFB555
	.uleb128 0x1
	.byte	0x9c
	.long	0x9ff
	.uleb128 0x1
	.string	"v"
	.byte	0x2
	.byte	0xa9
	.byte	0x19
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -128
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0xab
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x24
	.long	0x19ac
	.quad	.LBB68
	.quad	.LBE68-.LBB68
	.byte	0xad
	.long	0x9b0
	.uleb128 0x4
	.long	0x19bb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.uleb128 0x24
	.long	0x1aa9
	.quad	.LBB70
	.quad	.LBE70-.LBB70
	.byte	0xad
	.long	0x9d4
	.uleb128 0x4
	.long	0x1ab6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -104
	.byte	0
	.uleb128 0x5
	.long	0x19c8
	.quad	.LBB72
	.quad	.LBE72-.LBB72
	.byte	0xad
	.byte	0xa
	.uleb128 0x4
	.long	0x19d7
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x4
	.long	0x19e3
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.byte	0
	.byte	0
	.uleb128 0x3
	.long	.LASF68
	.byte	0x2
	.byte	0x9d
	.byte	0x7
	.long	0x2d9
	.quad	.LFB554
	.quad	.LFE554-.LFB554
	.uleb128 0x1
	.byte	0x9c
	.long	0xa5f
	.uleb128 0x1
	.string	"v"
	.byte	0x2
	.byte	0x9d
	.byte	0x18
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0x9f
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	0x19ac
	.quad	.LBB66
	.quad	.LBE66-.LBB66
	.byte	0xa1
	.byte	0xa
	.uleb128 0x4
	.long	0x19bb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.byte	0
	.uleb128 0x3
	.long	.LASF69
	.byte	0x2
	.byte	0x91
	.byte	0x7
	.long	0x2d9
	.quad	.LFB553
	.quad	.LFE553-.LFB553
	.uleb128 0x1
	.byte	0x9c
	.long	0xad7
	.uleb128 0x1
	.string	"s"
	.byte	0x2
	.byte	0x91
	.byte	0x16
	.long	0x16e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x1
	.string	"v0"
	.byte	0x2
	.byte	0x91
	.byte	0x1f
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0x93
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	0x19c8
	.quad	.LBB64
	.quad	.LBE64-.LBB64
	.byte	0x95
	.byte	0xa
	.uleb128 0x4
	.long	0x19d7
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x4
	.long	0x19e3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.byte	0
	.uleb128 0x3
	.long	.LASF70
	.byte	0x2
	.byte	0x86
	.byte	0x7
	.long	0x2d9
	.quad	.LFB552
	.quad	.LFE552-.LFB552
	.uleb128 0x1
	.byte	0x9c
	.long	0xb4f
	.uleb128 0x1
	.string	"v0"
	.byte	0x2
	.byte	0x86
	.byte	0x18
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x1
	.string	"s"
	.byte	0x2
	.byte	0x86
	.byte	0x20
	.long	0x16e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -104
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0x88
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	0x19c8
	.quad	.LBB62
	.quad	.LBE62-.LBB62
	.byte	0x8a
	.byte	0xa
	.uleb128 0x4
	.long	0x19d7
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x4
	.long	0x19e3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.byte	0
	.uleb128 0x3
	.long	.LASF71
	.byte	0x2
	.byte	0x7a
	.byte	0x7
	.long	0x2d9
	.quad	.LFB551
	.quad	.LFE551-.LFB551
	.uleb128 0x1
	.byte	0x9c
	.long	0xbc8
	.uleb128 0x1
	.string	"v0"
	.byte	0x2
	.byte	0x7a
	.byte	0x17
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x1
	.string	"v1"
	.byte	0x2
	.byte	0x7a
	.byte	0x21
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0x7c
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	0x19c8
	.quad	.LBB60
	.quad	.LBE60-.LBB60
	.byte	0x7e
	.byte	0xa
	.uleb128 0x4
	.long	0x19d7
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x4
	.long	0x19e3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.byte	0
	.uleb128 0x3
	.long	.LASF72
	.byte	0x2
	.byte	0x6e
	.byte	0x7
	.long	0x2d9
	.quad	.LFB550
	.quad	.LFE550-.LFB550
	.uleb128 0x1
	.byte	0x9c
	.long	0xc40
	.uleb128 0x1
	.string	"v0"
	.byte	0x2
	.byte	0x6e
	.byte	0x18
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x1
	.string	"s"
	.byte	0x2
	.byte	0x6e
	.byte	0x20
	.long	0x16e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -104
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0x70
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	0x19f0
	.quad	.LBB58
	.quad	.LBE58-.LBB58
	.byte	0x72
	.byte	0xa
	.uleb128 0x4
	.long	0x19ff
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x4
	.long	0x1a0b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.byte	0
	.uleb128 0x3
	.long	.LASF73
	.byte	0x2
	.byte	0x63
	.byte	0x7
	.long	0x2d9
	.quad	.LFB549
	.quad	.LFE549-.LFB549
	.uleb128 0x1
	.byte	0x9c
	.long	0xcb9
	.uleb128 0x1
	.string	"v0"
	.byte	0x2
	.byte	0x63
	.byte	0x17
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x1
	.string	"v1"
	.byte	0x2
	.byte	0x63
	.byte	0x21
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0x65
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	0x19f0
	.quad	.LBB56
	.quad	.LBE56-.LBB56
	.byte	0x67
	.byte	0xa
	.uleb128 0x4
	.long	0x19ff
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x4
	.long	0x1a0b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.byte	0
	.uleb128 0x3
	.long	.LASF74
	.byte	0x2
	.byte	0x57
	.byte	0x7
	.long	0x2d9
	.quad	.LFB548
	.quad	.LFE548-.LFB548
	.uleb128 0x1
	.byte	0x9c
	.long	0xd31
	.uleb128 0x1
	.string	"s"
	.byte	0x2
	.byte	0x57
	.byte	0x16
	.long	0x16e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x1
	.string	"v0"
	.byte	0x2
	.byte	0x57
	.byte	0x1f
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0x59
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	0x1a18
	.quad	.LBB54
	.quad	.LBE54-.LBB54
	.byte	0x5b
	.byte	0xa
	.uleb128 0x4
	.long	0x1a27
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x4
	.long	0x1a33
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.byte	0
	.uleb128 0x3
	.long	.LASF75
	.byte	0x2
	.byte	0x4b
	.byte	0x7
	.long	0x2d9
	.quad	.LFB547
	.quad	.LFE547-.LFB547
	.uleb128 0x1
	.byte	0x9c
	.long	0xda9
	.uleb128 0x1
	.string	"v0"
	.byte	0x2
	.byte	0x4b
	.byte	0x18
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x1
	.string	"s"
	.byte	0x2
	.byte	0x4b
	.byte	0x20
	.long	0x16e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -104
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0x4d
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	0x1a18
	.quad	.LBB52
	.quad	.LBE52-.LBB52
	.byte	0x4f
	.byte	0xa
	.uleb128 0x4
	.long	0x1a27
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x4
	.long	0x1a33
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.byte	0
	.uleb128 0x3
	.long	.LASF76
	.byte	0x2
	.byte	0x40
	.byte	0x7
	.long	0x2d9
	.quad	.LFB546
	.quad	.LFE546-.LFB546
	.uleb128 0x1
	.byte	0x9c
	.long	0xe22
	.uleb128 0x1
	.string	"v0"
	.byte	0x2
	.byte	0x40
	.byte	0x17
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x1
	.string	"v1"
	.byte	0x2
	.byte	0x40
	.byte	0x21
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0x42
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	0x1a18
	.quad	.LBB50
	.quad	.LBE50-.LBB50
	.byte	0x44
	.byte	0xa
	.uleb128 0x4
	.long	0x1a27
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x4
	.long	0x1a33
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.byte	0
	.uleb128 0x3
	.long	.LASF77
	.byte	0x2
	.byte	0x34
	.byte	0x7
	.long	0x2d9
	.quad	.LFB545
	.quad	.LFE545-.LFB545
	.uleb128 0x1
	.byte	0x9c
	.long	0xe9a
	.uleb128 0x1
	.string	"v0"
	.byte	0x2
	.byte	0x34
	.byte	0x18
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x1
	.string	"s"
	.byte	0x2
	.byte	0x34
	.byte	0x20
	.long	0x16e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -104
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0x36
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	0x1a40
	.quad	.LBB48
	.quad	.LBE48-.LBB48
	.byte	0x38
	.byte	0xa
	.uleb128 0x4
	.long	0x1a4e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x4
	.long	0x1a59
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.byte	0
	.uleb128 0x3
	.long	.LASF78
	.byte	0x2
	.byte	0x29
	.byte	0x7
	.long	0x2d9
	.quad	.LFB544
	.quad	.LFE544-.LFB544
	.uleb128 0x1
	.byte	0x9c
	.long	0xf13
	.uleb128 0x1
	.string	"v0"
	.byte	0x2
	.byte	0x29
	.byte	0x17
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x1
	.string	"v1"
	.byte	0x2
	.byte	0x29
	.byte	0x21
	.long	0x2d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0x2b
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	0x1a40
	.quad	.LBB46
	.quad	.LBE46-.LBB46
	.byte	0x2d
	.byte	0xa
	.uleb128 0x4
	.long	0x1a4e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x4
	.long	0x1a59
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.byte	0
	.uleb128 0x25
	.long	.LASF109
	.byte	0x2
	.byte	0x23
	.quad	.LFB543
	.quad	.LFE543-.LFB543
	.uleb128 0x1
	.byte	0x9c
	.long	0xf58
	.uleb128 0x1
	.string	"a"
	.byte	0x2
	.byte	0x23
	.byte	0x19
	.long	0xf58
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1
	.string	"b"
	.byte	0x2
	.byte	0x23
	.byte	0x21
	.long	0xf58
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1
	.string	"v"
	.byte	0x2
	.byte	0x23
	.byte	0x2a
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0xa
	.long	0x16e
	.uleb128 0x3
	.long	.LASF79
	.byte	0x2
	.byte	0x18
	.byte	0x7
	.long	0x2d9
	.quad	.LFB542
	.quad	.LFE542-.LFB542
	.uleb128 0x1
	.byte	0x9c
	.long	0xfbf
	.uleb128 0x1
	.string	"src"
	.byte	0x2
	.byte	0x18
	.byte	0x1d
	.long	0xfbf
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x2
	.string	"dst"
	.byte	0x2
	.byte	0x1a
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	0x1a65
	.quad	.LBB44
	.quad	.LBE44-.LBB44
	.byte	0x1c
	.byte	0xa
	.uleb128 0x4
	.long	0x1a73
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.byte	0
	.byte	0
	.uleb128 0xa
	.long	0x179
	.uleb128 0x3
	.long	.LASF80
	.byte	0x2
	.byte	0xd
	.byte	0x7
	.long	0x2d9
	.quad	.LFB541
	.quad	.LFE541-.LFB541
	.uleb128 0x1
	.byte	0x9c
	.long	0x1038
	.uleb128 0x1
	.string	"a"
	.byte	0x2
	.byte	0xd
	.byte	0x15
	.long	0x16e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x1
	.string	"b"
	.byte	0x2
	.byte	0xd
	.byte	0x1c
	.long	0x16e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x2
	.string	"v"
	.byte	0x2
	.byte	0xf
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	0x1a84
	.quad	.LBB42
	.quad	.LBE42-.LBB42
	.byte	0x11
	.byte	0x8
	.uleb128 0x4
	.long	0x1a92
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x4
	.long	0x1a9d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.byte	0
	.byte	0
	.uleb128 0x3
	.long	.LASF81
	.byte	0x2
	.byte	0x2
	.byte	0x7
	.long	0x2d9
	.quad	.LFB540
	.quad	.LFE540-.LFB540
	.uleb128 0x1
	.byte	0x9c
	.long	0x1096
	.uleb128 0x1
	.string	"a"
	.byte	0x2
	.byte	0x2
	.byte	0x16
	.long	0x16e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x2
	.string	"v"
	.byte	0x2
	.byte	0x4
	.byte	0x8
	.long	0x2d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	0x1aa9
	.quad	.LBB40
	.quad	.LBE40-.LBB40
	.byte	0x6
	.byte	0x8
	.uleb128 0x4
	.long	0x1ab6
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.byte	0
	.byte	0
	.uleb128 0x3
	.long	.LASF82
	.byte	0x1
	.byte	0xdb
	.byte	0x7
	.long	0x237
	.quad	.LFB539
	.quad	.LFE539-.LFB539
	.uleb128 0x1
	.byte	0x9c
	.long	0x10f5
	.uleb128 0x14
	.long	.LASF46
	.byte	0x1
	.byte	0xdb
	.byte	0x1b
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x14
	.long	.LASF47
	.byte	0x1
	.byte	0xdb
	.byte	0x2b
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x2
	.string	"dot"
	.byte	0x1
	.byte	0xdd
	.byte	0x6
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0xde
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF83
	.byte	0x1
	.byte	0xd3
	.byte	0x7
	.long	0x237
	.quad	.LFB538
	.quad	.LFE538-.LFB538
	.uleb128 0x1
	.byte	0x9c
	.long	0x1134
	.uleb128 0x1
	.string	"v"
	.byte	0x1
	.byte	0xd3
	.byte	0x1d
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0xd5
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF84
	.byte	0x1
	.byte	0xcb
	.byte	0x7
	.long	0x237
	.quad	.LFB537
	.quad	.LFE537-.LFB537
	.uleb128 0x1
	.byte	0x9c
	.long	0x1173
	.uleb128 0x1
	.string	"v"
	.byte	0x1
	.byte	0xcb
	.byte	0x1c
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0xcd
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF85
	.byte	0x1
	.byte	0xc4
	.byte	0x7
	.long	0x237
	.quad	.LFB536
	.quad	.LFE536-.LFB536
	.uleb128 0x1
	.byte	0x9c
	.long	0x11b2
	.uleb128 0x1
	.string	"v"
	.byte	0x1
	.byte	0xc4
	.byte	0x1b
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0xc6
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x11
	.long	.LASF86
	.byte	0x1
	.byte	0xbe
	.long	0x15e
	.quad	.LFB535
	.quad	.LFE535-.LFB535
	.uleb128 0x1
	.byte	0x9c
	.long	0x11ff
	.uleb128 0x1
	.string	"v0"
	.byte	0x1
	.byte	0xbe
	.byte	0x17
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1
	.string	"v1"
	.byte	0x1
	.byte	0xbe
	.byte	0x21
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0xc0
	.byte	0x6
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x11
	.long	.LASF87
	.byte	0x1
	.byte	0xb8
	.long	0x15e
	.quad	.LFB534
	.quad	.LFE534-.LFB534
	.uleb128 0x1
	.byte	0x9c
	.long	0x124c
	.uleb128 0x1
	.string	"v0"
	.byte	0x1
	.byte	0xb8
	.byte	0x15
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1
	.string	"v1"
	.byte	0x1
	.byte	0xb8
	.byte	0x1f
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0xba
	.byte	0x6
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x3
	.long	.LASF88
	.byte	0x1
	.byte	0xad
	.byte	0x7
	.long	0x237
	.quad	.LFB533
	.quad	.LFE533-.LFB533
	.uleb128 0x1
	.byte	0x9c
	.long	0x12c7
	.uleb128 0x1
	.string	"v"
	.byte	0x1
	.byte	0xad
	.byte	0x19
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x14
	.long	.LASF55
	.byte	0x1
	.byte	0xad
	.byte	0x20
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x10
	.long	.LASF56
	.byte	0x1
	.byte	0xaf
	.byte	0x6
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x2
	.string	"mag"
	.byte	0x1
	.byte	0xb2
	.byte	0x6
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.long	.LASF57
	.byte	0x1
	.byte	0xb3
	.byte	0x6
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0xb4
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF89
	.byte	0x1
	.byte	0xa7
	.byte	0x5
	.long	0x15e
	.quad	.LFB532
	.quad	.LFE532-.LFB532
	.uleb128 0x1
	.byte	0x9c
	.long	0x1306
	.uleb128 0x1
	.string	"v"
	.byte	0x1
	.byte	0xa7
	.byte	0x17
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0xa9
	.byte	0x6
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x3
	.long	.LASF90
	.byte	0x1
	.byte	0x9f
	.byte	0x7
	.long	0x237
	.quad	.LFB531
	.quad	.LFE531-.LFB531
	.uleb128 0x1
	.byte	0x9c
	.long	0x1361
	.uleb128 0x1
	.string	"v0"
	.byte	0x1
	.byte	0x9f
	.byte	0x18
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1
	.string	"v1"
	.byte	0x1
	.byte	0x9f
	.byte	0x22
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1
	.string	"t"
	.byte	0x1
	.byte	0x9f
	.byte	0x2a
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0xa1
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x11
	.long	.LASF91
	.byte	0x1
	.byte	0x9a
	.long	0x15e
	.quad	.LFB530
	.quad	.LFE530-.LFB530
	.uleb128 0x1
	.byte	0x9c
	.long	0x13aa
	.uleb128 0x1
	.string	"a"
	.byte	0x1
	.byte	0x9a
	.byte	0x12
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x1
	.string	"b"
	.byte	0x1
	.byte	0x9a
	.byte	0x19
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1
	.string	"t"
	.byte	0x1
	.byte	0x9a
	.byte	0x20
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0x3
	.long	.LASF92
	.byte	0x1
	.byte	0x93
	.byte	0x5
	.long	0x15e
	.quad	.LFB529
	.quad	.LFE529-.LFB529
	.uleb128 0x1
	.byte	0x9c
	.long	0x1407
	.uleb128 0x1
	.string	"v0"
	.byte	0x1
	.byte	0x93
	.byte	0x1a
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1
	.string	"v1"
	.byte	0x1
	.byte	0x93
	.byte	0x24
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x2
	.string	"dif"
	.byte	0x1
	.byte	0x95
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x96
	.byte	0x6
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.byte	0
	.uleb128 0x3
	.long	.LASF93
	.byte	0x1
	.byte	0x8c
	.byte	0x7
	.long	0x237
	.quad	.LFB528
	.quad	.LFE528-.LFB528
	.uleb128 0x1
	.byte	0x9c
	.long	0x1455
	.uleb128 0x1
	.string	"v"
	.byte	0x1
	.byte	0x8c
	.byte	0x18
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x10
	.long	.LASF63
	.byte	0x1
	.byte	0x8e
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x8f
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF94
	.byte	0x1
	.byte	0x86
	.byte	0x5
	.long	0x15e
	.quad	.LFB527
	.quad	.LFE527-.LFB527
	.uleb128 0x1
	.byte	0x9c
	.long	0x1494
	.uleb128 0x1
	.string	"v"
	.byte	0x1
	.byte	0x86
	.byte	0x18
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x88
	.byte	0x6
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x11
	.long	.LASF95
	.byte	0x1
	.byte	0x80
	.long	0x15e
	.quad	.LFB526
	.quad	.LFE526-.LFB526
	.uleb128 0x1
	.byte	0x9c
	.long	0x14d2
	.uleb128 0x1
	.string	"v"
	.byte	0x1
	.byte	0x80
	.byte	0x20
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x82
	.byte	0x6
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x3
	.long	.LASF96
	.byte	0x1
	.byte	0x78
	.byte	0x7
	.long	0x237
	.quad	.LFB525
	.quad	.LFE525-.LFB525
	.uleb128 0x1
	.byte	0x9c
	.long	0x1511
	.uleb128 0x1
	.string	"v"
	.byte	0x1
	.byte	0x78
	.byte	0x17
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x7a
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF97
	.byte	0x1
	.byte	0x70
	.byte	0x7
	.long	0x237
	.quad	.LFB524
	.quad	.LFE524-.LFB524
	.uleb128 0x1
	.byte	0x9c
	.long	0x1550
	.uleb128 0x1
	.string	"v"
	.byte	0x1
	.byte	0x70
	.byte	0x19
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x72
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF98
	.byte	0x1
	.byte	0x68
	.byte	0x7
	.long	0x237
	.quad	.LFB523
	.quad	.LFE523-.LFB523
	.uleb128 0x1
	.byte	0x9c
	.long	0x158f
	.uleb128 0x1
	.string	"v"
	.byte	0x1
	.byte	0x68
	.byte	0x18
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x6a
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF99
	.byte	0x1
	.byte	0x60
	.byte	0x7
	.long	0x237
	.quad	.LFB522
	.quad	.LFE522-.LFB522
	.uleb128 0x1
	.byte	0x9c
	.long	0x15dc
	.uleb128 0x1
	.string	"s"
	.byte	0x1
	.byte	0x60
	.byte	0x16
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x1
	.string	"v0"
	.byte	0x1
	.byte	0x60
	.byte	0x1f
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x62
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF100
	.byte	0x1
	.byte	0x59
	.byte	0x7
	.long	0x237
	.quad	.LFB521
	.quad	.LFE521-.LFB521
	.uleb128 0x1
	.byte	0x9c
	.long	0x1629
	.uleb128 0x1
	.string	"v0"
	.byte	0x1
	.byte	0x59
	.byte	0x18
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1
	.string	"s"
	.byte	0x1
	.byte	0x59
	.byte	0x20
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x5b
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF101
	.byte	0x1
	.byte	0x51
	.byte	0x7
	.long	0x237
	.quad	.LFB520
	.quad	.LFE520-.LFB520
	.uleb128 0x1
	.byte	0x9c
	.long	0x1677
	.uleb128 0x1
	.string	"v0"
	.byte	0x1
	.byte	0x51
	.byte	0x17
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1
	.string	"v1"
	.byte	0x1
	.byte	0x51
	.byte	0x21
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x53
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF102
	.byte	0x1
	.byte	0x49
	.byte	0x7
	.long	0x237
	.quad	.LFB519
	.quad	.LFE519-.LFB519
	.uleb128 0x1
	.byte	0x9c
	.long	0x16c4
	.uleb128 0x1
	.string	"v0"
	.byte	0x1
	.byte	0x49
	.byte	0x18
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1
	.string	"s"
	.byte	0x1
	.byte	0x49
	.byte	0x20
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x4b
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF103
	.byte	0x1
	.byte	0x42
	.byte	0x7
	.long	0x237
	.quad	.LFB518
	.quad	.LFE518-.LFB518
	.uleb128 0x1
	.byte	0x9c
	.long	0x1712
	.uleb128 0x1
	.string	"v0"
	.byte	0x1
	.byte	0x42
	.byte	0x17
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1
	.string	"v1"
	.byte	0x1
	.byte	0x42
	.byte	0x21
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x44
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF104
	.byte	0x1
	.byte	0x3a
	.byte	0x7
	.long	0x237
	.quad	.LFB517
	.quad	.LFE517-.LFB517
	.uleb128 0x1
	.byte	0x9c
	.long	0x175f
	.uleb128 0x1
	.string	"s"
	.byte	0x1
	.byte	0x3a
	.byte	0x16
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x1
	.string	"v0"
	.byte	0x1
	.byte	0x3a
	.byte	0x1f
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x3c
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF105
	.byte	0x1
	.byte	0x32
	.byte	0x7
	.long	0x237
	.quad	.LFB516
	.quad	.LFE516-.LFB516
	.uleb128 0x1
	.byte	0x9c
	.long	0x17ac
	.uleb128 0x1
	.string	"v0"
	.byte	0x1
	.byte	0x32
	.byte	0x18
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1
	.string	"s"
	.byte	0x1
	.byte	0x32
	.byte	0x20
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x34
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF106
	.byte	0x1
	.byte	0x2b
	.byte	0x7
	.long	0x237
	.quad	.LFB515
	.quad	.LFE515-.LFB515
	.uleb128 0x1
	.byte	0x9c
	.long	0x17fa
	.uleb128 0x1
	.string	"v0"
	.byte	0x1
	.byte	0x2b
	.byte	0x17
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1
	.string	"v1"
	.byte	0x1
	.byte	0x2b
	.byte	0x21
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x2d
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF107
	.byte	0x1
	.byte	0x23
	.byte	0x7
	.long	0x237
	.quad	.LFB514
	.quad	.LFE514-.LFB514
	.uleb128 0x1
	.byte	0x9c
	.long	0x1847
	.uleb128 0x1
	.string	"v0"
	.byte	0x1
	.byte	0x23
	.byte	0x18
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1
	.string	"s"
	.byte	0x1
	.byte	0x23
	.byte	0x20
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x25
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF108
	.byte	0x1
	.byte	0x1c
	.byte	0x7
	.long	0x237
	.quad	.LFB513
	.quad	.LFE513-.LFB513
	.uleb128 0x1
	.byte	0x9c
	.long	0x1895
	.uleb128 0x1
	.string	"v0"
	.byte	0x1
	.byte	0x1c
	.byte	0x17
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1
	.string	"v1"
	.byte	0x1
	.byte	0x1c
	.byte	0x21
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x1e
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x25
	.long	.LASF110
	.byte	0x1
	.byte	0x16
	.quad	.LFB512
	.quad	.LFE512-.LFB512
	.uleb128 0x1
	.byte	0x9c
	.long	0x18da
	.uleb128 0x1
	.string	"a"
	.byte	0x1
	.byte	0x16
	.byte	0x19
	.long	0x18da
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1
	.string	"b"
	.byte	0x1
	.byte	0x16
	.byte	0x21
	.long	0x18da
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1
	.string	"v"
	.byte	0x1
	.byte	0x16
	.byte	0x2a
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0xa
	.long	0x15e
	.uleb128 0x3
	.long	.LASF111
	.byte	0x1
	.byte	0xf
	.byte	0x7
	.long	0x237
	.quad	.LFB511
	.quad	.LFE511-.LFB511
	.uleb128 0x1
	.byte	0x9c
	.long	0x1920
	.uleb128 0x1
	.string	"src"
	.byte	0x1
	.byte	0xf
	.byte	0x1d
	.long	0x1920
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"dst"
	.byte	0x1
	.byte	0x11
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0xa
	.long	0x169
	.uleb128 0x3
	.long	.LASF112
	.byte	0x1
	.byte	0x9
	.byte	0x7
	.long	0x237
	.quad	.LFB510
	.quad	.LFE510-.LFB510
	.uleb128 0x1
	.byte	0x9c
	.long	0x196f
	.uleb128 0x1
	.string	"a"
	.byte	0x1
	.byte	0x9
	.byte	0x15
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x1
	.string	"b"
	.byte	0x1
	.byte	0x9
	.byte	0x1c
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.string	"v"
	.byte	0x1
	.byte	0xb
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x3
	.long	.LASF113
	.byte	0x1
	.byte	0x3
	.byte	0x7
	.long	0x237
	.quad	.LFB509
	.quad	.LFE509-.LFB509
	.uleb128 0x1
	.byte	0x9c
	.long	0x19ac
	.uleb128 0x1
	.string	"a"
	.byte	0x1
	.byte	0x3
	.byte	0x16
	.long	0x15e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x2
	.string	"v"
	.byte	0x1
	.byte	0x5
	.byte	0x8
	.long	0x237
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x19
	.long	.LASF114
	.value	0x12a
	.long	0x19c
	.long	0x19c8
	.uleb128 0xf
	.string	"__A"
	.value	0x12a
	.byte	0x16
	.long	0x19c
	.byte	0
	.uleb128 0x19
	.long	.LASF115
	.value	0x11e
	.long	0x19c
	.long	0x19f0
	.uleb128 0xf
	.string	"__A"
	.value	0x11e
	.byte	0x15
	.long	0x19c
	.uleb128 0xf
	.string	"__B"
	.value	0x11e
	.byte	0x22
	.long	0x19c
	.byte	0
	.uleb128 0x19
	.long	.LASF116
	.value	0x112
	.long	0x19c
	.long	0x1a18
	.uleb128 0xf
	.string	"__A"
	.value	0x112
	.byte	0x15
	.long	0x19c
	.uleb128 0xf
	.string	"__B"
	.value	0x112
	.byte	0x22
	.long	0x19c
	.byte	0
	.uleb128 0x19
	.long	.LASF117
	.value	0x106
	.long	0x19c
	.long	0x1a40
	.uleb128 0xf
	.string	"__A"
	.value	0x106
	.byte	0x15
	.long	0x19c
	.uleb128 0xf
	.string	"__B"
	.value	0x106
	.byte	0x22
	.long	0x19c
	.byte	0
	.uleb128 0x1b
	.long	.LASF118
	.byte	0xfa
	.long	0x19c
	.long	0x1a65
	.uleb128 0x12
	.string	"__A"
	.byte	0xfa
	.byte	0x15
	.long	0x19c
	.uleb128 0x12
	.string	"__B"
	.byte	0xfa
	.byte	0x22
	.long	0x19c
	.byte	0
	.uleb128 0x1b
	.long	.LASF119
	.byte	0x7e
	.long	0x19c
	.long	0x1a7f
	.uleb128 0x12
	.string	"__P"
	.byte	0x7e
	.byte	0x1c
	.long	0x1a7f
	.byte	0
	.uleb128 0xa
	.long	0x139
	.uleb128 0x1b
	.long	.LASF120
	.byte	0x57
	.long	0x19c
	.long	0x1aa9
	.uleb128 0x12
	.string	"__W"
	.byte	0x57
	.byte	0x14
	.long	0x132
	.uleb128 0x12
	.string	"__X"
	.byte	0x57
	.byte	0x20
	.long	0x132
	.byte	0
	.uleb128 0x2b
	.long	.LASF121
	.byte	0x3
	.byte	0x4a
	.byte	0x1
	.long	0x19c
	.byte	0x3
	.uleb128 0x12
	.string	"__F"
	.byte	0x4a
	.byte	0x15
	.long	0x132
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x58
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 8
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x89
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 10
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 16
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 16
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x2107
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x21
	.byte	0
	.uleb128 0x2f
	.uleb128 0x21
	.sleb128 1
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x21
	.sleb128 1
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x17
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 15
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0x21
	.sleb128 302
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x58
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0x21
	.sleb128 10
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x90
	.uleb128 0xb
	.uleb128 0x91
	.uleb128 0x6
	.uleb128 0x3
	.uleb128 0x1f
	.uleb128 0x1b
	.uleb128 0x1f
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x34
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF35:
	.string	"printf"
.LASF57:
	.string	"scale"
.LASF34:
	.string	"malloc"
.LASF106:
	.string	"f32x2_sub"
.LASF45:
	.string	"f64x2_reflect"
.LASF82:
	.string	"f32x2_reflect"
.LASF108:
	.string	"f32x2_add"
.LASF120:
	.string	"_mm_set_pd"
.LASF8:
	.string	"__uint8_t"
.LASF51:
	.string	"f64x2_perp_cw"
.LASF65:
	.string	"f64x2_length_squared"
.LASF49:
	.string	"f64x2_unit_perp"
.LASF61:
	.string	"f64x2_distance"
.LASF58:
	.string	"f64x2_angle"
.LASF21:
	.string	"long long unsigned int"
.LASF29:
	.string	"f64x2"
.LASF39:
	.string	"atan2f"
.LASF97:
	.string	"f32x2_rsqrt"
.LASF67:
	.string	"f64x2_rsqrt"
.LASF36:
	.string	"clock_gettime"
.LASF103:
	.string	"f32x2_mul"
.LASF79:
	.string	"f64x2_load"
.LASF42:
	.string	"string8_alloc"
.LASF16:
	.string	"long long int"
.LASF6:
	.string	"signed char"
.LASF55:
	.string	"max_mag"
.LASF99:
	.string	"f32x2_1div"
.LASF10:
	.string	"long int"
.LASF88:
	.string	"f32x2_trunc"
.LASF59:
	.string	"f64x2_lerp"
.LASF54:
	.string	"f64x2_trunc"
.LASF85:
	.string	"f32x2_perp_cw"
.LASF66:
	.string	"f64x2_abs"
.LASF25:
	.string	"double"
.LASF31:
	.string	"String8"
.LASF83:
	.string	"f32x2_unit_perp"
.LASF68:
	.string	"f64x2_sqrt"
.LASF72:
	.string	"f64x2_mul1"
.LASF111:
	.string	"f32x2_load"
.LASF50:
	.string	"f64x2_perp_ccw"
.LASF52:
	.string	"f64x2_cross"
.LASF119:
	.string	"_mm_load_pd"
.LASF75:
	.string	"f64x2_sub1"
.LASF3:
	.string	"unsigned int"
.LASF48:
	.string	"dot2"
.LASF116:
	.string	"_mm_mul_pd"
.LASF2:
	.string	"long unsigned int"
.LASF90:
	.string	"f32x2_lerp"
.LASF101:
	.string	"f32x2_div"
.LASF80:
	.string	"f64x2_set"
.LASF33:
	.string	"data"
.LASF32:
	.string	"size"
.LASF5:
	.string	"short unsigned int"
.LASF62:
	.string	"f64x2_unit"
.LASF91:
	.string	"f32_lerp"
.LASF98:
	.string	"f32x2_sqrt"
.LASF43:
	.string	"full_size"
.LASF102:
	.string	"f32x2_mul1"
.LASF7:
	.string	"short int"
.LASF76:
	.string	"f64x2_sub"
.LASF40:
	.string	"sqrtf"
.LASF105:
	.string	"f32x2_sub1"
.LASF56:
	.string	"mag_sq"
.LASF78:
	.string	"f64x2_add"
.LASF27:
	.string	"__m128d"
.LASF44:
	.string	"get_time_ns"
.LASF60:
	.string	"f64_lerp"
.LASF20:
	.string	"tv_nsec"
.LASF94:
	.string	"f32x2_length"
.LASF63:
	.string	"norm"
.LASF19:
	.string	"tv_sec"
.LASF14:
	.string	"__syscall_slong_t"
.LASF74:
	.string	"f64x2_1sub"
.LASF46:
	.string	"incident"
.LASF23:
	.string	"uint64_t"
.LASF73:
	.string	"f64x2_mul"
.LASF93:
	.string	"f32x2_unit"
.LASF81:
	.string	"f64x2_set1"
.LASF47:
	.string	"normal"
.LASF11:
	.string	"__uint64_t"
.LASF24:
	.string	"float"
.LASF92:
	.string	"f32x2_distance"
.LASF71:
	.string	"f64x2_div"
.LASF13:
	.string	"__clockid_t"
.LASF18:
	.string	"int32_t"
.LASF4:
	.string	"unsigned char"
.LASF122:
	.string	"GNU C23 15.2.1 20260103 -march=x86-64 -gdwarf -O0 -fanalyzer"
.LASF37:
	.string	"atan2"
.LASF104:
	.string	"f32x2_1sub"
.LASF95:
	.string	"f32x2_length_squared"
.LASF30:
	.string	"timespec"
.LASF115:
	.string	"_mm_div_pd"
.LASF77:
	.string	"f64x2_add1"
.LASF113:
	.string	"f32x2_set1"
.LASF121:
	.string	"_mm_set1_pd"
.LASF70:
	.string	"f64x2_div1"
.LASF15:
	.string	"char"
.LASF114:
	.string	"_mm_sqrt_pd"
.LASF86:
	.string	"f32x2_cross"
.LASF26:
	.string	"__v2df"
.LASF117:
	.string	"_mm_sub_pd"
.LASF28:
	.string	"f32x2"
.LASF9:
	.string	"__int32_t"
.LASF96:
	.string	"f32x2_abs"
.LASF84:
	.string	"f32x2_perp_ccw"
.LASF109:
	.string	"f64x2_scatter"
.LASF110:
	.string	"f32x2_scatter"
.LASF53:
	.string	"f64x2_dot"
.LASF12:
	.string	"__time_t"
.LASF64:
	.string	"f64x2_length"
.LASF118:
	.string	"_mm_add_pd"
.LASF22:
	.string	"uint8_t"
.LASF107:
	.string	"f32x2_add1"
.LASF100:
	.string	"f32x2_div1"
.LASF38:
	.string	"sqrt"
.LASF112:
	.string	"f32x2_set"
.LASF89:
	.string	"f32x2_angle"
.LASF17:
	.string	"clockid_t"
.LASF41:
	.string	"main"
.LASF69:
	.string	"f64x2_1div"
.LASF87:
	.string	"f32x2_dot"
	.section	.debug_line_str,"MS",@progbits,1
.LASF0:
	.string	"main.c"
.LASF1:
	.string	"/home/ic/unified"
	.ident	"GCC: (GNU) 15.2.1 20260103"
	.section	.note.GNU-stack,"",@progbits
