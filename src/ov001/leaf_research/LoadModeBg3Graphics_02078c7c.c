#include "nitro/types.h"

typedef struct {
    u32 fmt;
    BOOL extended;
    u32 szByte;
    void *pRawData;
} PaletteData;

typedef struct {
    u32 pixelFmt;
    u32 mapingType;
    u32 characterFmt;
    u32 unk_0C;
    u32 szByte;
    void *pRawData;
} CharacterData;

typedef struct {
    void *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

typedef struct {
    u32 active;
    u8 modeState[8];
    s32 mode;
    s32 layout;
    u8 pad_14[0xe4];
    BOOL skipLoad;
} ActiveContext;

extern ActiveContext *g_activeContext_020a04c4;

extern void *func_ov027_020ba1d8(void *resource);
extern void func_ov027_020ba1e0(void *resource, BOOL freeData);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void func_02007250(void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern void func_ov001_0207a1d0(void *modeState, s32 layout);
extern void func_ov001_0207a17c(void *modeState, s32 layout);

void LoadModeBg3Graphics_02078c7c(void *resource, u32 active)
{
    BgGraphicsData graphics;
    ActiveContext *context;

    if (g_activeContext_020a04c4->skipLoad) {
        func_ov027_020ba1e0(resource, TRUE);
        return;
    }
    g_activeContext_020a04c4->active = active;
    GetBgDataFromArchive_0202b554(&graphics, func_ov027_020ba1d8(resource), -1, 0, 0);
    func_02007250(graphics.palette->pRawData, 0, graphics.palette->szByte);
    GX_LoadBG3Char_02007b70(graphics.character->pRawData, 0, graphics.character->szByte);
    func_ov027_020ba1e0(resource, TRUE);
    context = g_activeContext_020a04c4;
    if (context->mode == 1) {
        if (context->layout == 0) {
            func_ov001_0207a1d0(context->modeState, context->layout);
        } else {
            func_ov001_0207a17c(context->modeState, context->layout);
        }
    }
}
