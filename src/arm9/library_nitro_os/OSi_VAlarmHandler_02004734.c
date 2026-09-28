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

typedef struct {
    u16 useVAlarm;
    s32 previousVCount;
    s32 frame;
    OSVAlarm *head;
    OSVAlarm *tail;
} OSiVAlarmState;

#define OS_IE_V_COUNT          (1UL << 2)
#define reg_GX_DISPSTAT        (*(vu16 *)0x04000004)
#define reg_GX_VCOUNT          (*(vu16 *)0x04000006)
#define OSi_IrqCheckFlags      (*(vu32 *)((u32)data_027e0000 + 0x3ff8))

#define VALARM_FUTURE 0
#define VALARM_NOW    1
#define VALARM_PAST   2

extern OSiVAlarmState data_02056eb0;
extern u8 data_027e0000[];
extern u32 OS_DisableIrqMask_02001f8c(u32 mask);
extern u32 OS_ResetRequestIrqMask_02001fbc(u32 mask);
extern void OSi_DetachVAlarm_0200461c(OSVAlarm *alarm);
extern void OSi_InsertVAlarm_02004568(OSVAlarm *alarm);
extern void OSi_VAlarmSetTimer_020046f4(OSVAlarm *alarm);
extern s32 OSi_CompareVCount_0200489c(OSVAlarm *alarm, s32 currentFrame, s32 currentVCount);
extern s32 OSi_GetVFrame_020048e8(s32 vcount);

static inline s32 GX_GetVCountEqVal(void)
{
    u16 dispstat = reg_GX_DISPSTAT;
    return ((dispstat >> 8) & 0xff) | ((dispstat << 1) & 0x100);
}

void OSi_VAlarmHandler_02004734(void)
{
    OSVAlarm *alarm;
    s32 currentVCount;
    s32 currentFrame;
    OSVAlarmHandler handler;

    (void)OS_DisableIrqMask_02001f8c(OS_IE_V_COUNT);
    reg_GX_DISPSTAT &= ~0x20;
    OSi_IrqCheckFlags |= OS_IE_V_COUNT;

    (void)OSi_GetVFrame_020048e8(GX_GetVCountEqVal() - 1);

    while ((alarm = data_02056eb0.head) != NULL) {
        currentVCount = reg_GX_VCOUNT;
        currentFrame = OSi_GetVFrame_020048e8(currentVCount);

        switch (OSi_CompareVCount_0200489c(alarm, currentFrame, currentVCount)) {
        case VALARM_FUTURE:
            OSi_VAlarmSetTimer_020046f4(alarm);
            currentVCount = reg_GX_VCOUNT;
            if (alarm->fire != currentVCount || alarm->frame != currentFrame) {
                return;
            }
            (void)OS_DisableIrqMask_02001f8c(OS_IE_V_COUNT);
            reg_GX_DISPSTAT &= ~0x20;
            (void)OS_ResetRequestIrqMask_02001fbc(OS_IE_V_COUNT);
        case VALARM_NOW:
            handler = alarm->handler;
            OSi_DetachVAlarm_0200461c(alarm);
            alarm->handler = NULL;
            if (handler) {
                handler(alarm->arg);
            }
            if (alarm->period && !alarm->canceled) {
                alarm->handler = handler;
                alarm->frame = data_02056eb0.frame + 1;
                OSi_InsertVAlarm_02004568(alarm);
            }
            break;
        case VALARM_PAST:
            OSi_DetachVAlarm_0200461c(alarm);
            alarm->frame = data_02056eb0.frame + 1;
            OSi_InsertVAlarm_02004568(alarm);
            break;
        }
    }
}
