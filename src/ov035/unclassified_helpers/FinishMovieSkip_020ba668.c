#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x2c];
    s16 pendingSkip;
} MovieContext;

extern MovieContext *g_movieContext_020bc4e0;
extern void func_ov035_020bad08(void);
extern void func_ov001_020645e8(int messageId);

int FinishMovieSkip_020ba668(void)
{
    MovieContext *context = g_movieContext_020bc4e0;

    func_ov035_020bad08();
    if (context->pendingSkip > 0) {
        context->pendingSkip = 0;
        func_ov001_020645e8(0x3533);
    }
    g_movieContext_020bc4e0->flags |= 0x8000;
    return 6;
}