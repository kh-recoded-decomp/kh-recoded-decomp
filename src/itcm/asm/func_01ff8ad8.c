/* SDK ITCM memory routine. */

extern void func_01ff8b7c(void);
extern void func_01ff8bb8(void);
extern void func_01ff8c50(void);
extern void func_01ff8ce8(void);

asm void func_01ff8ad8(void)
{
    cmp       r2, #8
    bgt       L058
    rsb       r3, r2, #8
    add       pc, pc, r3, lsl #3
    mov       r0, r0
    ldrb      r3, [r0], #1
    strb      r3, [r1], #1
    ldrb      r3, [r0], #1
    strb      r3, [r1], #1
    ldrb      r3, [r0], #1
    strb      r3, [r1], #1
    ldrb      r3, [r0], #1
    strb      r3, [r1], #1
    ldrb      r3, [r0], #1
    strb      r3, [r1], #1
    ldrb      r3, [r0], #1
    strb      r3, [r1], #1
    ldrb      r3, [r0], #1
    strb      r3, [r1], #1
    ldrb      r3, [r0], #1
    strb      r3, [r1], #1
    bx        lr
L058:
    tst       r0, #1
    subne     r2, r2, #1
    ldrneb    r3, [r0], #1
    strneb    r3, [r1], #1
    tst       r0, #2
    subne     r2, r2, #2
    ldrneb    r3, [r0], #1
    strneb    r3, [r1], #1
    ldrneb    r3, [r0], #1
    strneb    r3, [r1], #1
    and       r3, r1, #3
    bic       r1, r1, #3
    cmp       r3, #0
    beq       func_01ff8b7c
    cmp       r3, #1
    beq       func_01ff8bb8
    cmp       r3, #2
    beq       func_01ff8c50
    b         func_01ff8ce8
}
