/* SDK ITCM memory routine. */

extern void func_01ff9094(void);

asm void func_01ff8ff8(void)
{
    ldr       ip, [r1]
    mov       ip, ip, lsr #0x18
    mov       ip, ip, lsl #0x18
    stmdb     sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs      r2, r2, #0x20
L014:
    ldmgedb   r0!, {r4, r5, r6, r7, r8, r9, r10, lr}
    movge     r3, lr, lsl #0x18
    orrge     lr, ip, lr, lsr #8
    movge     ip, r10, lsl #0x18
    orrge     r10, r3, r10, lsr #8
    movge     r3, r9, lsl #0x18
    orrge     r9, ip, r9, lsr #8
    movge     ip, r8, lsl #0x18
    orrge     r8, r3, r8, lsr #8
    movge     r3, r7, lsl #0x18
    orrge     r7, ip, r7, lsr #8
    movge     ip, r6, lsl #0x18
    orrge     r6, r3, r6, lsr #8
    movge     r3, r5, lsl #0x18
    orrge     r5, ip, r5, lsr #8
    movge     ip, r4, lsl #0x18
    orrge     r4, r3, r4, lsr #8
    stmgeda   r1!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subges    r2, r2, #0x20
    bge       L014
    add       r2, r2, #0x20
    ldmia     sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs      r2, r2, #4
L070:
    ldrge     r3, [r0, #-4]!
    orrge     ip, ip, r3, lsr #8
    strge     ip, [r1], #-4
    movge     ip, r3, lsl #0x18
    subges    r2, r2, #4
    bge       L070
    add       r2, r2, #4
    add       r1, r1, #4
    add       r0, r0, #1
    add       r2, r2, #1
    b         func_01ff9094
}
