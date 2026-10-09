/* Runtime unsigned 64-bit divide helper. */

extern void func_02023c18(void);
extern void func_02023fd0(void);

asm void _ll_udiv_02023d54(void)
{
    stmfd     sp!, {r4, r5, r6, r7, r11, r12, lr}
    mov       r4, #0
    b         L014
    stmfd     sp!, {r4, r5, r6, r7, r11, r12, lr}
    mov       r4, #1
L014:
    orrs      r5, r3, r2
    bne       L024
    ldmfd     sp!, {r4, r5, r6, r7, r11, r12, lr}
    bx        lr
L024:
    orrs      r5, r1, r3
    bne       func_02023c18
    mov       r1, r2
    bl        func_02023fd0
    cmp       r4, #0
    movne     r0, r1
    mov       r1, #0
    ldmfd     sp!, {r4, r5, r6, r7, r11, r12, lr}
    bx        lr
}
