extern void func_02000a78(void);
extern void func_020009fc(void);
extern void func_0200093c(void);
extern void func_02000950(void);
extern void func_01ff8158(void);
extern void func_020253b0(void);
extern void func_02000b60(void);
extern void func_020253b4(void);
extern void main_02000bec(void);
extern unsigned char data_027e0000[];

/* NitroSDK crt0 _start entry point. */
asm void Entry_02000800(void)
{
    mov r12, #0x4000000
    str r12, [r12, #0x208]
@wait_vcount_0:
    ldrh r0, [r12, #6]
    cmp r0, #0
    bne @wait_vcount_0
    bl func_02000a78
    mov r0, #0x13
    msr cpsr_c, r0
    ldr r0, =data_027e0000
    add r0, r0, #0x3fc0
    mov sp, r0
    mov r0, #0x12
    msr cpsr_c, r0
    ldr r0, =data_027e0000
    add r0, r0, #0x3fc0
    sub r0, r0, #0x40
    sub sp, r0, #4
    tst sp, #4
    subeq sp, sp, #4
    ldr r1, =0x800
    sub r1, r0, r1
    mov r0, #0x1f
    msr cpsr_csfx, r0
    sub sp, r1, #4
    tst sp, #4
    subne sp, sp, #4
    mov r0, #0
    ldr r1, =data_027e0000
    mov r2, #0x4000
    bl func_0200093c
    mov r0, #0
    ldr r1, =0x5000000
    mov r2, #0x400
    bl func_0200093c
    mov r0, #0x200
    ldr r1, =0x7000000
    mov r2, #0x400
    bl func_0200093c
    ldr r1, =0x02000b88
    ldr r0, [r1, #20]
    bl func_02000950
    bl func_020009fc
    ldr r0, =0x02000b88
    ldr r1, [r0, #12]
    ldr r2, [r0, #16]
    mov r3, r1
    mov r0, #0
@clear_bss:
    cmp r1, r2
    strcc r0, [r1], #4
    bcc @clear_bss
    bic r1, r3, #0x1f
@cacheflush:
    mcr p15, 0, r0, c7, c10, 4
    mcr p15, 0, r1, c7, c5, 1
    mcr p15, 0, r1, c7, c14, 1
    add r1, r1, #0x20
    cmp r1, r2
    blt @cacheflush
    ldr r1, =0x2ffff9c
    str r0, [r1, #0]
    ldr r1, =data_027e0000
    add r1, r1, #0x3fc0
    add r1, r1, #0x3c
    ldr r0, =func_01ff8158
    str r0, [r1, #0]
    bl func_020253b0
    bl func_02000b60
    bl func_020253b4
    ldr r1, =main_02000bec
    ldr lr, =0xffff0000
    bx r1
}
