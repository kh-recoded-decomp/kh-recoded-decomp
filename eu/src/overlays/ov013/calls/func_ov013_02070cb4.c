#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x2f0];
    s8 progress;
} PanelState;

extern PanelState *data_ov013_02074ce0;

s32 func_ov013_02070cb4(void) {
    s32 progress = data_ov013_02074ce0->progress;
    return progress - (progress + 1) / 10;
}
