/* Runtime soft-float helper. */

extern void func_02023dbc(void);

asm void func_02023b94(void)
{
    stmfd     sp!, {r4, r5, r6, r7, r11, r12, lr}
    mov       r4, r1
    orr       r4, r4, #1
    b         L020
    stmfd     sp!, {r4, r5, r6, r7, r11, r12, lr}
    eor       r4, r1, r3
    mov       r4, r4, asr #1
    mov       r4, r4, lsl #1
L020:
    orrs      r5, r3, r2
    bne       L030
    ldmfd     sp!, {r4, r5, r6, r7, r11, r12, lr}
    bx        lr
L030:
    mov       r5, r0, lsr #0x1f
    add       r5, r5, r1
    mov       r6, r2, lsr #0x1f
    add       r6, r6, r3
    orrs      r6, r5, r6
    bne       L064
    mov       r1, r2
    bl        func_02023dbc
    ands      r4, r4, #1
    movne     r0, r1
    mov       r1, r0, asr #0x1f
    ldmfd     sp!, {r4, r5, r6, r7, r11, r12, lr}
    bx        lr
L064:
    cmp       r1, #0
    bge       L074
    rsbs      r0, r0, #0
    rsc       r1, r1, #0
L074:
    cmp       r3, #0
    bge       L084
    rsbs      r2, r2, #0
    rsc       r3, r3, #0
L084:
    orrs      r5, r1, r0
    beq       L1a8
    mov       r5, #0
    mov       r6, #1
    cmp       r3, #0
    bmi       L0b0
L09c:
    add       r5, r5, #1
    adds      r2, r2, r2
    adcs      r3, r3, r3
    bpl       L09c
    add       r6, r6, r5
L0b0:
    cmp       r1, #0
    blt       L0d0
L0b8:
    cmp       r6, #1
    beq       L0d0
    sub       r6, r6, #1
    adds      r0, r0, r0
    adcs      r1, r1, r1
    bpl       L0b8
L0d0:
    mov       r7, #0
    mov       r12, #0
    mov       r11, #0
    b         L0f8
L0e0:
    orr       r12, r12, #1
    subs      r6, r6, #1
    beq       L150
    adds      r0, r0, r0
    adcs      r1, r1, r1
    adcs      r7, r7, r7
L0f8:
    subs      r0, r0, r2
    sbcs      r1, r1, r3
    sbcs      r7, r7, #0
    adds      r12, r12, r12
    adc       r11, r11, r11
    cmp       r7, #0
    bge       L0e0
L114:
    subs      r6, r6, #1
    beq       L148
    adds      r0, r0, r0
    adcs      r1, r1, r1
    adc       r7, r7, r7
    adds      r0, r0, r2
    adcs      r1, r1, r3
    adc       r7, r7, #0
    adds      r12, r12, r12
    adc       r11, r11, r11
    cmp       r7, #0
    bge       L0e0
    b         L114
L148:
    adds      r0, r0, r2
    adc       r1, r1, r3
L150:
    ands      r7, r4, #1
    moveq     r0, r12
    moveq     r1, r11
    beq       L188
    subs      r7, r5, #0x20
    movge     r0, r1, lsr r7
    bge       L1ac
    rsb       r7, r5, #0x20
    mov       r0, r0, lsr r5
    orr       r0, r0, r1, lsl r7
    mov       r1, r1, lsr r5
    b         L188
    mov       r0, r1, lsr r7
    mov       r1, #0
L188:
    cmp       r4, #0
    blt       L198
    ldmfd     sp!, {r4, r5, r6, r7, r11, r12, lr}
    bx        lr
L198:
    rsbs      r0, r0, #0
    rsc       r1, r1, #0
    ldmfd     sp!, {r4, r5, r6, r7, r11, r12, lr}
    bx        lr
L1a8:
    mov       r0, #0
L1ac:
    mov       r1, #0
    cmp       r4, #0
    blt       L198
    ldmfd     sp!, {r4, r5, r6, r7, r11, r12, lr}
    bx        lr
}
