/* SDK ITCM memory routine. */

extern void func_01ff9094(void);

asm void func_01ff8e84(void)
{
    stmdb     sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs      r2, r2, #0x20
L008:
    ldmgedb   r0!, {r4, r5, r6, r7, r8, r9, r10, lr}
    stmgedb   r1!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subges    r2, r2, #0x20
    bge       L008
    add       r2, r2, #0x20
    ldmia     sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    subs      r2, r2, #4
L024:
    ldrge     r3, [r0, #-4]!
    strge     r3, [r1, #-4]!
    subges    r2, r2, #4
    bge       L024
    add       r2, r2, #4
    b         func_01ff9094
}
