/* SDK ITCM memory routine. */

extern void func_01ff8d80(void);

asm void func_01ff8c50(void)
{
    ldr       ip, [r1]
    mov       ip, ip, lsl #0x10
    mov       ip, ip, lsr #0x10
    stmdb     sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs      r2, r2, #0x20
L014:
    ldmgeia   r0!, {r4, r5, r6, r7, r8, r9, r10, lr}
    movge     r3, r4, lsr #0x10
    orrge     r4, ip, r4, lsl #16
    movge     ip, r5, lsr #0x10
    orrge     r5, r3, r5, lsl #16
    movge     r3, r6, lsr #0x10
    orrge     r6, ip, r6, lsl #16
    movge     ip, r7, lsr #0x10
    orrge     r7, r3, r7, lsl #16
    movge     r3, r8, lsr #0x10
    orrge     r8, ip, r8, lsl #16
    movge     ip, r9, lsr #0x10
    orrge     r9, r3, r9, lsl #16
    movge     r3, r10, lsr #0x10
    orrge     r10, ip, r10, lsl #16
    movge     ip, lr, lsr #0x10
    orrge     lr, r3, lr, lsl #16
    stmgeia   r1!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subges    r2, r2, #0x20
    bge       L014
    add       r2, r2, #0x20
    ldmia     sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs      r2, r2, #4
L070:
    ldrge     r3, [r0], #4
    orrge     ip, ip, r3, lsl #16
    strge     ip, [r1], #4
    movge     ip, r3, lsr #0x10
    subges    r2, r2, #4
    bge       L070
    add       r2, r2, #4
    sub       r0, r0, #2
    add       r2, r2, #2
    b         func_01ff8d80
}
