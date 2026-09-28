#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x34];
    u8 mode;
} OverlayState;

extern OverlayState *g_activeState_020bc800;

void SetModeByte_020bb4c0(u8 mode)
{
    g_activeState_020bc800->mode = mode;
    g_activeState_020bc800->flags = g_activeState_020bc800->flags | 0x4000;
}
