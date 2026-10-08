extern void func_02022b00(void);

/* Runtime double-precision subtract helper. */
asm double _dsub_02022e20(double left, double right)
{
    stmfd sp!, {r4, lr}
    eors r12, r1, r3
    eormi r3, r3, #0x80000000
    bmi func_02022b00
    subs r12, r0, r2
    sbcs lr, r1, r3
    bhs @L030
    eor lr, lr, #0x80000000
    adds r2, r2, r12
    adc r3, r3, lr
    subs r0, r0, r12
    sbc r1, r1, lr
@L030:
    mov lr, #0x80000000
    mov r12, r1, lsr #0x14
    orr r1, lr, r1, lsl #11
    orr r1, r1, r0, lsr #21
    mov r0, r0, lsl #0xb
    movs r4, r12, lsl #0x15
    cmnne r4, #0x200000
    beq @L234
    mov r4, r3, lsr #0x14
    orr r3, lr, r3, lsl #11
    orr r3, r3, r2, lsr #21
    mov r2, r2, lsl #0xb
    movs lr, r4, lsl #0x15
    beq @L27c
@L068:
    subs r4, r12, r4
    beq @L110
    cmp r4, #0x20
    ble @L0a4
    cmp r4, #0x38
    movge r4, #0x3f
    sub r4, r4, #0x20
    rsb lr, r4, #0x20
    orrs lr, r2, r3, lsl lr
    mov r2, r3, lsr r4
    orrne r2, r2, #1
    subs r0, r0, r2
    sbcs r1, r1, #0
    bmi @L0cc
    b @L1bc
@L0a4:
    rsb lr, r4, #0x20
    movs lr, r2, lsl lr
    rsb lr, r4, #0x20
    mov r2, r2, lsr r4
    orr r2, r2, r3, lsl lr
    mov r3, r3, lsr r4
    orrne r2, r2, #1
    subs r0, r0, r2
    sbcs r1, r1, r3
    bpl @L1bc
@L0cc:
    movs r2, r0, lsl #0x15
    mov r0, r0, lsr #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    mov r1, r1, lsr #0xc
    orr r1, r1, r12, lsl #20
    tst r2, #0x80000000
    ldmeqfd sp!, {r4, lr}
    bxeq lr
    movs r2, r2, lsl #1
    andeqs r2, r0, #1
    ldmeqfd sp!, {r4, lr}
    bxeq lr
    adds r0, r0, #1
    adc r1, r1, #0
    ldmfd sp!, {r4, lr}
    bx lr
@L110:
    subs r0, r0, r2
    sbc r1, r1, r3
    orrs lr, r1, r0
    beq @L3a0
    mov lr, r12, lsl #0x14
    and lr, lr, #0x80000000
    bic r12, r12, #0x800
    cmp r1, #0
    bmi @L198
    bne @L148
    sub r12, r12, #0x20
    movs r1, r0
    mov r0, #0
    bmi @L164
@L148:
    clz r4, r1
    movs r1, r1, lsl r4
    rsb r4, r4, #0x20
    orr r1, r1, r0, lsr r4
    rsb r4, r4, #0x20
    mov r0, r0, lsl r4
    sub r12, r12, r4
@L164:
    cmp r12, #0
    bgt @L1a0
    rsb r12, r12, #0xc
    cmp r12, #0x20
    movge r0, r1
    movge r1, #0
    subge r12, r12, #0x20
    rsb r4, r12, #0x20
    mov r0, r0, lsr r12
    orr r0, r0, r1, lsl r4
    orr r1, lr, r1, lsr r12
    ldmfd sp!, {r4, lr}
    bx lr
@L198:
    cmp r1, #0
    subges r12, r12, #1
@L1a0:
    mov r0, r0, lsr #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    orr r1, lr, r1, lsr #12
    orr r1, r1, r12, lsl #20
    ldmfd sp!, {r4, lr}
    bx lr
@L1bc:
    mov lr, r12, lsl #0x14
    and lr, lr, #0x80000000
    bic r12, r12, #0x800
    cmp r1, #0
    bne @L1e0
    sub r12, r12, #0x20
    movs r1, r0
    mov r0, #0
    bmi @L1fc
@L1e0:
    clz r4, r1
    movs r1, r1, lsl r4
    rsb r4, r4, #0x20
    orr r1, r1, r0, lsr r4
    rsb r4, r4, #0x20
    mov r0, r0, lsl r4
    sub r12, r12, r4
@L1fc:
    cmp r12, #0
    orrgt r12, r12, lr, lsr #20
    bgt @L0cc
    rsb r12, r12, #0xc
    cmp r12, #0x20
    movge r0, r1
    movge r1, #0
    subge r12, r12, #0x20
    rsb r4, r12, #0x20
    mov r0, r0, lsr r12
    orr r0, r0, r1, lsl r4
    orr r1, lr, r1, lsr r12
    ldmfd sp!, {r4, lr}
    bx lr
@L234:
    cmp r12, #0x800
    movge lr, #0x80000000
    movlt lr, #0
    bics r12, r12, #0x800
    beq @L2a0
    orrs r4, r0, r1, lsl #1
    bne @L37c
    mov r4, r3, lsr #0x14
    mov r3, r3, lsl #0xb
    orr r3, r3, r2, lsr #21
    mov r2, r2, lsl #0xb
    movs r4, r4, lsl #0x15
    beq @L368
    cmn r4, #0x200000
    bne @L368
    orrs r4, r2, r3, lsl #1
    beq @L390
    b @L37c
@L27c:
    cmp r4, #0x800
    movge lr, #0x80000000
    movlt lr, #0
    bic r12, r12, #0x800
    bics r4, r4, #0x800
    beq @L318
    orrs r4, r2, r3, lsl #1
    bne @L37c
    b @L368
@L2a0:
    orrs r4, r0, r1, lsl #1
    beq @L2e0
    mov r12, #1
    bic r1, r1, #0x80000000
    mov r4, r3, lsr #0x14
    mov r3, r3, lsl #0xb
    orr r3, r3, r2, lsr #21
    mov r2, r2, lsl #0xb
    movs r4, r4, lsl #0x15
    cmnne r4, #0x200000
    mov r4, r4, lsr #0x15
    orr r4, r4, lr, lsr #20
    beq @L27c
    orr r3, r3, #0x80000000
    orr r12, r12, lr, lsr #20
    b @L068
@L2e0:
    mov r12, r3, lsr #0x14
    mov r1, r3, lsl #0xb
    orr r1, r1, r2, lsr #21
    mov r0, r2, lsl #0xb
    movs r4, r12, lsl #0x15
    beq @L30c
    cmn r4, #0x200000
    bne @L334
    orrs r4, r0, r1, lsl #1
    bne @L380
    b @L368
@L30c:
    orrs r4, r0, r1, lsl #1
    beq @L3a0
    b @L334
@L318:
    orrs r4, r2, r3, lsl #1
    beq @L344
    mov r4, #1
    bic r3, r3, #0x80000000
    orr r12, r12, lr, lsr #20
    orr r4, r4, lr, lsr #20
    b @L068
@L334:
    mov r1, r3
    mov r0, r2
    ldmfd sp!, {r4, lr}
    bx lr
@L344:
    cmp r1, #0
    subges r12, r12, #1
    mov r0, r0, lsr #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    orr r1, lr, r1, lsr #12
    orr r1, r1, r12, lsl #20
    ldmfd sp!, {r4, lr}
    bx lr
@L368:
    ldr r1, =0x7ff00000
    orr r1, lr, r1
    mov r0, #0
    ldmfd sp!, {r4, lr}
    bx lr
@L37c:
    mov r1, r3
@L380:
    mvn r0, #0
    bic r1, r0, #0x80000000
    ldmfd sp!, {r4, lr}
    bx lr
@L390:
    mvn r0, #0
    bic r1, r0, #0x80000000
    ldmfd sp!, {r4, lr}
    bx lr
@L3a0:
    mov r1, #0
    mov r0, #0
    ldmfd sp!, {r4, lr}
    bx lr
}
