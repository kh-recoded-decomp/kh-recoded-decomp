#include "nitro/types.h"

typedef void (*ExceptionHandler)(void *context, void *arg);

typedef struct ExceptionStatics {
    u32 debuggerHandler;
    void *handlerArg;
    u32 reserved;
    ExceptionHandler handler;
} ExceptionStatics;

extern ExceptionStatics data_02056df0;
extern void *data_02056df4;
extern ExceptionHandler data_02056dfc;
extern u8 data_02056e20[];
extern void func_02003b50(void);
extern void func_02003b60(void);

void OSi_DisplayExContext_02003e28(void)
{
    if (data_02056df0.handler) {
        asm {
            mrs r2, CPSR
            mov r0, sp
            ldr r1, =0x9f
            msr CPSR_cxsf, r1
            mov r1, sp
            mov sp, r0
            stmfd sp!, {r1, r2}
            bl func_02003b50
            ldr r0, =data_02056e20
            ldr r1, =data_02056df4
            ldr r1, [r1]
            ldr r12, =data_02056dfc
            ldr r12, [r12]
            ldr lr, =@1
            bx r12
        @1:
            bl func_02003b60
            ldmfd sp!, {r1, r2}
            mov sp, r1
            msr CPSR_cxsf, r2
        }
    }
}
