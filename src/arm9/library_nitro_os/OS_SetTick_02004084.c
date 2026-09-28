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

void OS_SetTick_02004084(OSTick count)
{
    OSIntrMode prev = OS_DisableInterrupts_02004938();

    REG_IF = 8;
    data_02056e94.needResetTimer = TRUE;
    data_02056e94.tickCounter = count >> 16;

    REG_TM0CNT_H = 0;
    REG_TM0CNT_L = (u16)(count & 0xffff);
    REG_TM0CNT_H = 0xc1;

    (void)OS_RestoreInterrupts_0200494c(prev);
}
