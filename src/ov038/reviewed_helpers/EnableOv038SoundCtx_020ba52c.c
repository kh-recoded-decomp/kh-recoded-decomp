#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *g_ov038SoundCtx_020bd140;
extern void StoreToGlobalPtr4Field28_0202a778(s32 value);
extern void func_ov038_020bbc9c(void);

u32 EnableOv038SoundCtx_020ba52c(void)
{
    func_ov038_020bbc9c();
    if ((g_ov038SoundCtx_020bd140->flags & 1) != 0) {
        g_ov038SoundCtx_020bd140->flags = g_ov038SoundCtx_020bd140->flags & 0xfffe;
    }
    StoreToGlobalPtr4Field28_0202a778(0);
    return 2;
}
