#include "nitro/types.h"

extern s32 StepResourceSlotLoading(void);
extern void ResetSceneSlots(void);

s32 func_ov032_020ba98c(void) {
    s32 ready = StepResourceSlotLoading();
    if (ready == 0) {
        return -1;
    }
    ResetSceneSlots();
    return 4;
}
