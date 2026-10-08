
/* Runtime double-precision divide helper. */
asm double _ddiv_02024e6c(double left, double right)
{
    stmfd sp!, {r4, r5, r6, lr}
    ldr lr, =0x00000ffe
    eor r4, r1, r3
    ands r12, lr, r1, lsr #19
    cmpne r12, lr
    beq @L3ac
    bic r1, r1, lr, lsl #20
    orr r1, r1, #0x100000
    add r12, r12, r4, lsr #31
@L024:
    ands r4, lr, r3, lsr #19
    cmpne r4, lr
    beq @L444
    bic r3, r3, lr, lsl #20
    orr r3, r3, #0x100000
@L038:
    sub r12, r12, r4
    cmp r1, r3
    cmpeq r0, r2
    bhs @L054
    adds r0, r0, r0
    adc r1, r1, r1
    sub r12, r12, #2
@L054:
    sub r4, pc, #0x24
    ldrb lr, [r4, r3, lsr #12]
    rsbs r2, r2, #0
    rsc r3, r3, #0
    mov r4, #0x20000000
    mla r5, lr, r3, r4
    mov r6, r3, lsl #0xa
    mov r5, r5, lsr #7
    mul lr, r5, lr
    orr r6, r6, r2, lsr #22
    mov lr, lr, lsr #0xd
    mul r5, lr, r6
    mov r6, r1, lsl #0xa
    orr r6, r6, r0, lsr #22
    mov r5, r5, lsr #0x10
    mul r5, lr, r5
    mov lr, lr, lsl #0xe
    add lr, lr, r5, lsr #16
    umull r5, r6, lr, r6
    umull r4, r5, r6, r2
    mla r5, r3, r6, r5
    mov r4, r4, lsr #0x1a
    orr r4, r4, r5, lsl #6
    add r4, r4, r0, lsl #2
    umull lr, r5, r4, lr
    mov r4, #0
    adds r5, r5, r6, lsl #24
    adc r4, r4, r6, lsr #8
    cmp r12, #0x800
    bge @L238
    add r12, r12, #0x7f0
    adds r12, r12, #0xc
    bmi @L250
    orr r1, r4, r12, lsl #31
    bic r12, r12, #1
    add r1, r1, r12, lsl #19
    tst lr, #0x80000000
    bne @L128
    rsbs r2, r2, #0
    mov r4, r4, lsl #1
    add r4, r4, r5, lsr #31
    mul lr, r2, r4
    mov r6, #0
    mov r4, r5, lsl #1
    orr r4, r4, #1
    umlal r6, lr, r4, r2
    rsc r3, r3, #0
    mla lr, r4, r3, lr
    cmp lr, r0, lsl #21
    bmi @L128
    mov r0, r5
    ldmfd sp!, {r4, r5, r6, lr}
    bx lr
@L128:
    adds r0, r5, #1
    adc r1, r1, #0
    ldmfd sp!, {r4, r5, r6, lr}
    bx lr
    dcd 0xfdfeffff
    dcd 0xf9fafbfc
    dcd 0xf5f6f7f8
    dcd 0xf1f2f3f4
    dcd 0xeeeff0f0
    dcd 0xeaebeced
    dcd 0xe7e8e9ea
    dcd 0xe4e5e6e6
    dcd 0xe1e2e2e3
    dcd 0xdedfdfe0
    dcd 0xdbdcdcdd
    dcd 0xd8d9d9da
    dcd 0xd5d6d7d7
    dcd 0xd2d3d4d4
    dcd 0xd0d0d1d2
    dcd 0xcdcececf
    dcd 0xcbcbcccc
    dcd 0xc8c9c9ca
    dcd 0xc6c6c7c8
    dcd 0xc3c4c5c5
    dcd 0xc1c2c2c3
    dcd 0xbfbfc0c0
    dcd 0xbdbdbebe
    dcd 0xbabbbcbc
    dcd 0xb8b9b9ba
    dcd 0xb6b7b7b8
    dcd 0xb4b5b5b6
    dcd 0xb2b3b3b4
    dcd 0xb0b1b1b2
    dcd 0xafafafb0
    dcd 0xadadaeae
    dcd 0xababacac
    dcd 0xa9aaaaaa
    dcd 0xa7a8a8a9
    dcd 0xa6a6a7a7
    dcd 0xa4a4a5a5
    dcd 0xa2a3a3a4
    dcd 0xa1a1a2a2
    dcd 0x9fa0a0a0
    dcd 0x9e9e9e9f
    dcd 0x9c9d9d9d
    dcd 0x9b9b9b9c
    dcd 0x999a9a9a
    dcd 0x98989999
    dcd 0x96979798
    dcd 0x95959696
    dcd 0x94949495
    dcd 0x92939393
    dcd 0x91919292
    dcd 0x90909191
    dcd 0x8f8f8f90
    dcd 0x8d8e8e8e
    dcd 0x8c8c8d8d
    dcd 0x8b8b8c8c
    dcd 0x8a8a8a8b
    dcd 0x8989898a
    dcd 0x88888888
    dcd 0x86878787
    dcd 0x85868686
    dcd 0x84858585
    dcd 0x83838484
    dcd 0x82828383
    dcd 0x81818282
    dcd 0x80808181
@L238:
    movs r1, r12, lsl #0x1f
    orr r1, r1, #0x7f000000
    orr r1, r1, #0xf00000
    mov r0, #0
    ldmfd sp!, {r4, r5, r6, lr}
    bx lr
@L250:
    mvn r6, r12, asr #1
    cmp r6, #0x34
    bgt @L39c
    beq @L378
    cmp r6, #0x14
    bge @L298
    rsb r6, r6, #0x13
    mov lr, r0, lsl r6
    rsb r6, r6, #0x14
    mov r0, r5, lsr r6
    rsb r6, r6, #0x20
    orr r0, r0, r4, lsl r6
    rsb r6, r6, #0x20
    mov r4, r4, lsr r6
    orr r1, r4, r12, lsl #31
    mov r12, lr
    mov lr, #0
    b @L2c8
@L298:
    rsb r6, r6, #0x33
    mov lr, r1, lsl r6
    mov r1, r12, lsl #0x1f
    rsb r6, r6, #0x20
    orr r12, lr, r0, lsr r6
    rsb r6, r6, #0x20
    mov lr, r0, lsl r6
    mov r5, r5, lsr #0x15
    orr r5, r5, r4, lsl #11
    rsb r6, r6, #0x1f
    mov r0, r5, lsr r6
    mov r4, #0
@L2c8:
    rsbs r2, r2, #0
    mul r4, r2, r4
    mov r5, #0
    umlal r5, r4, r2, r0
    rsc r3, r3, #0
    mla r4, r0, r3, r4
    cmp r4, r12
    cmpeq r5, lr
    ldmeqfd sp!, {r4, r5, r6, lr}
    bxeq lr
    adds r5, r5, r2
    adc r4, r4, r3
    cmp r4, r12
    bmi @L36c
    bne @L310
    cmp r5, lr
    beq @L35c
    blo @L36c
@L310:
    subs r5, r5, r2
    sbc r4, r4, r3
@L318:
    adds r5, r5, r5
    adc r4, r4, r4
    adds r5, r5, r2
    adc r4, r4, r3
    adds lr, lr, lr
    adc r12, r12, r12
    cmp r4, r12
    bmi @L35c
    ldmnefd sp!, {r4, r5, r6, lr}
    bxne lr
    cmp r5, lr
    blo @L35c
    ldmnefd sp!, {r4, r5, r6, lr}
    bxne lr
    tst r0, #1
    ldmeqfd sp!, {r4, r5, r6, lr}
    bxeq lr
@L35c:
    adds r0, r0, #1
    adc r1, r1, #0
    ldmfd sp!, {r4, r5, r6, lr}
    bx lr
@L36c:
    adds r0, r0, #1
    adc r1, r1, #0
    b @L318
@L378:
    rsbs r2, r2, #0
    rsc r3, r3, #0
    cmp r1, r3
    cmpeq r0, r2
    mov r1, r12, lsl #0x1f
    mov r0, #0
    movne r0, #1
    ldmfd sp!, {r4, r5, r6, lr}
    bx lr
@L39c:
    mov r1, r12, lsl #0x1f
    mov r0, #0
    ldmfd sp!, {r4, r5, r6, lr}
    bx lr
@L3ac:
    orrs r5, r0, r1, lsl #1
    beq @L4d0
    cmp r12, lr
    beq @L414
    movs r1, r1, lsl #0xc
    beq @L3f0
    clz r5, r1
    movs r1, r1, lsl r5
    sub r12, r12, r5
    add r5, r12, #0x1f
    mov r1, r1, lsr #0xb
    orr r1, r1, r0, lsr r5
    rsb r5, r5, #0x20
    mov r0, r0, lsl r5
    mov r12, r12, lsl #1
    orr r12, r12, r4, lsr #31
    b @L024
@L3f0:
    mvn r12, #0x13
    clz r5, r0
    movs r0, r0, lsl r5
    sub r12, r12, r5
    mov r1, r0, lsr #0xb
    mov r0, r0, lsl #0x15
    mov r12, r12, lsl #1
    orr r12, r12, r4, lsr #31
    b @L024
@L414:
    orrs r5, r0, r1, lsl #12
    bne @L4f8
    bic r5, r3, #0x80000000
    cmp r5, lr, lsl #19
    bhs @L438
    and r5, r3, #0x80000000
    eor r1, r5, r1
    ldmfd sp!, {r4, r5, r6, lr}
    bx lr
@L438:
    orrs r5, r2, r3, lsl #12
    bne @L518
    b @L530
@L444:
    orrs r5, r2, r3, lsl #1
    beq @L4bc
    cmp r4, lr
    beq @L4a4
    movs r3, r3, lsl #0xc
    beq @L484
    clz r5, r3
    movs r3, r3, lsl r5
    sub r4, r4, r5
    add r5, r4, #0x1f
    mov r3, r3, lsr #0xb
    orr r3, r3, r2, lsr r5
    rsb r5, r5, #0x20
    mov r2, r2, lsl r5
    mov r4, r4, lsl #1
    b @L038
@L484:
    mvn r4, #0x13
    clz r5, r2
    movs r2, r2, lsl r5
    sub r4, r4, r5
    mov r3, r2, lsr #0xb
    mov r2, r2, lsl #0x15
    mov r4, r4, lsl #1
    b @L038
@L4a4:
    orrs r5, r2, r3, lsl #12
    bne @L518
    mov r1, r12, lsl #0x1f
    mov r0, #0
    ldmfd sp!, {r4, r5, r6, lr}
    bx lr
@L4bc:
    mov r1, r12, lsl #0x1f
    orr r1, r1, lr, lsl #19
    mov r0, #0
    ldmfd sp!, {r4, r5, r6, lr}
    bx lr
@L4d0:
    orrs r5, r2, r3, lsl #1
    beq @L530
    bic r5, r3, #0x80000000
    cmp r5, lr, lsl #19
    cmpeq r2, #0
    bhi @L518
    eor r1, r1, r3
    and r1, r1, #0x80000000
    ldmfd sp!, {r4, r5, r6, lr}
    bx lr
@L4f8:
    tst r1, #0x80000
    beq @L530
    bic r5, r3, #0x80000000
    cmp r5, lr, lsl #19
    cmpeq r2, #0
    bhi @L518
    ldmfd sp!, {r4, r5, r6, lr}
    bx lr
@L518:
    tst r3, #0x80000
    beq @L530
    mov r1, r3
    mov r0, r2
    ldmfd sp!, {r4, r5, r6, lr}
    bx lr
@L530:
    orr r1, r1, #0x7f000000
    orr r1, r1, #0xf80000
    ldmfd sp!, {r4, r5, r6, lr}
    bx lr
}
