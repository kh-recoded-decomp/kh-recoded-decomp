#include "nitro/types.h"

typedef struct SceneWork {
    u8 pad_0000[0x8];
    s32 state;
} SceneWork;

typedef struct SceneContext {
    u32 unk_00;
    SceneWork *work;
} SceneContext;

extern SceneContext data_ov036_020c3920;
extern BOOL IsSoundStreamActive_0204ded4(int channel);
extern void OS_WaitVBlankIntr_020049d0(void);
extern void GX_BeginLoadTex_02007ff4(void);
extern void GX_LoadTex_02008050(const void *src, u32 destSlotAddr, u32 size);
extern void GX_EndLoadTex_0200819c(void);

void LoadTextureInChunks_020bc8b4(const u8 *src, u32 destSlotAddr, u32 size)
{
    int chunk = 0x8000;
    u32 i;
    u32 count;

    if (IsSoundStreamActive_0204ded4(0) || data_ov036_020c3920.work->state == 4) {
        chunk >>= 1;
        OS_WaitVBlankIntr_020049d0();
    }
    if (size <= chunk) {
        GX_BeginLoadTex_02007ff4();
        GX_LoadTex_02008050(src, destSlotAddr, size);
        GX_EndLoadTex_0200819c();
        return;
    }
    i = 0;
    count = size / chunk + 1;
    for (; i < count; i++) {
        GX_BeginLoadTex_02007ff4();
        GX_LoadTex_02008050(src + i * chunk, destSlotAddr + i * chunk, size > chunk ? chunk : size);
        size -= chunk;
        GX_EndLoadTex_0200819c();
        if (size == 0) {
            return;
        }
        OS_WaitVBlankIntr_020049d0();
    }
}
