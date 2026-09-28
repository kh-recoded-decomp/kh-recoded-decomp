#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x28];
    u32 unk_28;
} OverlayState;

extern OverlayState *g_activeState_020bc800;

u32 GetField28_020bbff4(void)
{
    if (g_activeState_020bc800 != 0) {
        return g_activeState_020bc800->unk_28;
    }
    return 0;
}
