#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern u32 func_ov001_0207b688(void);
extern void StoreToGlobalPtr4Field28_0202a778(u32 a);

u32 TryEnterState7_020ba7c4(void)
{
    u32 result;

    result = func_ov001_0207b688();
    if (result == 0) {
        return 0xffffffff;
    }
    if ((g_activeState_020bc800->flags & 1) != 0) {
        g_activeState_020bc800->flags = g_activeState_020bc800->flags & 0xfffe;
    }
    StoreToGlobalPtr4Field28_0202a778(0);
    return 7;
}
