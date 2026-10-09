/* SDK ITCM memory routine. */

extern void func_01ff840c(void);

asm void func_01ff833c(void)
{
    mov       r12, #0x4000000
    str       r12, [r12, #0x208]
    ldr       r1, =0x27e0000
    add       r1, r1, #0x3fc0
    add       r1, r1, #0x3c
    mov       r0, #0
    str       r0, [r1]
    ldr       r1, =0x4000180
L020:
    ldrh      r0, [r1]
    and       r0, r0, #0xf
    cmp       r0, #1
    bne       L020
    mov       r0, #0x100
    strh      r0, [r1]
    mov       r0, #0
    ldr       r3, =0x2ffff9c
    ldr       r4, [r3]
    ldr       r1, =0x2fffd80
    mov       r2, #0x80
    bl        func_01ff840c
    ldr       r3, =0x2fffd9c
    str       r4, [r3]
    ldr       r1, =0x2ffff80
    mov       r2, #0x18
    bl        func_01ff840c
    ldr       r1, =0x2ffff98
    strh      r0, [r1]
    ldr       r1, =0x2ffff9c
    mov       r2, #0x64
    bl        func_01ff840c
    ldr       r1, =0x4000180
L07c:
    ldrh      r0, [r1]
    and       r0, r0, #0xf
    cmp       r0, #1
    beq       L07c
    mov       r0, #0
    strh      r0, [r1]
    ldr       r3, =0x2fffe00
    ldr       r12, [r3, #0x24]
    mov       lr, r12
    ldr       r11, =0x2ffff80
    ldmia     r11, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10}
    mov       r11, #0
    bx        r12
}
