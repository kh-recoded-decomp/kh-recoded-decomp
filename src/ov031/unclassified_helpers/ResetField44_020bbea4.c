#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x44];
    u32 unk_44;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern void func_ov031_020bbebc(void);

void ResetField44_020bbea4(void)
{
    func_ov031_020bbebc();
    g_activeState_020bc800->unk_44 = 0xffffffff;
}
