/* Runtime double-precision add helper. */

extern void func_02022e30(void);

asm void _dadd_02022af0(void)
{
    stmfd     sp!, {r4, lr}
    eors      r12, r1, r3
    eormi     r3, r3, #0x80000000
    bmi       func_02022e30
    subs      r12, r0, r2
    sbcs      lr, r1, r3
    bhs       L02c
    adds      r2, r2, r12
    adc       r3, r3, lr
    subs      r0, r0, r12
    sbc       r1, r1, lr
L02c:
    mov       lr, #0x80000000
    mov       r12, r1, lsr #0x14
    orr       r1, lr, r1, lsl #11
    orr       r1, r1, r0, lsr #21
    mov       r0, r0, lsl #0xb
    movs      r4, r12, lsl #0x15
    cmnne     r4, #0x200000
    beq       L128
    mov       r4, r3, lsr #0x14
    orr       r3, lr, r3, lsl #11
    orr       r3, r3, r2, lsr #21
    mov       r2, r2, lsl #0xb
    movs      lr, r4, lsl #0x15
    beq       L170
L064:
    subs      r4, r12, r4
    beq       L0bc
    cmp       r4, #0x20
    ble       L0a0
    cmp       r4, #0x38
    movge     r4, #0x3f
    sub       r4, r4, #0x20
    rsb       lr, r4, #0x20
    orrs      lr, r2, r3, lsl lr
    mov       r2, r3, lsr r4
    orrne     r2, r2, #1
    adds      r0, r0, r2
    adcs      r1, r1, #0
    blo       L0e4
    b         L0c8
L0a0:
    rsb       lr, r4, #0x20
    movs      lr, r2, lsl lr
    rsb       lr, r4, #0x20
    mov       r2, r2, lsr r4
    orr       r2, r2, r3, lsl lr
    mov       r3, r3, lsr r4
    orrne     r2, r2, #1
L0bc:
    adds      r0, r0, r2
    adcs      r1, r1, r3
    blo       L0e4
L0c8:
    add       r12, r12, #1
    and       r4, r0, #1
    movs      r1, r1, rrx
    orr       r0, r4, r0, rrx
    mov       lr, r12, lsl #0x15
    cmn       lr, #0x200000
    beq       L2f4
L0e4:
    movs      r2, r0, lsl #0x15
    mov       r0, r0, lsr #0xb
    orr       r0, r0, r1, lsl #21
    add       r1, r1, r1
    mov       r1, r1, lsr #0xc
    orr       r1, r1, r12, lsl #20
    tst       r2, #0x80000000
    ldmeqfd   sp!, {r4, lr}
    bxeq      lr
    movs      r2, r2, lsl #1
    andeqs    r2, r0, #1
    ldmeqfd   sp!, {r4, lr}
    bxeq      lr
    adds      r0, r0, #1
    adc       r1, r1, #0
    ldmfd     sp!, {r4, lr}
    bx        lr
L128:
    cmp       r12, #0x800
    movge     lr, #0x80000000
    movlt     lr, #0
    bics      r12, r12, #0x800
    beq       L194
    orrs      r4, r0, r1, lsl #1
    bne       L2d0
    mov       r4, r3, lsr #0x14
    mov       r3, r3, lsl #0xb
    orr       r3, r3, r2, lsr #21
    mov       r2, r2, lsl #0xb
    movs      r4, r4, lsl #0x15
    beq       L2bc
    cmn       r4, #0x200000
    bne       L2bc
    orrs      r4, r2, r3, lsl #1
    beq       L2bc
    b         L2d0
L170:
    cmp       r4, #0x800
    movge     lr, #0x80000000
    movlt     lr, #0
    bic       r12, r12, #0x800
    bics      r4, r4, #0x800
    beq       L200
    orrs      r4, r2, r3, lsl #1
    bne       L2d0
    b         L2bc
L194:
    orrs      r4, r0, r1, lsl #1
    beq       L1d4
    mov       r12, #1
    bic       r1, r1, #0x80000000
    mov       r4, r3, lsr #0x14
    mov       r3, r3, lsl #0xb
    orr       r3, r3, r2, lsr #21
    mov       r2, r2, lsl #0xb
    movs      r4, r4, lsl #0x15
    cmnne     r4, #0x200000
    mov       r4, r4, lsr #0x15
    orr       r4, r4, lr, lsr #20
    beq       L170
    orr       r3, r3, #0x80000000
    orr       r12, r12, lr, lsr #20
    b         L064
L1d4:
    mov       r12, r3, lsr #0x14
    mov       r1, r3, lsl #0xb
    orr       r1, r1, r2, lsr #21
    mov       r0, r2, lsl #0xb
    movs      r4, r12, lsl #0x15
    beq       L288
    cmn       r4, #0x200000
    bne       L288
    orrs      r4, r0, r1, lsl #1
    beq       L2bc
    b         L2d4
L200:
    orrs      r4, r2, r3, lsl #1
    beq       L298
    mov       r4, #1
    bic       r3, r3, #0x80000000
    cmp       r1, #0
    bpl       L224
    orr       r12, r12, lr, lsr #20
    orr       r4, r4, lr, lsr #20
    b         L064
L224:
    adds      r0, r0, r2
    adcs      r1, r1, r3
    blo       L244
    add       r12, r12, #1
    and       r4, r0, #1
    movs      r1, r1, rrx
    mov       r0, r0, rrx
    orr       r0, r0, r4
L244:
    cmp       r1, #0
    subges    r12, r12, #1
    movs      r2, r0, lsl #0x15
    mov       r0, r0, lsr #0xb
    orr       r0, r0, r1, lsl #21
    add       r1, r1, r1
    orr       r1, lr, r1, lsr #12
    orr       r1, r1, r12, lsl #20
    ldmeqfd   sp!, {r4, lr}
    bxeq      lr
    tst       r2, #0x80000000
    ldmeqfd   sp!, {r4, lr}
    bxeq      lr
    movs      r2, r2, lsl #1
    andeqs    r2, r0, #1
    ldmeqfd   sp!, {r4, lr}
    bxeq      lr
L288:
    mov       r1, r3
    mov       r0, r2
    ldmfd     sp!, {r4, lr}
    bx        lr
L298:
    cmp       r1, #0
    subges    r12, r12, #1
    mov       r0, r0, lsr #0xb
    orr       r0, r0, r1, lsl #21
    add       r1, r1, r1
    orr       r1, lr, r1, lsr #12
    orr       r1, r1, r12, lsl #20
    ldmfd     sp!, {r4, lr}
    bx        lr
L2bc:
    ldr       r1, =0x7ff00000
    orr       r1, lr, r1
    mov       r0, #0
    ldmfd     sp!, {r4, lr}
    bx        lr
L2d0:
    mov       r1, r3
L2d4:
    mvn       r0, #0
    bic       r1, r0, #0x80000000
    ldmfd     sp!, {r4, lr}
    bx        lr
    mvn       r0, #0
    bic       r1, r0, #0x80000000
    ldmfd     sp!, {r4, lr}
    bx        lr
L2f4:
    cmp       r12, #0x800
    movge     lr, #0x80000000
    movlt     lr, #0
    ldr       r1, =0x7ff00000
    orr       r1, lr, r1
    mov       r0, #0
    ldmfd     sp!, {r4, lr}
    bx        lr
}
