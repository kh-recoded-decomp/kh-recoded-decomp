/* MobiClip decoder routine, hand-written ARM. */

asm void func_ov022_020b726c(void)
{
    stmfd     sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
    ldr       lr, [r0, #0x10]
    ldr       r12, [r0, #0x14]
    ldr       r1, [r0, #4]
    ldr       r11, [r0]
    ldr       r3, [r0, #0xc]
    ldr       r2, [r11], #4
    ldr       r10, [r0, #8]
    str       r3, [sp, #-4]!
    str       r2, [r1], #4
    sub       r10, r10, #8
L02c:
    str       r10, [sp, #-4]!
    ldrb      r2, [r11], #1
    ldrb      r3, [r11], #1
    ldrb      r4, [r11], #1
    ldrb      r5, [r11], #1
    ldrb      r6, [r11], #1
    ldrb      r7, [r11], #1
    ldrb      r8, [r11], #1
    and       r9, lr, #0xff
    subs      r10, r5, r6
    rsblt     r10, r10, #0
    cmp       r10, r9
    bge       L0d4
    subs      r10, r4, r5
    rsblt     r10, r10, #0
    cmp       r10, lr, lsr #8
    bge       L0d4
    subs      r10, r7, r6
    rsblt     r10, r10, #0
    cmp       r10, lr, lsr #8
    bge       L0d4
    add       r10, r5, r6
    add       r10, r10, #1
    subs      r9, r3, r5
    sub       r5, r4, r7
    add       r5, r5, #4
    mov       r5, r5, asr #3
    rsblt     r9, r9, #0
    cmp       r9, lr, lsr #8
    addlt     r4, r3, r10, asr #1
    addlt     r4, r4, #1
    movlt     r4, r4, asr #1
    subs      r9, r8, r6
    rsblt     r9, r9, #0
    cmp       r9, lr, lsr #8
    addlt     r7, r8, r10, asr #1
    addlt     r7, r7, #1
    movlt     r7, r7, asr #1
    rsb       r6, r5, r10, asr #1
    ldrb      r6, [r12, r6]
    add       r5, r5, r10, asr #1
    ldrb      r5, [r12, r5]
L0d4:
    ldrb      r9, [r11], #1
    orr       r2, r2, r3, lsl #8
    orr       r2, r2, r4, lsl #16
    orr       r2, r2, r5, lsl #24
    orr       r6, r6, r7, lsl #8
    orr       r6, r6, r8, lsl #16
    orr       r6, r6, r9, lsl #24
    stmia     r1!, {r2, r6}
    ldr       r10, [sp], #4
    subs      r10, r10, #8
    bne       L02c
    ldr       r3, [sp], #4
    ldr       r2, [r11], #4
    ldr       r10, [r0, #8]
    add       r11, r11, #0x100
    str       r2, [r1], #0x104
    sub       r11, r11, r10
    sub       r1, r1, r10
    subs      r3, r3, #1
    ldrne     r2, [r11], #4
    strne     r3, [sp, #-4]!
    subne     r10, r10, #8
    strne     r2, [r1], #4
    bne       L02c
    ldmfd     sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, pc}
}
