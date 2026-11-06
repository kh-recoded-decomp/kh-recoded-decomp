#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x2f0];
    s8 progress;
} PanelState;

extern PanelState *gOv013PanelGlobals;

s32 GetOv013PlayerCardIndexFromCursor(void) {
    s32 progress = gOv013PanelGlobals->progress;
    return progress - (progress + 1) / 10;
}
