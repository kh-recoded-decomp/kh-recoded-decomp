extern void func_020245f4(void);

/* Runtime single-precision float subtract helper. */
asm float _fsub_02024818(float left, float right)
{
    eors r2, r0, r1
    eormi r1, r1, #0x80000000
    bmi func_020245f4
    subs r12, r0, r1
    eorlo r12, r12, #0x80000000
    sublo r0, r0, r12
    addlo r1, r1, r12
    mov r2, #0x80000000
    mov r3, r0, lsr #0x17
    orr r0, r2, r0, lsl #8
    ands r12, r3, #0xff
    cmpne r12, #0xff
    beq @L128
    mov r12, r1, lsr #0x17
    orr r1, r2, r1, lsl #8
    ands r2, r12, #0xff
    beq @L168
@L044:
    subs r12, r3, r12
    beq @L08c
    rsb r2, r12, #0x20
    movs r2, r1, lsl r2
    mov r1, r1, lsr r12
    orrne r1, r1, #1
    subs r0, r0, r1
    bpl @L0d0
    ands r1, r0, #0xff
    add r0, r0, r0
    mov r0, r0, lsr #9
    orr r0, r0, r3, lsl #23
    tst r1, #0x80
    bxeq lr
    ands r1, r1, #0x7f
    andeqs r1, r0, #1
    addne r0, r0, #1
    bx lr
@L08c:
    subs r0, r0, r1
    beq @L234
    mov r2, r3, lsl #0x17
    and r2, r2, #0x80000000
    bic r3, r3, #0x100
    clz r12, r0
    movs r0, r0, lsl r12
    sub r3, r3, r12
    cmp r3, #0
    bgt @L0c0
    rsb r3, r3, #9
    orr r0, r2, r0, lsr r3
    bx lr
@L0c0:
    add r0, r0, r0
    orr r0, r2, r0, lsr #9
    orr r0, r0, r3, lsl #23
    bx lr
@L0d0:
    mov r2, r3, lsl #0x17
    and r2, r2, #0x80000000
    bic r3, r3, #0x100
    clz r12, r0
    movs r0, r0, lsl r12
    sub r3, r3, r12
    cmp r3, #0
    bgt @L0fc
    rsb r3, r3, #9
    orr r0, r2, r0, lsr r3
    bx lr
@L0fc:
    ands r1, r0, #0xff
    add r0, r0, r0
    orr r0, r2, r0, lsr #9
    orr r0, r0, r3, lsl #23
    bxeq lr
    tst r1, #0x80
    bxeq lr
    ands r1, r1, #0x7f
    andeqs r1, r0, #1
    addne r0, r0, #1
    bx lr
@L128:
    cmp r3, #0x100
    movge r2, #0x80000000
    movlt r2, #0
    ands r3, r3, #0xff
    beq @L190
    movs r0, r0, lsl #1
    bne @L268
    mov r12, r1, lsr #0x17
    mov r1, r1, lsl #9
    ands r12, r12, #0xff
    beq @L25c
    cmp r12, #0xff
    blt @L25c
    cmp r1, #0
    beq @L270
    b @L268
@L168:
    cmp r12, #0x100
    movge r2, #0x80000000
    movlt r2, #0
    and r3, r3, #0xff
    ands r12, r12, #0xff
    beq @L1f8
@L180:
    eor r2, r2, #0x80000000
    movs r1, r1, lsl #1
    bne @L268
    b @L25c
@L190:
    movs r0, r0, lsl #1
    beq @L1c8
    mov r0, r0, lsr #1
    mov r3, #1
    mov r12, r1, lsr #0x17
    mov r1, r1, lsl #8
    ands r12, r12, #0xff
    beq @L1f8
    cmp r12, #0xff
    beq @L180
    orr r1, r1, #0x80000000
    orr r3, r3, r2, lsr #23
    orr r12, r12, r2, lsr #23
    b @L044
@L1c8:
    mov r3, r1, lsr #0x17
    mov r0, r1, lsl #9
    ands r2, r3, #0xff
    beq @L1ec
    cmp r2, #0xff
    blt @L214
    cmp r0, #0
    bne @L254
    b @L25c
@L1ec:
    cmp r0, #0
    beq @L234
    b @L214
@L1f8:
    movs r1, r1, lsl #1
    beq @L21c
    mov r1, r1, lsr #1
    mov r12, #1
    orr r12, r12, r2, lsr #23
    orr r3, r3, r2, lsr #23
    b @L044
@L214:
    mov r0, r1
    bx lr
@L21c:
    cmp r0, #0
    subges r3, r3, #1
    add r0, r0, r0
    orr r0, r2, r0, lsr #9
    orr r0, r0, r3, lsl #23
    bx lr
@L234:
    mov r0, #0
    bx lr
    cmp r0, #0
    subges r3, r3, #1
    add r0, r0, r0
    mov r0, r0, lsr #9
    orr r0, r0, r3, lsl #23
    bx lr
@L254:
    mvn r0, #0x80000000
    bx lr
@L25c:
    mov r0, #0xff000000
    orr r0, r2, r0, lsr #1
    bx lr
@L268:
    mvn r0, #0x80000000
    bx lr
@L270:
    mvn r0, #0x80000000
    bx lr
}
