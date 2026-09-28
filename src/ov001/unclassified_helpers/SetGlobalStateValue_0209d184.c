#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18f40];
    u32 value;
} OverlayState;

extern OverlayState *g_ov001State_020a0508;

void SetGlobalStateValue_0209d184(u32 value)
{
    if (g_ov001State_020a0508 != 0) {
        g_ov001State_020a0508->value = value;
    }
}
