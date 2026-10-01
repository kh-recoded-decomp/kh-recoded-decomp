#include "nitro/types.h"

typedef struct AreaDef {
    u8 pad_00[7];
    u8 eventCount;
    u8 pad_08[0xc];
    u16 *eventIds;
    u8 pad_18[4];
} AreaDef;

typedef struct AreaTracker {
    u8 pad_00[0x10];
    AreaDef *areas;
    u8 pad_14[0xe];
    s8 currentArea;
} AreaTracker;

typedef struct FieldState {
    u8 pad_00[0x40];
    AreaTracker tracker;
} FieldState;

extern FieldState *data_ov035_020bc4e0;
extern BOOL func_ov001_020645c8(u32 flag);
extern BOOL StageEvents_CheckEvent_02087824(u16 eventIndex);
extern void StageEvent_ReleaseHoldBit2_02087714(int eventIndex);
extern void func_ov001_02087e1c(u32 groupIndex);

void StartCurrentAreaEvents_020bc55c(void)
{
    AreaTracker *tracker;
    AreaDef *area;
    int eventIndex;

    tracker = &data_ov035_020bc4e0->tracker;
    if (func_ov001_020645c8(0x3628) != 0) {
        return;
    }
    if (tracker->currentArea < 0) {
        return;
    }
    area = &tracker->areas[tracker->currentArea];
    for (eventIndex = 0; eventIndex < area->eventCount; eventIndex++) {
        if (StageEvents_CheckEvent_02087824(area->eventIds[eventIndex]) == FALSE) {
            StageEvent_ReleaseHoldBit2_02087714(area->eventIds[eventIndex]);
            func_ov001_02087e1c(area->eventIds[eventIndex]);
        }
    }
}
