#include "nitro/types.h"
#include "nitro/hw.h"

typedef u64 OSTick;
typedef int OSIntrMode;

typedef struct {
    u16 useTick;
    u16 pad;
    BOOL needResetTimer;
    volatile u64 tickCounter;
} OSiTickState;

extern OSiTickState data_02056e94;
extern OSIntrMode OS_DisableInterrupts_02004938(void);
extern OSIntrMode OS_RestoreInterrupts_0200494c(OSIntrMode state);

OSTick OS_GetTick_02003fd4(void)
{
    vu16 countL;
    vu64 countH;

    OSIntrMode prev = OS_DisableInterrupts_02004938();

    countL = *(u16 *)REG_TM0CNT_L_ADDR;
    countH = data_02056e94.tickCounter & 0xffffffffffffULL;

    if (REG_IF & 8 && !(countL & 0x8000)) {
        countH++;
    }

    (void)OS_RestoreInterrupts_0200494c(prev);

    return (countH << 16) | countL;
}
