#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x6684];
    u32 unk_6684;
} Panel;

extern u8 SDK_OVERLAY_ov022_ID_00000002[];
extern void func_02029f78(int processor, int overlayId);

void func_ov000_02062e3c(Panel *panel)
{
    func_02029f78(0, (int)SDK_OVERLAY_ov022_ID_00000002);
    panel->unk_6684 = 0;
}
