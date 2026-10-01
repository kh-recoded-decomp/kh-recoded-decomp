#include "nitro/types.h"

typedef struct ScreenData {
    u8 pad_00[0xc];
    u8 rawData[1];
} ScreenData;

typedef struct CharacterData {
    u8 pad_00[0x14];
    u8 *rawData;
} CharacterData;

typedef struct PaletteData {
    u8 pad_00[0xc];
    void *rawData;
} PaletteData;

typedef struct BgGraphicsData {
    ScreenData *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

typedef struct ItemScreen {
    s32 panelFileId;
    s32 frameFileId;
    u8 pad_00008[0x12004 - 0x8];
    u8 panelTiles[4][0x340];
    u8 cursorTiles[2][0x800];
} ItemScreen;

typedef struct GameState {
    u8 pad_0000[0x2c6a];
    u8 language;
} GameState;

extern GameState *data_0205fe0c;
extern void G2x_SetBlendAlpha_02006850(vu32 *reg, int plane1, int plane2, int ev1, int ev2);
extern void *func_0202c478(u32 fileId, int heapId);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GX_LoadBG2Char_02007a90(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Scr_02007710(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Scr_020077f0(const void *src, u32 offset, u32 size);
extern void func_02007250(const void *src, u32 offset, u32 size);
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void func_0200344c(void *start, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

static inline u32 GetLanguageNumber(void)
{
    return data_0205fe0c->language + 1;
}

static inline void SetWindowOutsidePlane(int planeMask, BOOL effect)
{
    u32 value = (*(vu16 *)0x0400004a & ~0x3f) | planeMask;
    if (effect) {
        value |= 0x20;
    }
    *(vu16 *)0x0400004a = (u16)value;
}

static inline void SetWindow1InsidePlane(int planeMask, BOOL effect)
{
    u32 value = (*(vu16 *)0x04000048 & ~0x3f00) | (planeMask << 8);
    if (effect) {
        value |= 0x2000;
    }
    *(vu16 *)0x04000048 = (u16)value;
}

void SetupItemScreenBackgrounds_020c4dd4(ItemScreen *screen)
{
    void *archive;
    void *panelArchive;
    BgGraphicsData panelBg;
    BgGraphicsData frameBg;
    BgGraphicsData backBg;

    G2x_SetBlendAlpha_02006850((vu32 *)0x04000050, 1, 0x1e, 16, 16);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1d00;
    *(vu16 *)0x04000008 = (u16)((*(vu16 *)0x04000008 & ~3) | 1);
    *(vu16 *)0x0400000a = (u16)((*(vu16 *)0x0400000a & ~3) | 0);
    *(vu16 *)0x0400000c = (u16)((*(vu16 *)0x0400000c & ~3) | 2);
    *(vu16 *)0x0400000e = (u16)((*(vu16 *)0x0400000e & ~3) | 3);
    *(vu32 *)0x04000014 = 0;
    *(vu32 *)0x04000018 = 0;
    *(vu32 *)0x0400001c = 0;
    SetWindowOutsidePlane(0x1f, TRUE);
    SetWindow1InsidePlane(0x1a, TRUE);
    *(vu16 *)0x04000042 = 0x40ff;
    *(vu16 *)0x04000046 = 0xa8c0;
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0xe000) | 0x4000;
    *(vu16 *)0x0400000a = (u16)((*(vu16 *)0x0400000a & 0x43) | 0x90);
    *(vu16 *)0x0400000c = (u16)((*(vu16 *)0x0400000c & 0x43) | 0x1a0);
    *(vu16 *)0x0400000e = (u16)((*(vu16 *)0x0400000e & 0x43) | 0x3b0);

    panelArchive = func_0202c478((((screen->panelFileId + 0x8000) & 0xfffffc) << 7) | 0x80000001, 0xf);
    GetBgDataFromArchive_0202b554(&panelBg, panelArchive, GetLanguageNumber() - 1, 0, -1);
    GX_LoadBG2Char_02007a90(panelBg.character->rawData, 0, 0x6600);
    GX_LoadBG2Scr_02007710(panelBg.screen->rawData, 0, 0x600);
    func_01ff878c(panelBg.character->rawData + 0x840, screen->panelTiles[0], 0x340);
    func_01ff878c(panelBg.character->rawData + 0xe40, screen->panelTiles[1], 0x340);
    func_01ff878c(panelBg.character->rawData + 0x3240, screen->panelTiles[2], 0x340);
    func_01ff878c(panelBg.character->rawData + 0x3840, screen->panelTiles[3], 0x340);
    func_0200344c(screen->panelTiles[0], 0x680);
    func_0200344c(screen->panelTiles[2], 0x680);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(panelArchive);

    archive = func_0202c478((((screen->frameFileId + 0x8000) & 0xfffffc) << 7) | 0x80000000, 0xf);
    GetBgDataFromArchive_0202b554(&frameBg, archive, -1, 0, -1);
    GX_LoadBG2Char_02007a90(frameBg.character->rawData, 0x6600, 0xc00);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);

    archive = func_0202c478((((screen->panelFileId + 0x8000) & 0xfffffc) << 7) | 0x80000000, 0xf);
    GetBgDataFromArchive_0202b554(&backBg, archive, 0, 0, 0);
    func_02007250(backBg.palette->rawData, 0, 0x200);
    GX_LoadBG3Char_02007b70(backBg.character->rawData, 0, 0xc000);
    GX_LoadBG3Scr_020077f0(backBg.screen->rawData, 0, 0x600);
    func_01ff878c(backBg.character->rawData + 0xb000, screen->cursorTiles[0], 0x800);
    func_01ff878c(backBg.character->rawData + 0xb800, screen->cursorTiles[1], 0x800);
    func_0200344c(screen->cursorTiles[0], 0x1000);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
}
