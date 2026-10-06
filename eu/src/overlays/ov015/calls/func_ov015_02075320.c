#include "nitro/types.h"

extern u32 RunPanelIntroSequence(void);
extern void UpdatePanelBoard(void);

u32 func_ov015_02075320(void) {
    u32 result;

    result = RunPanelIntroSequence();
    UpdatePanelBoard();
    return result;
}
