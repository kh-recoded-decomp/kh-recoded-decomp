#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *g_ov038SoundCtx_020bd140;
extern void StoreToGlobalPtr4Field28_0202a778(s32 value);
extern void func_02036434(void);
extern void ReleaseSeqArcHeapLevel_0204e040(s32 level);
extern void ReleaseOv038Context_020bbcb8(void);

u32 DisableOv038Sound_020ba5b4(void)
{
    ReleaseOv038Context_020bbcb8();
    func_02036434();
    ReleaseSeqArcHeapLevel_0204e040(1);
    StoreToGlobalPtr4Field28_0202a778(1);
    g_ov038SoundCtx_020bd140->flags = g_ov038SoundCtx_020bd140->flags | 0x8000;
    return 5;
}
