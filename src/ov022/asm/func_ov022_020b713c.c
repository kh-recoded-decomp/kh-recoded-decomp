/* MobiClip decoder routine, hand-written ARM. */

extern void func_020b726c(void);
extern void func_020b73a4(void);
extern void func_020b7498(void);
extern void func_020b75a0(void);

asm void func_ov022_020b713c(void)
{
    stmfd     sp!, {r4, r5, r6, r7, r8, r9, lr}
    sub       sp, sp, #0x18
    mov       r4, r0
    ldr       r5, [r4, #0x18]
    add       r6, pc, #0xc0
    ldrb      r6, [r6, r5]
    add       r7, pc, #0xdd
    ldrb      r7, [r7, r5]
    orr       r6, r6, r7, lsl #8
    str       r6, [sp, #0x10]
    ldr       r5, [r4]
    ldr       r6, [r4, #8]
    ldr       r7, [r4, #0x10]
    ldr       r8, [r4, #0x14]
    ldr       r9, [r4, #0x1c]
    str       r5, [sp]
    str       r6, [sp, #4]
    str       r7, [sp, #8]
    str       r8, [sp, #0xc]
    add       r9, r9, #0x40
    str       r9, [sp, #0x14]
    mov       r0, sp
    bl        func_020b726c
    ldr       r0, [r4, #0x20]
    cmp       r0, #1
    movne     r0, sp
    blne      func_020b73a4
    ldr       r5, [r4, #4]
    ldr       r6, [r4, #0xc]
    ldr       r7, [r4, #0x10]
    ldr       r8, [r4, #0x14]
    str       r5, [sp]
    str       r6, [sp, #4]
    mov       r7, r7, asr #1
    mov       r8, r8, asr #1
    str       r7, [sp, #8]
    str       r8, [sp, #0xc]
    mov       r0, sp
    bl        func_020b7498
    ldr       r0, [r4, #0x20]
    cmp       r0, #1
    movne     r0, sp
    blne      func_020b75a0
    ldr       r5, [r4, #4]
    ldr       r6, [r4, #0xc]
    add       r5, r5, #0x80
    add       r6, r6, #0x80
    str       r5, [sp]
    str       r6, [sp, #4]
    mov       r0, sp
    bl        func_020b7498
    ldr       r0, [r4, #0x20]
    cmp       r0, #1
    movne     r0, sp
    blne      func_020b75a0
    add       sp, sp, #0x18
    ldmfd     sp!, {r4, r5, r6, r7, r8, r9, pc}
}
