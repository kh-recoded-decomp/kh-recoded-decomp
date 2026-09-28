#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18de0];
    u32 value;
} OverlayState;

extern OverlayState *g_ov001State_020a0508;

u32 GetGlobalScaleValue_0209c3cc(void)
{
    if (g_ov001State_020a0508 != 0) {
        return g_ov001State_020a0508->value;
    }
    return 0;
}
