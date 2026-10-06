#include "nitro/types.h"

extern s32 StepResourceSlotLoading(void);
extern void ResetSceneSlots(void);

u32 func_ov030_020ba614(void)
{
    s32 ready;

    ready = StepResourceSlotLoading();
    if (ready == 0) {
        return 0xffffffff;
    }
    ResetSceneSlots();
    return 4;
}
