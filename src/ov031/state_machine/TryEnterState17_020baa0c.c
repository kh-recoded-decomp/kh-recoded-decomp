#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern u32 func_ov001_0206a814(void);

u32 TryEnterState17_020baa0c(void)
{
    u32 result;

    result = func_ov001_0206a814();
    if (result != 0) {
        g_activeState_020bc800->flags = g_activeState_020bc800->flags | 0x8000;
        return 0x11;
    }
    return 0xffffffff;
}
