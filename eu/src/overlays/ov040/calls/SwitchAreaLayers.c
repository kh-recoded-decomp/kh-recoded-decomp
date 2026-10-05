#include "nitro/types.h"

typedef struct AreaTracker {
    u8 pad_00[4];
    s8 layerListId;
    u8 pad_05[0x1d];
    s8 currentArea;
    s8 previousArea;
} AreaTracker;

typedef struct FieldState {
    u8 pad_00[0x40];
    AreaTracker tracker;
} FieldState;

extern FieldState *data_ov035_020bc4e0;
extern u32 func_ov001_0207f050(void);
extern void SetSlotSide(u32 list, int area, BOOL enable);

void SwitchAreaLayers(void)
{
    AreaTracker *tracker;
    u32 list;
    int previousArea;

    tracker = &data_ov035_020bc4e0->tracker;
    if (tracker->layerListId < 0) {
        return;
    }
    list = func_ov001_0207f050();
    previousArea = tracker->previousArea;
    if (tracker->currentArea == previousArea) {
        return;
    }
    if (previousArea >= 0) {
        SetSlotSide(list, previousArea, FALSE);
    }
    if (tracker->currentArea >= 0) {
        SetSlotSide(list, tracker->currentArea, TRUE);
    }
}
