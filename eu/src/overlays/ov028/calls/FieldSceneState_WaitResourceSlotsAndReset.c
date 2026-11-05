#include "nitro/types.h"

extern s32 StepResourceSlotLoading(void);
extern void ResetSceneSlots(s32 value);

u32 FieldSceneState_WaitResourceSlotsAndReset(void)
{
    s32 value = StepResourceSlotLoading();

    if (value != 0) {
        ResetSceneSlots(value);
        return 4;
    }
    return 0xffffffff;
}
