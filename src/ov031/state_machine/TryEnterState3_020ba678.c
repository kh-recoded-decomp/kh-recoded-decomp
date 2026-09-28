#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern u32 func_ov001_0207ed2c(void);
extern u32 func_ov001_02087178(void);

u32 TryEnterState3_020ba678(void)
{
    u32 result;

    result = func_ov001_0207ed2c();
    if (result == 0) {
        return 0xffffffff;
    }
    func_ov001_02087178();
    g_activeState_020bc800->flags = g_activeState_020bc800->flags | 0x8000;
    return 3;
}
