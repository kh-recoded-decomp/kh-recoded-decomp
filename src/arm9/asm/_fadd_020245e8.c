/* Runtime single-precision add helper. */

extern void func_02024824(void);

asm void _fadd_020245e8(void)
{
    eors      r2, r0, r1
    eormi     r1, r1, #0x80000000
    bmi       func_02024824
    subs      r12, r0, r1
    sublo     r0, r0, r12
    addlo     r1, r1, r12
    mov       r2, #0x80000000
    mov       r3, r0, lsr #0x17
    orr       r0, r2, r0, lsl #8
    ands      r12, r3, #0xff
    cmpne     r12, #0xff
    beq       L0a0
    mov       r12, r1, lsr #0x17
    orr       r1, r2, r1, lsl #8
    ands      r2, r12, #0xff
    beq       L0e0
L040:
    subs      r12, r3, r12
    beq       L058
    rsb       r2, r12, #0x20
    movs      r2, r1, lsl r2
    mov       r1, r1, lsr r12
    orrne     r1, r1, #1
L058:
    adds      r0, r0, r1
    blo       L078
    and       r1, r0, #1
    orr       r0, r1, r0, rrx
    add       r3, r3, #1
    and       r2, r3, #0xff
    cmp       r2, #0xff
    beq       L1e8
L078:
    ands      r1, r0, #0xff
    add       r0, r0, r0
    mov       r0, r0, lsr #9
    orr       r0, r0, r3, lsl #23
    tst       r1, #0x80
    bxeq      lr
    ands      r1, r1, #0x7f
    andeqs    r1, r0, #1
    addne     r0, r0, #1
    bx        lr
L0a0:
    cmp       r3, #0x100
    movge     r2, #0x80000000
    movlt     r2, #0
    ands      r3, r3, #0xff
    beq       L104
    movs      r0, r0, lsl #1
    bne       L214
    mov       r12, r1, lsr #0x17
    mov       r1, r1, lsl #9
    ands      r12, r12, #0xff
    beq       L208
    cmp       r12, #0xff
    blt       L208
    cmp       r1, #0
    beq       L208
    b         L214
L0e0:
    cmp       r3, #0x100
    movge     r2, #0x80000000
    movlt     r2, #0
    and       r3, r3, #0xff
    ands      r12, r12, #0xff
    beq       L160
L0f8:
    movs      r1, r1, lsl #1
    bne       L214
    b         L208
L104:
    movs      r0, r0, lsl #1
    beq       L13c
    mov       r3, #1
    mov       r0, r0, lsr #1
    mov       r12, r1, lsr #0x17
    mov       r1, r1, lsl #8
    ands      r12, r12, #0xff
    beq       L160
    cmp       r12, #0xff
    beq       L0f8
    orr       r1, r1, #0x80000000
    orr       r3, r3, r2, lsr #23
    orr       r12, r12, r2, lsr #23
    b         L040
L13c:
    mov       r3, r1, lsr #0x17
    mov       r0, r1, lsl #9
    ands      r3, r3, #0xff
    beq       L1c8
    cmp       r3, #0xff
    blt       L1c8
    cmp       r0, #0
    beq       L208
    b         L200
L160:
    movs      r1, r1, lsl #1
    beq       L1d0
    mov       r1, r1, lsr #1
    mov       r12, #1
    orr       r3, r3, r2, lsr #23
    orr       r12, r12, r2, lsr #23
    cmp       r0, #0
    bmi       L040
    adds      r0, r0, r1
    blo       L194
    and       r1, r0, #1
    orr       r0, r1, r0, rrx
    add       r12, r12, #1
L194:
    cmp       r0, #0
    subge     r12, r12, #1
    ands      r1, r0, #0xff
    add       r0, r0, r0
    mov       r0, r0, lsr #9
    orr       r0, r0, r12, lsl #23
    bxeq      lr
    tst       r1, #0x80
    bxeq      lr
    ands      r1, r1, #0x7f
    andeqs    r1, r0, #1
    addne     r0, r0, #1
    bx        lr
L1c8:
    mov       r0, r1
    bx        lr
L1d0:
    cmp       r0, #0
    subges    r3, r3, #1
    add       r0, r0, r0
    orr       r0, r2, r0, lsr #9
    orr       r0, r0, r3, lsl #23
    bx        lr
L1e8:
    cmp       r3, #0x100
    movge     r2, #0x80000000
    movlt     r2, #0
    mov       r0, #0xff000000
    orr       r0, r2, r0, lsr #1
    bx        lr
L200:
    mvn       r0, #0x80000000
    bx        lr
L208:
    mov       r0, #0xff000000
    orr       r0, r2, r0, lsr #1
    bx        lr
L214:
    mvn       r0, #0x80000000
    bx        lr
}
