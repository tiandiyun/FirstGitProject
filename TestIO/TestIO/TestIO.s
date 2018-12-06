	.file	"TestIO.cpp"
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "Input a character: \0"
	.align 8
.LC1:
	.ascii "The character input was: '%c'\12\0"
	.text
	.globl	_Z8TestGetCv
	.def	_Z8TestGetCv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z8TestGetCv
_Z8TestGetCv:
.LFB20:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	leaq	.LC0(%rip), %rcx
	call	printf
	call	__getreent
	movq	8(%rax), %rax
	movq	%rax, %rcx
	call	fgetc
	movb	%al, -1(%rbp)
	movsbl	-1(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC1(%rip), %rcx
	call	printf
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC2:
	.ascii "pause\0"
	.text
	.globl	_Z6_tmainiPPc
	.def	_Z6_tmainiPPc;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z6_tmainiPPc
_Z6_tmainiPPc:
.LFB21:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	call	_Z8TestGetCv
	leaq	.LC2(%rip), %rcx
	call	system
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 7.3.0"
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	__getreent;	.scl	2;	.type	32;	.endef
	.def	fgetc;	.scl	2;	.type	32;	.endef
	.def	system;	.scl	2;	.type	32;	.endef
