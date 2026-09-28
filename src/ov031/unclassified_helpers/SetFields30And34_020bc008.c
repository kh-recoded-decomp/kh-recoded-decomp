#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x30];
    u32 unk_30;
    u32 unk_34;
} OverlayState;

extern OverlayState *g_activeState_020bc800;

void SetFields30And34_020bc008(u32 a, u32 b)
{
    g_activeState_020bc800->unk_30 = a;
    g_activeState_020bc800->unk_34 = b;
}
