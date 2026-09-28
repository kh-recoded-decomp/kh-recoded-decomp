#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *g_activeState_020bc800;

void SetFlagBit4_020bc748(int enable)
{
    if (enable != 0) {
        g_activeState_020bc800->flags = g_activeState_020bc800->flags | 4;
        return;
    }
    g_activeState_020bc800->flags = g_activeState_020bc800->flags & 0xfffb;
}
