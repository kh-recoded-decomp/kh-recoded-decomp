#include "nitro/types.h"

extern void func_01ff84e0(u32 src, void *dst, u32 size);

void OSi_ReloadRomData_01ff8420(u32 isFirstBoot)
{
    asm {
        mov r4, isFirstBoot
        cmp r4, #0
        movne r0, #0
        ldreq r0, =0x02fffc2c
        ldreq r0, [r0]
        stmfd sp!, {r0}
        cmp r0, #0x8000
        ldrhs r1, =0x02fffe00
        movhs r2, #0x160
        blhs func_01ff84e0
        ldr r12, =0x02fffe00
        ldr r0, [r12, #0x20]
        ldr r1, [r12, #0x28]
        ldr r2, [r12, #0x2c]
        ldr r3, [sp]
        add r0, r0, r3
        subs r3, r0, #0x8000
        movlt r0, #0x8000
        sublt r1, r1, r3
        addlt r2, r2, r3
        cmp r2, #0
        blgt func_01ff84e0
        ldr r12, =0x02fffe00
        ldr r0, [r12, #0x30]
        ldr r1, [r12, #0x38]
        ldr r2, [r12, #0x3c]
        ldr r3, [sp]
        add r0, r0, r3
        cmp r2, #0
        blgt func_01ff84e0
        ldmfd sp!, {r0}
        mov r1, #0
    @1:
        mov r0, #0
    @2:
        orr r2, r1, r0
        mcr p15, 0, r2, c7, c10, 2
        add r0, r0, #0x20
        cmp r0, #0x400
        blt @2
        adds r1, r1, #0x40000000
        bne @1
        mov r0, #0
        mcr p15, 0, r0, c7, c6, 0
        mcr p15, 0, r0, c7, c5, 0
        mcr p15, 0, r0, c7, c10, 4
    }
}
