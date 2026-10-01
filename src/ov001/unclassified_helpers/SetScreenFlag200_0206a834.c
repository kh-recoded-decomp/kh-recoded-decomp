#include "nitro/types.h"

typedef struct ScreenState {
    u32 flags;
} ScreenState;

extern ScreenState *data_ov001_020a0480;

void SetScreenFlag200_0206a834(BOOL enable)
{
    if (enable) {
        data_ov001_020a0480->flags |= 0x200;
        return;
    }
    data_ov001_020a0480->flags &= ~0x200;
}
