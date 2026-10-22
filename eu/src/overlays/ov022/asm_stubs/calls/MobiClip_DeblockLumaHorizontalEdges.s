/* MobiClip deblocking, luma horizontal edges: hand-written ARM the frame filter calls per block
 * row. It reads the three pixels on each side of the edge down a 256-byte-stride column and, when
 * the alpha/beta thresholds allow it, writes back the filtered p1/p0/q0/q1. */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global MobiClip_DeblockLumaHorizontalEdges
    .type MobiClip_DeblockLumaHorizontalEdges, %function
MobiClip_DeblockLumaHorizontalEdges:
MobiClip_Code_020B73C4:
    push {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_020B73C8:
    ldr r1, [r0, #8]
MobiClip_Code_020B73CC:
    ldr r2, [r0, #0xc]
MobiClip_Code_020B73D0:
    ldr r3, [r0, #0x10]
MobiClip_Code_020B73D4:
    ldr r4, [r0, #0x14]
MobiClip_Code_020B73D8:
    ldr r0, [r0, #4]
MobiClip_Code_020B73DC:
    mov r5, r1
MobiClip_Code_020B73E0:
    add r0, r0, #0x800
MobiClip_Code_020B73E4:
    subs r2, r2, #8
MobiClip_Code_020B73E8:
    ldrb r7, [r0, #-0x100]
MobiClip_Code_020B73EC:
    ldrb r8, [r0]
MobiClip_Code_020B73F0:
    ldrb r6, [r0, #-0x200]
MobiClip_Code_020B73F4:
    ldrb sb, [r0, #0x100]
MobiClip_Code_020B73F8:
    and lr, r3, #0xff
MobiClip_Code_020b73fc:
    subs sl, r7, r8
MobiClip_Code_020b7400:
    rsblt sl, sl, #0
MobiClip_Code_020b7404:
    cmp sl, lr
MobiClip_Code_020B7408:
    bge MobiClip_Code_020b7494
MobiClip_Code_020b740c:
    subs sl, r6, r7
MobiClip_Code_020b7410:
    rsblt sl, sl, #0
MobiClip_Code_020b7414:
    cmp sl, r3, lsr #8
MobiClip_Code_020B7418:
    bge MobiClip_Code_020b7494
MobiClip_Code_020b741c:
    subs sl, r8, sb
MobiClip_Code_020b7420:
    rsblt sl, sl, #0
MobiClip_Code_020b7424:
    cmp sl, r3, lsr #8
MobiClip_Code_020B7428:
    bge MobiClip_Code_020b7494
MobiClip_Code_020b742c:
    ldrb ip, [r0, #-0x300]
MobiClip_Code_020b7430:
    ldrb lr, [r0, #0x200]
MobiClip_Code_020b7434:
    sub r6, r6, sb
MobiClip_Code_020B7438:
    add sb, r7, r8
MobiClip_Code_020b743c:
    add r6, r6, #4
MobiClip_Code_020b7440:
    add sb, sb, #1
MobiClip_Code_020b7444:
    asr sb, sb, #1
MobiClip_Code_020B7448:
    adds sl, sb, r6, asr #3
MobiClip_Code_020b744c:
    subs fp, sb, r6, asr #3
MobiClip_Code_020b7450:
    ldrb sl, [r4, sl]
MobiClip_Code_020b7454:
    ldrb fp, [r4, fp]
MobiClip_Code_020B7458:
    add sb, sb, #1
MobiClip_Code_020b745c:
    subs r7, ip, r7
MobiClip_Code_020b7460:
    rsblt r7, r7, #0
MobiClip_Code_020b7464:
    cmp r7, r3, lsr #8
MobiClip_Code_020B7468:
    addlt ip, ip, sb
MobiClip_Code_020b746c:
    asrlt ip, ip, #1
MobiClip_Code_020b7470:
    strblt ip, [r0, #-0x200]
MobiClip_Code_020b7474:
    subs r8, lr, r8
MobiClip_Code_020B7478:
    rsblt r8, r8, #0
MobiClip_Code_020b747c:
    cmp r8, r3, lsr #8
MobiClip_Code_020b7480:
    addlt lr, lr, sb
MobiClip_Code_020b7484:
    asrlt lr, lr, #1
MobiClip_Code_020B7488:
    strblt lr, [r0, #0x100]
MobiClip_Code_020b748c:
    strb sl, [r0, #-0x100]
MobiClip_Code_020b7490:
    strb fp, [r0]
MobiClip_Code_020b7494:
    add r0, r0, #1
MobiClip_Code_020B7498:
    subs r5, r5, #1
MobiClip_Code_020B749C:
    bne MobiClip_Code_020B73E8
MobiClip_Code_020B74A0:
    add r0, r0, #0x800
MobiClip_Code_020B74A4:
    sub r0, r0, r1
MobiClip_Code_020B74A8:
    mov r5, r1
MobiClip_Code_020B74AC:
    subs r2, r2, #8
MobiClip_Code_020B74B0:
    bne MobiClip_Code_020B73E8
MobiClip_Code_020B74B4:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, pc}
    .size MobiClip_DeblockLumaHorizontalEdges, . - MobiClip_DeblockLumaHorizontalEdges
