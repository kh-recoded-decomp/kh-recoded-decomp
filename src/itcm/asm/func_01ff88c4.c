/* SDK ITCM memory routine. */

asm void func_01ff88c4(void)
{
    cmp       r2, #0
    bxeq      lr
    cmp       r2, #8
    bgt       L040
    rsb       r3, r2, #8
    add       pc, pc, r3, lsl #2
    mov       r0, r0
    strb      r1, [r0], #1
    strb      r1, [r0], #1
    strb      r1, [r0], #1
    strb      r1, [r0], #1
    strb      r1, [r0], #1
    strb      r1, [r0], #1
    strb      r1, [r0], #1
    strb      r1, [r0], #1
    bx        lr
L040:
    orr       r1, r1, r1, lsl #8
    orr       r1, r1, r1, lsl #16
    tst       r0, #1
    subne     r2, r2, #1
    strneb    r1, [r0], #1
    tst       r0, #2
    subne     r2, r2, #2
    strneh    r1, [r0], #2
    tst       r0, #4
    subne     r2, r2, #4
    strne     r1, [r0], #4
    cmp       r2, #0x20
    blt       L0ac
    stmfd     sp!, {r4, r5, r6, r7, r8, r9, r10}
    mov       r4, r1
    mov       r5, r1
    mov       r6, r1
    mov       r7, r1
    mov       r8, r1
    mov       r9, r1
    mov       r10, r1
    subs      r2, r2, #0x20
L098:
    stmgeia   r0!, {r1, r4, r5, r6, r7, r8, r9, r10}
    subges    r2, r2, #0x20
    bge       L098
    add       r2, r2, #0x20
    ldmfd     sp!, {r4, r5, r6, r7, r8, r9, r10}
L0ac:
    cmp       r2, #4
    blt       L0c8
    subs      r2, r2, #4
L0b8:
    strge     r1, [r0], #4
    subs      r2, r2, #4
    bge       L0b8
    add       r2, r2, #4
L0c8:
    subs      r2, r2, #1
    strgeb    r1, [r0], #1
    subges    r2, r2, #1
    strgeb    r1, [r0], #1
    subges    r2, r2, #1
    strgeb    r1, [r0], #1
    bx        lr
}
