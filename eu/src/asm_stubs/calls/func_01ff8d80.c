/* SDK ITCM memory routine. */


asm void func_01ff8d80(void)
{
    tst       r2, #4
    ldrneb    r3, [r0], #1
    strneb    r3, [r1], #1
    ldrneb    r3, [r0], #1
    strneb    r3, [r1], #1
    ldrneb    r3, [r0], #1
    strneb    r3, [r1], #1
    ldrneb    r3, [r0], #1
    strneb    r3, [r1], #1
    tst       r2, #2
    ldrneb    r3, [r0], #1
    strneb    r3, [r1], #1
    ldrneb    r3, [r0], #1
    strneb    r3, [r1], #1
    tst       r2, #1
    ldrneb    r3, [r0], #1
    strneb    r3, [r1], #1
    bx        lr
}
