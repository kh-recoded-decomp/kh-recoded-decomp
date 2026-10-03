#include "nitro/types.h"

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
    u8 *rawData;
} CharacterData;

typedef struct PaletteData {
    u8 pad_00[8];
    u32 size;
    void *rawData;
} PaletteData;

typedef struct BgGraphicsData {
    void *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

typedef struct MenuScreen {
    u8 pad_00[0x64e9];
    u8 drawMode;
    u8 pad_64ea[0xa];
    u8 drawState[1];
} MenuScreen;

extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void func_020033e0(void);
extern void GXS_LoadBG1Char_02007a20(const void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt_020072b4(const void *src, u32 offset, u32 size);
extern void DispatchDrawCommand_020b75b0(u32 entity, int mode);

void LoadSubBgGraphics_020b5908(MenuScreen *screen, void *archive)
{
    BgGraphicsData bg;

    GetBgDataFromArchive_0202b554(&bg, archive, -1, 0, 0);
    func_020033e0();
    GXS_LoadBG1Char_02007a20(bg.character->rawData + 0x1a0, 0x1a0, bg.character->size - 0x1a0);
    GXS_LoadBGPltt_020072b4(bg.palette->rawData, 0, bg.palette->size);
    DispatchDrawCommand_020b75b0((u32)screen->drawState, screen->drawMode);
}
