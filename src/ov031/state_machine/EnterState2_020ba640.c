#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x34];
    s8 mode;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern u32 func_ov001_02063404(void);
extern void ObjectManager_LoadShadowModel_0207efac(void);

u32 EnterState2_020ba640(void)
{
    if (func_ov001_02063404() == 1 && g_activeState_020bc800->mode != 3) {
        g_activeState_020bc800->mode = 0;
    }
    ObjectManager_LoadShadowModel_0207efac();
    g_activeState_020bc800->flags = g_activeState_020bc800->flags | 0x8000;
    return 2;
}
