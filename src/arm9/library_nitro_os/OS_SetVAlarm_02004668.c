#include "nitro/types.h"

typedef void (*OSVAlarmHandler)(void *arg);

typedef struct OSVAlarm {
    OSVAlarmHandler handler;
    void *arg;
    u32 tag;
    u32 frame;
    s16 fire;
    s16 delay;
    struct OSVAlarm *prev;
    struct OSVAlarm *next;
    BOOL period;
    s16 start;
    BOOL canceled;
} OSVAlarm;

#define reg_GX_VCOUNT (*(vu16 *)0x04000006)

extern int OS_DisableInterrupts_02004938(void);
extern int OS_RestoreInterrupts_0200494c(int state);
extern void RunResetCallbackAndIdle_02004cf0(void);
extern s32 OSi_GetVFrame_020048e8(s32 vcount);
extern void OSi_InsertVAlarm_02004568(OSVAlarm *alarm);

void OS_SetVAlarm_02004668(OSVAlarm *alarm, s16 count, s16 delay, OSVAlarmHandler handler, void *arg)
{
    int enabled = OS_DisableInterrupts_02004938();
    s32 currentVCount;
    s32 frame;

    if (!alarm || alarm->handler) {
        RunResetCallbackAndIdle_02004cf0();
    }

    currentVCount = reg_GX_VCOUNT;
    frame = OSi_GetVFrame_020048e8(currentVCount);
    alarm->period = FALSE;
    if (count <= currentVCount) {
        frame++;
    }
    alarm->frame = frame;
    alarm->fire = count;
    alarm->delay = delay;
    alarm->handler = handler;
    alarm->arg = arg;
    alarm->canceled = FALSE;

    OSi_InsertVAlarm_02004568(alarm);
    (void)OS_RestoreInterrupts_0200494c(enabled);
}
