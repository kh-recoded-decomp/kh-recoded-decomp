#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x34];
    s8 mode;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern u32 func_ov001_0206685c(void);
extern void func_ov001_0206a7c0(int mode);
extern u32 func_ov001_0206a814(void);

u32 TryEnterState16_020ba9d0(void)
{
    OverlayState *state;
    u32 result;

    state = g_activeState_020bc800;
    if ((g_activeState_020bc800->flags & 0x10) == 0) {
        result = func_ov001_0206685c();
        if (result != 0) {
            return 0xffffffff;
        }
    }
    result = func_ov001_0206a814();
    if (result == 0) {
        return 0xffffffff;
    }
    func_ov001_0206a7c0((int)state->mode);
    return 0x10;
}
