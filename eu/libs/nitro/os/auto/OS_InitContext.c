#include "nitro/types.h"

#define HW_PSR_SYS_MODE    0x1f
#define HW_PSR_THUMB_STATE 0x20
#define HW_SVC_STACK_SIZE  0x40

typedef struct OSContext {
    u32 cpsr;
    u32 r[13];
    u32 sp;
    u32 lr;
    u32 pc_plus4;
    u32 sp_svc;
} OSContext;

register u32 sValue __asm("r1");
register u32 sStack __asm("r2");

void OS_InitContext(volatile OSContext *context, u32 newpc, u32 newsp)
{
    sValue = newpc + 4;
    sStack = newsp;
    context->pc_plus4 = sValue;
    context->sp_svc = sStack;
    __atomic_signal_fence(__ATOMIC_SEQ_CST);
    sStack -= HW_SVC_STACK_SIZE;
    __atomic_signal_fence(__ATOMIC_SEQ_CST);
    if (sStack & 4) {
        sStack -= 4;
    }
    context->sp = sStack;
    __atomic_signal_fence(__ATOMIC_SEQ_CST);
    sValue &= 1;
    if (sValue) {
        __atomic_signal_fence(__ATOMIC_SEQ_CST);
        sValue = HW_PSR_SYS_MODE | HW_PSR_THUMB_STATE;
    } else {
        __atomic_signal_fence(__ATOMIC_SEQ_CST);
        sValue = HW_PSR_SYS_MODE;
    }
    context->cpsr = sValue;
    __atomic_signal_fence(__ATOMIC_SEQ_CST);
    sValue = 0;
    __atomic_signal_fence(__ATOMIC_SEQ_CST);
    context->r[0] = sValue;
    context->r[1] = sValue;
    context->r[2] = sValue;
    context->r[3] = sValue;
    context->r[4] = sValue;
    context->r[5] = sValue;
    context->r[6] = sValue;
    context->r[7] = sValue;
    context->r[8] = sValue;
    context->r[9] = sValue;
    context->r[10] = sValue;
    context->r[11] = sValue;
    context->r[12] = sValue;
    context->lr = sValue;
}
