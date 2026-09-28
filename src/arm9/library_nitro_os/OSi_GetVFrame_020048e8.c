#include "nitro/types.h"

typedef struct OSVAlarm OSVAlarm;

typedef struct {
    u16 useVAlarm;
    s32 previousVCount;
    s32 frame;
    OSVAlarm *head;
    OSVAlarm *tail;
} OSiVAlarmState;

extern OSiVAlarmState data_02056eb0;
extern int OS_DisableInterrupts_02004938(void);
extern int OS_RestoreInterrupts_0200494c(int state);

s32 OSi_GetVFrame_020048e8(s32 vcount)
{
    int enabled = OS_DisableInterrupts_02004938();

    if (vcount < data_02056eb0.previousVCount) {
        data_02056eb0.frame++;
    }
    data_02056eb0.previousVCount = vcount;

    (void)OS_RestoreInterrupts_0200494c(enabled);
    return data_02056eb0.frame;
}
