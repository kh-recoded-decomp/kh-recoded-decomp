/* MobiClip decoder fragment, hand-written ARM. */

asm void func_ov022_020abe24(void)
{
    cmp       r8, #0
    beq       L018
    mov       r12, r8
L00c:
    strh      r6, [r3], r10
    subs      r12, r12, #1
    bne       L00c
L018:
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    strh      r6, [r3], r10
    strh      r6, [r3], r10
    ldr       r9, [r4], #4
    ldr       r9, [r7, r9, lsl #2]
    strh      r9, [r3], r10
    rsbs      r12, r8, #3
    moveq     pc, lr
L1bc:
    strh      r6, [r3], r10
    subs      r12, r12, #1
    bne       L1bc
    mov       pc, lr
}
