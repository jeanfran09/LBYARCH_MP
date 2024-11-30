section .data
var1 dd 1000.0
var2 dd 3600.0

section .text
bits 64
default rel
global x64calc

x64calc:
    xor r9, r9
    movss xmm0, [var1]
	movss xmm1, [var2]

loop:
    cmp r9, rcx
    jge done

    mov rax, r9
    imul rax, 3

    movss xmm2, [rdx + rax * 4]
    movss xmm3, [rdx + rax * 4 + 4]
    movss xmm4, [rdx + rax * 4 + 8]

    subss xmm3, xmm2
	vmulss xmm5, xmm3, xmm0
	vdivss xmm6, xmm5, xmm1
	vdivss xmm7, xmm6, xmm4

    cvtss2si eax, xmm7
    mov [r8 + r9 * 4], eax
    inc r9

    jmp loop

done:
    ret