#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern u32 func_ov001_02063620(void);
extern u32 func_020365a4(void);

u32 TryEnterState1_020ba614(void)
{
    u32 result;

    result = func_ov001_02063620();
    if (result != 0) {
        return 0xffffffff;
    }
    func_020365a4();
    g_activeState_020bc800->flags = g_activeState_020bc800->flags | 0x8000;
    return 1;
}
