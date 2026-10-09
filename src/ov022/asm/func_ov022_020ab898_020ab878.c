/* MobiClip header unpack: hand-written ARM, no prologue. */

asm void func_ov022_020ab898_020ab878(void)
{
    ldrh      r3, [r0], #2
    ldrh      r4, [r0], #2
    orr       r3, r3, r4, lsl #16
    sub       r12, pc, #0x294
    mov       r4, r3, lsr #0x1a
    ldr       r5, [r12, r4, lsl #2]
    str       r5, [r2]
    mov       r4, r3, lsr #0x14
    and       r4, r4, #0x3f
    ldr       r5, [r12, r4, lsl #2]
    str       r5, [r2, #4]
    sub       r12, pc, #0x1b4
    mov       r4, r3, lsr #0xf
    and       r4, r4, #0x1f
    ldr       r5, [r12, r4, lsl #2]
    str       r5, [r2, #8]
    sub       r12, pc, #0x148
    mov       r4, r3, lsr #0xa
    and       r4, r4, #0x1f
    ldr       r5, [r12, r4, lsl #2]
    str       r5, [r2, #0xc]
    sub       r12, pc, #0xdc
    mov       r4, r3, lsr #6
    and       r4, r4, #0xf
    ldr       r5, [r12, r4, lsl #2]
    str       r5, [r2, #0x10]
    sub       r12, pc, #0xb0
    mov       r4, r3, lsr #3
    and       r4, r4, #7
    ldr       r5, [r12, r4, lsl #2]
    str       r5, [r2, #0x18]
    sub       r12, pc, #0xa4
    and       r3, r3, #7
    ldr       r5, [r12, r3, lsl #2]
    str       r5, [r2, #0x1c]
    ldrh      r3, [r0], #2
    ldrh      r4, [r0], #2
    orr       r3, r3, r4, lsl #16
    mov       r4, r3, lsr #0x1a
    str       r4, [r2, #0x3c]
    mov       r4, r3, lsr #0x14
    and       r4, r4, #0x3f
    str       r4, [r2, #0x38]
    mov       r4, r3, lsr #0xe
    and       r4, r4, #0x3f
    str       r4, [r2, #0x34]
    mov       r4, r3, lsr #8
    and       r4, r4, #0x3f
    str       r4, [r2, #0x30]
    mov       r4, r3, lsr #6
    and       r4, r4, #3
    str       r4, [r2, #0x2c]
    mov       r4, r3, lsr #4
    and       r4, r4, #3
    str       r4, [r2, #0x28]
    mov       r4, r3, lsr #2
    and       r4, r4, #3
    str       r4, [r2, #0x24]
    and       r3, r3, #3
    str       r3, [r2, #0x20]
    ldrh      r3, [r0], #2
    ldrh      r4, [r0], #2
    orr       r3, r3, r4, lsl #16
    mov       r4, r3, lsr #0x1d
    str       r4, [r2, #0x40]
    mov       r4, r3, lsr #0x1a
    and       r4, r4, #7
    str       r4, [r2, #0x44]
    mov       r4, r3, lsr #0x17
    and       r4, r4, #7
    str       r4, [r2, #0x48]
    mov       r4, r3, lsr #0x14
    and       r4, r4, #7
    str       r4, [r2, #0x4c]
    mov       r4, r3, lsr #0x11
    and       r4, r4, #7
    str       r4, [r2, #0x50]
    mov       r4, r3, lsr #0xe
    and       r4, r4, #7
    str       r4, [r2, #0x54]
    mov       r4, r3, lsr #0xb
    and       r4, r4, #7
    str       r4, [r2, #0x58]
    mov       r4, r3, lsr #8
    and       r4, r4, #7
    str       r4, [r2, #0x5c]
    mov       r4, r3, lsr #5
    and       r4, r4, #7
    str       r4, [r2, #0x60]
    mov       r4, r3, lsr #2
    and       r4, r4, #7
    str       r4, [r2, #0x64]
    ldrh      r5, [r0], #2
    ldrh      r4, [r0], #2
    orr       r5, r5, r4, lsl #16
    mov       r4, r5, lsr #0x1d
    str       r4, [r2, #0x68]
    mov       r4, r5, lsr #0x1a
    and       r4, r4, #7
    str       r4, [r2, #0x6c]
    mov       r4, r5, lsr #0x17
    and       r4, r4, #7
    str       r4, [r2, #0x70]
    mov       r4, r5, lsr #0x14
    and       r4, r4, #7
    str       r4, [r2, #0x74]
    mov       r4, r5, lsr #0x11
    and       r4, r4, #7
    str       r4, [r2, #0x78]
    mov       r4, r5, lsr #0xe
    and       r4, r4, #7
    str       r4, [r2, #0x7c]
    mov       r4, r5, lsr #0xb
    and       r4, r4, #7
    str       r4, [r2, #0x80]
    mov       r4, r5, lsr #8
    and       r4, r4, #7
    str       r4, [r2, #0x84]
    mov       r4, r5, lsr #5
    and       r4, r4, #7
    str       r4, [r2, #0x88]
    mov       r4, r5, lsr #2
    and       r4, r4, #7
    str       r4, [r2, #0x8c]
    and       r3, r3, #3
    mov       r4, r5, lsr #1
    and       r4, r4, #1
    orr       r4, r4, r3, lsl #1
    str       r4, [r2, #0x90]
    ldrh      r3, [r0], #2
    ldrh      r4, [r0], #2
    orr       r3, r3, r4, lsl #16
    mov       r4, r3, lsr #0x1d
    str       r4, [r2, #0x94]
    mov       r4, r3, lsr #0x1a
    and       r4, r4, #7
    str       r4, [r2, #0x98]
    mov       r4, r3, lsr #0x17
    and       r4, r4, #7
    str       r4, [r2, #0x9c]
    mov       r4, r3, lsr #0x14
    and       r4, r4, #7
    str       r4, [r2, #0xa0]
    mov       r4, r3, lsr #0x11
    and       r4, r4, #7
    str       r4, [r2, #0xa4]
    mov       r4, r3, lsr #0xe
    and       r4, r4, #7
    str       r4, [r2, #0xa8]
    mov       r4, r3, lsr #0xb
    and       r4, r4, #7
    str       r4, [r2, #0xac]
    mov       r4, r3, lsr #8
    and       r4, r4, #7
    str       r4, [r2, #0xb0]
    mov       r4, r3, lsr #5
    and       r4, r4, #7
    str       r4, [r2, #0xb4]
    mov       r4, r3, lsr #2
    and       r4, r4, #7
    str       r4, [r2, #0xb8]
    ldrh      r6, [r0], #2
    ldrh      r4, [r0], #2
    orr       r6, r6, r4, lsl #16
    mov       r4, r6, lsr #0x1d
    str       r4, [r2, #0xbc]
    mov       r4, r6, lsr #0x1a
    and       r4, r4, #7
    str       r4, [r2, #0xc0]
    mov       r4, r6, lsr #0x17
    and       r4, r4, #7
    str       r4, [r2, #0xc4]
    mov       r4, r6, lsr #0x14
    and       r4, r4, #7
    str       r4, [r2, #0xc8]
    mov       r4, r6, lsr #0x11
    and       r4, r4, #7
    str       r4, [r2, #0xcc]
    mov       r4, r6, lsr #0xe
    and       r4, r4, #7
    str       r4, [r2, #0xd0]
    mov       r4, r6, lsr #0xb
    and       r4, r4, #7
    str       r4, [r2, #0xd4]
    mov       r4, r6, lsr #8
    and       r4, r4, #7
    str       r4, [r2, #0xd8]
    mov       r4, r6, lsr #5
    and       r4, r4, #7
    str       r4, [r2, #0xdc]
    mov       r4, r6, lsr #2
    and       r4, r4, #7
    str       r4, [r2, #0xe0]
    and       r3, r3, #3
    mov       r4, r6, lsr #1
    and       r4, r4, #1
    orr       r4, r4, r3, lsl #1
    str       r4, [r2, #0xe4]
    ldrh      r3, [r0], #2
    ldrh      r4, [r0], #2
    orr       r3, r3, r4, lsl #16
    mov       r4, r3, lsr #0x1d
    str       r4, [r2, #0xe8]
    mov       r4, r3, lsr #0x1a
    and       r4, r4, #7
    str       r4, [r2, #0xec]
    mov       r4, r3, lsr #0x17
    and       r4, r4, #7
    str       r4, [r2, #0xf0]
    mov       r4, r3, lsr #0x14
    and       r4, r4, #7
    str       r4, [r2, #0xf4]
    mov       r4, r3, lsr #0x11
    and       r4, r4, #7
    str       r4, [r2, #0xf8]
    mov       r4, r3, lsr #0xe
    and       r4, r4, #7
    str       r4, [r2, #0xfc]
    mov       r4, r3, lsr #0xb
    and       r4, r4, #7
    str       r4, [r2, #0x100]
    mov       r4, r3, lsr #8
    and       r4, r4, #7
    str       r4, [r2, #0x104]
    mov       r4, r3, lsr #5
    and       r4, r4, #7
    str       r4, [r2, #0x108]
    mov       r4, r3, lsr #2
    and       r4, r4, #7
    str       r4, [r2, #0x10c]
    ldrh      r7, [r0], #2
    ldrh      r4, [r0], #2
    orr       r7, r7, r4, lsl #16
    mov       r4, r7, lsr #0x1d
    str       r4, [r2, #0x110]
    mov       r4, r7, lsr #0x1a
    and       r4, r4, #7
    str       r4, [r2, #0x114]
    mov       r4, r7, lsr #0x17
    and       r4, r4, #7
    str       r4, [r2, #0x118]
    mov       r4, r7, lsr #0x14
    and       r4, r4, #7
    str       r4, [r2, #0x11c]
    mov       r4, r7, lsr #0x11
    and       r4, r4, #7
    str       r4, [r2, #0x120]
    mov       r4, r7, lsr #0xe
    and       r4, r4, #7
    str       r4, [r2, #0x124]
    mov       r4, r7, lsr #0xb
    and       r4, r4, #7
    str       r4, [r2, #0x128]
    mov       r4, r7, lsr #8
    and       r4, r4, #7
    str       r4, [r2, #0x12c]
    mov       r4, r7, lsr #5
    and       r4, r4, #7
    str       r4, [r2, #0x130]
    mov       r4, r7, lsr #2
    and       r4, r4, #7
    str       r4, [r2, #0x134]
    and       r3, r3, #3
    mov       r4, r7, lsr #1
    and       r4, r4, #1
    orr       r4, r4, r3, lsl #1
    str       r4, [r2, #0x138]
    ldrh      r3, [r0], #2
    ldrh      r4, [r0], #2
    orr       r3, r3, r4, lsl #16
    mov       r4, r3, lsr #0x1d
    str       r4, [r2, #0x13c]
    mov       r4, r3, lsr #0x1a
    and       r4, r4, #7
    str       r4, [r2, #0x140]
    mov       r4, r3, lsr #0x17
    and       r4, r4, #7
    str       r4, [r2, #0x144]
    mov       r4, r3, lsr #0x14
    and       r4, r4, #7
    str       r4, [r2, #0x148]
    mov       r4, r3, lsr #0x11
    and       r4, r4, #7
    str       r4, [r2, #0x14c]
    mov       r4, r3, lsr #0xe
    and       r4, r4, #7
    str       r4, [r2, #0x150]
    mov       r4, r3, lsr #0xb
    and       r4, r4, #7
    str       r4, [r2, #0x154]
    mov       r4, r3, lsr #8
    and       r4, r4, #7
    str       r4, [r2, #0x158]
    mov       r4, r3, lsr #5
    and       r4, r4, #7
    str       r4, [r2, #0x15c]
    mov       r4, r3, lsr #2
    and       r4, r4, #7
    str       r4, [r2, #0x160]
    ldrh      r8, [r0], #2
    ldrh      r4, [r0], #2
    orr       r8, r8, r4, lsl #16
    mov       r4, r8, lsr #0x1d
    str       r4, [r2, #0x164]
    mov       r4, r8, lsr #0x1a
    and       r4, r4, #7
    str       r4, [r2, #0x168]
    mov       r4, r8, lsr #0x17
    and       r4, r4, #7
    str       r4, [r2, #0x16c]
    mov       r4, r8, lsr #0x14
    and       r4, r4, #7
    str       r4, [r2, #0x170]
    mov       r4, r8, lsr #0x11
    and       r4, r4, #7
    str       r4, [r2, #0x174]
    mov       r4, r8, lsr #0xe
    and       r4, r4, #7
    str       r4, [r2, #0x178]
    mov       r4, r8, lsr #0xb
    and       r4, r4, #7
    str       r4, [r2, #0x17c]
    mov       r4, r8, lsr #8
    and       r4, r4, #7
    str       r4, [r2, #0x180]
    mov       r4, r8, lsr #5
    and       r4, r4, #7
    str       r4, [r2, #0x184]
    mov       r4, r8, lsr #2
    and       r4, r4, #7
    str       r4, [r2, #0x188]
    and       r3, r3, #3
    mov       r4, r8, lsr #1
    and       r4, r4, #1
    orr       r4, r4, r3, lsl #1
    str       r4, [r2, #0x18c]
    add       r12, pc, #0x24
    and       r5, r5, #1
    and       r6, r6, #1
    and       r7, r7, #1
    and       r8, r8, #1
    orr       r8, r8, r7, lsl #1
    orr       r8, r8, r6, lsl #2
    orr       r8, r8, r5, lsl #3
    ldr       r4, [r12, r8, lsl #2]
    str       r4, [r2, #0x14]
    mov       pc, lr
}
