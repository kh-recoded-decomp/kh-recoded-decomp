/* SDK ITCM memory routine. */

extern void func_01ff8ad8(void);
extern void func_01ff8e84(void);
extern void func_01ff8ec0(void);
extern void func_01ff8f5c(void);
extern void func_01ff8ff8(void);

asm void func_01ff8dc8(void)
{
    cmp       r2, #0
    subnes    r3, r0, r1
    bxeq      lr
    bgt       func_01ff8ad8
    add       r1, r1, r2
    add       r0, r0, r2
    cmp       r2, #8
    bgt       L070
    rsb       r3, r2, #8
    add       pc, pc, r3, lsl #3
    mov       r0, r0
    ldrb      r3, [r0, #-1]!
    strb      r3, [r1, #-1]!
    ldrb      r3, [r0, #-1]!
    strb      r3, [r1, #-1]!
    ldrb      r3, [r0, #-1]!
    strb      r3, [r1, #-1]!
    ldrb      r3, [r0, #-1]!
    strb      r3, [r1, #-1]!
    ldrb      r3, [r0, #-1]!
    strb      r3, [r1, #-1]!
    ldrb      r3, [r0, #-1]!
    strb      r3, [r1, #-1]!
    ldrb      r3, [r0, #-1]!
    strb      r3, [r1, #-1]!
    ldrb      r3, [r0, #-1]!
    strb      r3, [r1, #-1]!
    bx        lr
L070:
    tst       r0, #2
    subne     r2, r2, #2
    ldrneb    r3, [r0, #-1]!
    strneb    r3, [r1, #-1]!
    ldrneb    r3, [r0, #-1]!
    strneb    r3, [r1, #-1]!
    tst       r0, #1
    subne     r2, r2, #1
    ldrneb    r3, [r0, #-1]!
    strneb    r3, [r1, #-1]!
    and       r3, r1, #3
    bic       r1, r1, #3
    cmp       r3, #0
    beq       func_01ff8e84
    cmp       r3, #1
    beq       func_01ff8ec0
    cmp       r3, #2
    beq       func_01ff8f5c
    b         func_01ff8ff8
}
