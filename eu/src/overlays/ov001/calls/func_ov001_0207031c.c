#include "nitro/types.h"

extern void CloseSceneMessage(u32 context);
extern s32 DrawNextTypewriterGlyph(u32 context);

void func_ov001_0207031c(u32 context)
{
    s32 ready;

    ready = DrawNextTypewriterGlyph(context + 0x550);
    if (ready == 0) {
        CloseSceneMessage(context + 0x550);
    }
}
