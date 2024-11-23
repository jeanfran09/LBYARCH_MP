section .data

var1 dd 1000.0
var2 dd 3600.0
temp dd 0.0

section .text
bits 64
default rel

global x64calc
extern printf

x64calc:
	movss xmm0, [var1]
	movss xmm1, [var2]
L1:
	movss xmm2, [rdx]
	add rdx, 4
	movss xmm3, [rdx]
	add rdx, 4
	movss xmm4, [rdx]
	subss xmm3, xmm2
	vmulss xmm5, xmm3, xmm0
	vdivss xmm6, xmm5, xmm1
	vdivss xmm7, xmm6, xmm4
	
	vmovsd xmm8, xmm7
	cvtsd2si rsi, xmm8
	;movsx rdi, edx
	;mov [rdx], rsi
	movss [rdx], xmm8
	add rdx, 4
	LOOP L1
ret