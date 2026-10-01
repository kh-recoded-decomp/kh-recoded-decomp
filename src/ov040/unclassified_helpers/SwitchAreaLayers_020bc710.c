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
extern u32 func_ov001_0207f028(void);
extern void func_ov007_020a1b3c(u32 list, int area, BOOL enable);

void SwitchAreaLayers_020bc710(void)
{
    AreaTracker *tracker;
    u32 list;
    int previousArea;

    tracker = &data_ov035_020bc4e0->tracker;
    if (tracker->layerListId < 0) {
        return;
    }
    list = func_ov001_0207f028();
    previousArea = tracker->previousArea;
    if (tracker->currentArea == previousArea) {
        return;
    }
    if (previousArea >= 0) {
        func_ov007_020a1b3c(list, previousArea, FALSE);
    }
    if (tracker->currentArea >= 0) {
        func_ov007_020a1b3c(list, tracker->currentArea, TRUE);
    }
}
