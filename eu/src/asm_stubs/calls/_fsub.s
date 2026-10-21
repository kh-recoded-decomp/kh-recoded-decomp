/* MSL runtime single-precision subtract (original assembly) */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global _fsub
    .type _fsub, %function
_fsub:
    eors r2, r0, r1
    eormi r1, r1, #0x80000000
    bmi func_02024608
    .global func_02024838
    .type func_02024838, %function
func_02024838:
    subs ip, r0, r1
    eorlo ip, ip, #0x80000000
    sublo r0, r0, ip
    addlo r1, r1, ip
    mov r2, #0x80000000
    lsr r3, r0, #0x17
    orr r0, r2, r0, lsl #8
    ands ip, r3, #0xff
    cmpne ip, #0xff
    beq .L_0128
    lsr ip, r1, #0x17
    orr r1, r2, r1, lsl #8
    ands r2, ip, #0xff
    beq .L_0168
.L_0044:
    subs ip, r3, ip
    beq .L_008c
    rsb r2, ip, #0x20
    lsls r2, r1, r2
    lsr r1, r1, ip
    orrne r1, r1, #1
    subs r0, r0, r1
    bpl .L_00d0
    ands r1, r0, #0xff
    add r0, r0, r0
    lsr r0, r0, #9
    orr r0, r0, r3, lsl #23
    tst r1, #0x80
    bxeq lr
    ands r1, r1, #0x7f
    andseq r1, r0, #1
    addne r0, r0, #1
    bx lr
.L_008c:
    subs r0, r0, r1
    beq .L_0234
    lsl r2, r3, #0x17
    and r2, r2, #0x80000000
    bic r3, r3, #0x100
    clz ip, r0
    lsls r0, r0, ip
    sub r3, r3, ip
    cmp r3, #0
    bgt .L_00c0
    rsb r3, r3, #9
    orr r0, r2, r0, lsr r3
    bx lr
.L_00c0:
    add r0, r0, r0
    orr r0, r2, r0, lsr #9
    orr r0, r0, r3, lsl #23
    bx lr
.L_00d0:
    lsl r2, r3, #0x17
    and r2, r2, #0x80000000
    bic r3, r3, #0x100
    clz ip, r0
    lsls r0, r0, ip
    sub r3, r3, ip
    cmp r3, #0
    bgt .L_00fc
    rsb r3, r3, #9
    orr r0, r2, r0, lsr r3
    bx lr
.L_00fc:
    ands r1, r0, #0xff
    add r0, r0, r0
    orr r0, r2, r0, lsr #9
    orr r0, r0, r3, lsl #23
    bxeq lr
    tst r1, #0x80
    bxeq lr
    ands r1, r1, #0x7f
    andseq r1, r0, #1
    addne r0, r0, #1
    bx lr
.L_0128:
    cmp r3, #0x100
    movge r2, #0x80000000
    movlt r2, #0
    ands r3, r3, #0xff
    beq .L_0190
    lsls r0, r0, #1
    bne .L_0268
    lsr ip, r1, #0x17
    lsl r1, r1, #9
    ands ip, ip, #0xff
    beq .L_025c
    cmp ip, #0xff
    blt .L_025c
    cmp r1, #0
    beq .L_0270
    b .L_0268
.L_0168:
    cmp ip, #0x100
    movge r2, #0x80000000
    movlt r2, #0
    and r3, r3, #0xff
    ands ip, ip, #0xff
    beq .L_01f8
.L_0180:
    eor r2, r2, #0x80000000
    lsls r1, r1, #1
    bne .L_0268
    b .L_025c
.L_0190:
    lsls r0, r0, #1
    beq .L_01c8
    lsr r0, r0, #1
    mov r3, #1
    lsr ip, r1, #0x17
    lsl r1, r1, #8
    ands ip, ip, #0xff
    beq .L_01f8
    cmp ip, #0xff
    beq .L_0180
    orr r1, r1, #0x80000000
    orr r3, r3, r2, lsr #23
    orr ip, ip, r2, lsr #23
    b .L_0044
.L_01c8:
    lsr r3, r1, #0x17
    lsl r0, r1, #9
    ands r2, r3, #0xff
    beq .L_01ec
    cmp r2, #0xff
    blt .L_0214
    cmp r0, #0
    bne .L_0254
    b .L_025c
.L_01ec:
    cmp r0, #0
    beq .L_0234
    b .L_0214
.L_01f8:
    lsls r1, r1, #1
    beq .L_021c
    lsr r1, r1, #1
    mov ip, #1
    orr ip, ip, r2, lsr #23
    orr r3, r3, r2, lsr #23
    b .L_0044
.L_0214:
    mov r0, r1
    bx lr
.L_021c:
    cmp r0, #0
    subsge r3, r3, #1
    add r0, r0, r0
    orr r0, r2, r0, lsr #9
    orr r0, r0, r3, lsl #23
    bx lr
.L_0234:
    mov r0, #0
    bx lr
    cmp r0, #0
    subsge r3, r3, #1
    add r0, r0, r0
    lsr r0, r0, #9
    orr r0, r0, r3, lsl #23
    bx lr
.L_0254:
    mvn r0, #0x80000000
    bx lr
.L_025c:
    mov r0, #0xff000000
    orr r0, r2, r0, lsr #1
    bx lr
.L_0268:
    mvn r0, #0x80000000
    bx lr
.L_0270:
    mvn r0, #0x80000000
    bx lr
    .size _fsub, .-_fsub
