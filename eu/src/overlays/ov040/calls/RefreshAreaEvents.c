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
extern BOOL StageEvents_CheckEvent(u16 eventIndex);
extern void StageEvent_SetHoldBit2(int eventIndex);
extern BOOL func_ov001_02087df8(u16 groupIndex);
extern void ResetStageEntries(int mode);
extern void StartCurrentAreaEvents(void);

void RefreshAreaEvents(void)
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
                if (StageEvents_CheckEvent(area->eventIds[eventIndex]) == FALSE) {
                    StageEvent_SetHoldBit2(area->eventIds[eventIndex]);
                }
            }
            ResetStageEntries(1);
        }
        StartCurrentAreaEvents();
    }
    if (tracker->currentArea >= 0) {
        area = &tracker->areas[tracker->currentArea];
        area->pendingEventCount = 0;
        for (eventIndex = 0; eventIndex < area->eventCount; eventIndex++) {
            if (StageEvents_CheckEvent(area->eventIds[eventIndex]) == FALSE
                && func_ov001_02087df8(area->eventIds[eventIndex]) == FALSE) {
                area->pendingEventCount++;
            }
        }
    }
}
