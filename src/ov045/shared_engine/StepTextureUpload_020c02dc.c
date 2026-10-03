#include "nitro/types.h"

typedef struct {
    u8 pad00[0x10];
    u32 remaining;
    u32 vramOffset;
    const void *source;
} TextureUpload;

extern void OS_WaitVBlankIntr_020049d0(void);
extern void GX_BeginLoadTex_02007ff4(void);
extern void GX_LoadTex_02008050(const void *src, u32 destSlotAddr, u32 size);
extern void GX_EndLoadTex_0200819c(void);

BOOL StepTextureUpload_020c02dc(TextureUpload *upload)
{
    u32 size = upload->remaining;

    if (size >= 0x400) {
        size = 0x400;
    }
    OS_WaitVBlankIntr_020049d0();
    GX_BeginLoadTex_02007ff4();
    GX_LoadTex_02008050(upload->source, upload->vramOffset, size);
    GX_EndLoadTex_0200819c();
    upload->vramOffset += size;
    upload->source = (const u8 *)upload->source + size;
    upload->remaining -= size;
    if (upload->remaining == 0) {
        return TRUE;
    }
    return FALSE;
}
