/* MSL runtime double-precision subtract (original assembly) */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global _dsub
    .type _dsub, %function
_dsub:
    push {r4, lr}
    eors ip, r1, r3
    eormi r3, r3, #0x80000000
    bmi func_02022b14
    .global func_02022e44
    .type func_02022e44, %function
func_02022e44:
    subs ip, r0, r2
    sbcs lr, r1, r3
    bhs .L_0030
    eor lr, lr, #0x80000000
    adds r2, r2, ip
    adc r3, r3, lr
    subs r0, r0, ip
    sbc r1, r1, lr
.L_0030:
    mov lr, #0x80000000
    lsr ip, r1, #0x14
    orr r1, lr, r1, lsl #11
    orr r1, r1, r0, lsr #21
    lsl r0, r0, #0xb
    lsls r4, ip, #0x15
    cmnne r4, #0x200000
    beq .L_0234
    lsr r4, r3, #0x14
    orr r3, lr, r3, lsl #11
    orr r3, r3, r2, lsr #21
    lsl r2, r2, #0xb
    lsls lr, r4, #0x15
    beq .L_027c
.L_0068:
    subs r4, ip, r4
    beq .L_0110
    cmp r4, #0x20
    ble .L_00a4
    cmp r4, #0x38
    movge r4, #0x3f
    sub r4, r4, #0x20
    rsb lr, r4, #0x20
    orrs lr, r2, r3, lsl lr
    lsr r2, r3, r4
    orrne r2, r2, #1
    subs r0, r0, r2
    sbcs r1, r1, #0
    bmi .L_00cc
    b .L_01bc
.L_00a4:
    rsb lr, r4, #0x20
    lsls lr, r2, lr
    rsb lr, r4, #0x20
    lsr r2, r2, r4
    orr r2, r2, r3, lsl lr
    lsr r3, r3, r4
    orrne r2, r2, #1
    subs r0, r0, r2
    sbcs r1, r1, r3
    bpl .L_01bc
.L_00cc:
    lsls r2, r0, #0x15
    lsr r0, r0, #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    lsr r1, r1, #0xc
    orr r1, r1, ip, lsl #20
    tst r2, #0x80000000
    popeq {r4, lr}
    bxeq lr
    lsls r2, r2, #1
    andseq r2, r0, #1
    popeq {r4, lr}
    bxeq lr
    adds r0, r0, #1
    adc r1, r1, #0
    pop {r4, lr}
    bx lr
.L_0110:
    subs r0, r0, r2
    sbc r1, r1, r3
    orrs lr, r1, r0
    beq .L_03a0
    lsl lr, ip, #0x14
    and lr, lr, #0x80000000
    bic ip, ip, #0x800
    cmp r1, #0
    bmi .L_0198
    bne .L_0148
    sub ip, ip, #0x20
    movs r1, r0
    mov r0, #0
    bmi .L_0164
.L_0148:
    clz r4, r1
    lsls r1, r1, r4
    rsb r4, r4, #0x20
    orr r1, r1, r0, lsr r4
    rsb r4, r4, #0x20
    lsl r0, r0, r4
    sub ip, ip, r4
.L_0164:
    cmp ip, #0
    bgt .L_01a0
    rsb ip, ip, #0xc
    cmp ip, #0x20
    movge r0, r1
    movge r1, #0
    subge ip, ip, #0x20
    rsb r4, ip, #0x20
    lsr r0, r0, ip
    orr r0, r0, r1, lsl r4
    orr r1, lr, r1, lsr ip
    pop {r4, lr}
    bx lr
.L_0198:
    cmp r1, #0
    subsge ip, ip, #1
.L_01a0:
    lsr r0, r0, #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    orr r1, lr, r1, lsr #12
    orr r1, r1, ip, lsl #20
    pop {r4, lr}
    bx lr
.L_01bc:
    lsl lr, ip, #0x14
    and lr, lr, #0x80000000
    bic ip, ip, #0x800
    cmp r1, #0
    bne .L_01e0
    sub ip, ip, #0x20
    movs r1, r0
    mov r0, #0
    bmi .L_01fc
.L_01e0:
    clz r4, r1
    lsls r1, r1, r4
    rsb r4, r4, #0x20
    orr r1, r1, r0, lsr r4
    rsb r4, r4, #0x20
    lsl r0, r0, r4
    sub ip, ip, r4
.L_01fc:
    cmp ip, #0
    orrgt ip, ip, lr, lsr #20
    bgt .L_00cc
    rsb ip, ip, #0xc
    cmp ip, #0x20
    movge r0, r1
    movge r1, #0
    subge ip, ip, #0x20
    rsb r4, ip, #0x20
    lsr r0, r0, ip
    orr r0, r0, r1, lsl r4
    orr r1, lr, r1, lsr ip
    pop {r4, lr}
    bx lr
.L_0234:
    cmp ip, #0x800
    movge lr, #0x80000000
    movlt lr, #0
    bics ip, ip, #0x800
    beq .L_02a0
    orrs r4, r0, r1, lsl #1
    bne .L_037c
    lsr r4, r3, #0x14
    lsl r3, r3, #0xb
    orr r3, r3, r2, lsr #21
    lsl r2, r2, #0xb
    lsls r4, r4, #0x15
    beq .L_0368
    cmn r4, #0x200000
    bne .L_0368
    orrs r4, r2, r3, lsl #1
    beq .L_0390
    b .L_037c
.L_027c:
    cmp r4, #0x800
    movge lr, #0x80000000
    movlt lr, #0
    bic ip, ip, #0x800
    bics r4, r4, #0x800
    beq .L_0318
    orrs r4, r2, r3, lsl #1
    bne .L_037c
    b .L_0368
.L_02a0:
    orrs r4, r0, r1, lsl #1
    beq .L_02e0
    mov ip, #1
    bic r1, r1, #0x80000000
    lsr r4, r3, #0x14
    lsl r3, r3, #0xb
    orr r3, r3, r2, lsr #21
    lsl r2, r2, #0xb
    lsls r4, r4, #0x15
    cmnne r4, #0x200000
    lsr r4, r4, #0x15
    orr r4, r4, lr, lsr #20
    beq .L_027c
    orr r3, r3, #0x80000000
    orr ip, ip, lr, lsr #20
    b .L_0068
.L_02e0:
    lsr ip, r3, #0x14
    lsl r1, r3, #0xb
    orr r1, r1, r2, lsr #21
    lsl r0, r2, #0xb
    lsls r4, ip, #0x15
    beq .L_030c
    cmn r4, #0x200000
    bne .L_0334
    orrs r4, r0, r1, lsl #1
    bne .L_0380
    b .L_0368
.L_030c:
    orrs r4, r0, r1, lsl #1
    beq .L_03a0
    b .L_0334
.L_0318:
    orrs r4, r2, r3, lsl #1
    beq .L_0344
    mov r4, #1
    bic r3, r3, #0x80000000
    orr ip, ip, lr, lsr #20
    orr r4, r4, lr, lsr #20
    b .L_0068
.L_0334:
    mov r1, r3
    mov r0, r2
    pop {r4, lr}
    bx lr
.L_0344:
    cmp r1, #0
    subsge ip, ip, #1
    lsr r0, r0, #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    orr r1, lr, r1, lsr #12
    orr r1, r1, ip, lsl #20
    pop {r4, lr}
    bx lr
.L_0368:
    ldr r1, .L_pool_03b0
    orr r1, lr, r1
    mov r0, #0
    pop {r4, lr}
    bx lr
.L_037c:
    mov r1, r3
.L_0380:
    mvn r0, #0
    bic r1, r0, #0x80000000
    pop {r4, lr}
    bx lr
.L_0390:
    mvn r0, #0
    bic r1, r0, #0x80000000
    pop {r4, lr}
    bx lr
.L_03a0:
    mov r1, #0
    mov r0, #0
    pop {r4, lr}
    bx lr
.L_pool_03b0:
    .word 0x7ff00000
    .size _dsub, .-_dsub
