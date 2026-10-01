#include "nitro/types.h"

typedef struct AreaDef {
    u8 pad_00[6];
    u8 pendingEventCount;
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
    s8 previousArea;
} AreaTracker;

typedef struct FieldState {
    u8 pad_00[0x40];
    AreaTracker tracker;
} FieldState;

extern FieldState *data_ov035_020bc4e0;
extern BOOL StageEvents_CheckEvent_02087824(u16 eventIndex);
extern void StageEvent_SetHoldBit2_02087db8(int eventIndex);
extern BOOL func_ov001_02087dd0(u16 groupIndex);
extern void func_ov001_02087f00(int mode);
extern void StartCurrentAreaEvents_020bc55c(void);

void RefreshAreaEvents_020bc5b8(void)
{
    AreaTracker *tracker;
    AreaDef *area;
    int eventIndex;
    int previousArea;

    tracker = &data_ov035_020bc4e0->tracker;
    previousArea = tracker->previousArea;
    if (tracker->currentArea != previousArea) {
        if (previousArea >= 0) {
            area = &tracker->areas[previousArea];
            for (eventIndex = 0; eventIndex < area->eventCount; eventIndex++) {
                if (StageEvents_CheckEvent_02087824(area->eventIds[eventIndex]) == FALSE) {
                    StageEvent_SetHoldBit2_02087db8(area->eventIds[eventIndex]);
                }
            }
            func_ov001_02087f00(1);
        }
        StartCurrentAreaEvents_020bc55c();
    }
    if (tracker->currentArea >= 0) {
        area = &tracker->areas[tracker->currentArea];
        area->pendingEventCount = 0;
        for (eventIndex = 0; eventIndex < area->eventCount; eventIndex++) {
            if (StageEvents_CheckEvent_02087824(area->eventIds[eventIndex]) == FALSE
                && func_ov001_02087dd0(area->eventIds[eventIndex]) == FALSE) {
                area->pendingEventCount++;
            }
        }
    }
}
