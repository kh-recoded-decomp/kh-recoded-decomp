/* SDK ITCM memory routine. */

extern void func_01ff8d80(void);

asm void func_01ff8ce8(void)
{
    ldr       ip, [r1]
    mov       ip, ip, lsl #8
    mov       ip, ip, lsr #8
    stmdb     sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs      r2, r2, #0x20
L014:
    ldmgeia   r0!, {r4, r5, r6, r7, r8, r9, r10, lr}
    movge     r3, r4, lsr #8
    orrge     r4, ip, r4, lsl #24
    movge     ip, r5, lsr #8
    orrge     r5, r3, r5, lsl #24
    movge     r3, r6, lsr #8
    orrge     r6, ip, r6, lsl #24
    movge     ip, r7, lsr #8
    orrge     r7, r3, r7, lsl #24
    movge     r3, r8, lsr #8
    orrge     r8, ip, r8, lsl #24
    movge     ip, r9, lsr #8
    orrge     r9, r3, r9, lsl #24
    movge     r3, r10, lsr #8
    orrge     r10, ip, r10, lsl #24
    movge     ip, lr, lsr #8
    orrge     lr, r3, lr, lsl #24
    stmgeia   r1!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subges    r2, r2, #0x20
    bge       L014
    add       r2, r2, #0x20
    ldmia     sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs      r2, r2, #4
L070:
    ldrge     r3, [r0], #4
    orrge     ip, ip, r3, lsl #24
    strge     ip, [r1], #4
    movge     ip, r3, lsr #8
    subges    r2, r2, #4
    bge       L070
    add       r2, r2, #4
    sub       r0, r0, #3
    add       r2, r2, #3
    b         func_01ff8d80
}
