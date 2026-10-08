extern void func_02023aa4(void);

/* Runtime long long to float conversion helper. */
asm float _ll2f_02023b28(long long value)
{
    ands r2, r1, #0x80000000
    beq @positive
    rsbs r0, r0, #0
    rsc r1, r1, #0
@positive:
    cmp r1, #0
    bne @wide
    movs r0, r0
    b func_02023aa4
@wide:
    clz r3, r1
    movs r1, r1, lsl r3
    rsb r3, r3, #0x20
    orr r1, r1, r0, lsr r3
    rsb r12, r3, #0x20
    movs r0, r0, lsl r12
    orrne r1, r1, #1
    add r3, r3, #0x9e
    ands r12, r1, #0xff
    add r0, r1, r1
    orr r0, r2, r0, lsr #9
    orr r0, r0, r3, lsl #23
    bxeq lr
    tst r12, #0x80
    bxeq lr
    ands r3, r12, #0x7f
    andeqs r3, r0, #1
    addne r0, r0, #1
    bx lr
}
