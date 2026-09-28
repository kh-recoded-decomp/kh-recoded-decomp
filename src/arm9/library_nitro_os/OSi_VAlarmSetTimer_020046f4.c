#include "nitro/types.h"

typedef void (*OSVAlarmHandler)(void *arg);
typedef void (*OSIrqFunction)(void);

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

#define OS_IE_V_COUNT      (1UL << 2)
#define reg_GX_DISPSTAT    (*(vu16 *)0x04000004)

extern void OS_SetIrqFunction_02001d90(u32 intrBits, OSIrqFunction function);
extern u32 OS_EnableIrqMask_02001f5c(u32 mask);
extern void GX_SetVCountEqVal_020065d0(s32 vcount);
extern void OSi_VAlarmHandler_02004734(void);

void OSi_VAlarmSetTimer_020046f4(OSVAlarm *alarm)
{
    OS_SetIrqFunction_02001d90(OS_IE_V_COUNT, OSi_VAlarmHandler_02004734);
    GX_SetVCountEqVal_020065d0(alarm->fire);
    reg_GX_DISPSTAT |= 0x20;
    (void)OS_EnableIrqMask_02001f5c(OS_IE_V_COUNT);
}
