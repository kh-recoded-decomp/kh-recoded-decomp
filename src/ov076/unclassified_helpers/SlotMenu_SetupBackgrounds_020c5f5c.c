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

typedef struct SlotMenu {
    u8 pad_00000[0x18];
    s32 archiveId;
    u8 pad_0001C[0x1c6f8 - 0x1c];
    u8 panelBackground[2][0x3c0];
    u8 widePanelBackground[2][0x3c0];
} SlotMenu;

extern void G2x_SetBlendAlpha_02006850(vu32 *reg, int plane1, int plane2, int ev1, int ev2);
extern void SlotMenu_SetBg0Priority_020c4424(SlotMenu *menu, int priority);
extern void *G2_GetBG1ScrPtr_02006e34(void);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dest, u32 size);
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

static inline void SetWindowOutsidePlane(int planeMask, BOOL effect)
{
    u32 value = (*(vu16 *)0x0400004a & ~0x3f) | planeMask;
    if (effect) {
        value |= 0x20;
    }
    *(vu16 *)0x0400004a = (u16)value;
}

static inline void SetWindow0InsidePlane(int planeMask, BOOL effect)
{
    u32 value = (*(vu16 *)0x04000048 & ~0x3f) | planeMask;
    if (effect) {
        value |= 0x20;
    }
    *(vu16 *)0x04000048 = (u16)value;
}

static inline void SetWindow1InsidePlane(int planeMask, BOOL effect)
{
    u32 value = (*(vu16 *)0x04000048 & ~0x3f00) | (planeMask << 8);
    if (effect) {
        value |= 0x2000;
    }
    *(vu16 *)0x04000048 = (u16)value;
}

void SlotMenu_SetupBackgrounds_020c5f5c(SlotMenu *menu)
{
    void *archive;
    int i;
    BgGraphicsData panelBg;
    BgGraphicsData backBg;

    G2x_SetBlendAlpha_02006850((vu32 *)0x04000050, 1, 0x1e, 16, 16);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1d00;
    SlotMenu_SetBg0Priority_020c4424(menu, 1);
    *(vu16 *)0x0400000a = (u16)((*(vu16 *)0x0400000a & ~3) | 0);
    *(vu16 *)0x0400000c = (u16)((*(vu16 *)0x0400000c & ~3) | 2);
    *(vu16 *)0x0400000e = (u16)((*(vu16 *)0x0400000e & ~3) | 3);
    *(vu32 *)0x04000014 = 0;
    *(vu32 *)0x04000018 = 0;
    *(vu32 *)0x0400001c = 0;
    SetWindowOutsidePlane(0x1b, TRUE);
    SetWindow0InsidePlane(0x1f, TRUE);
    SetWindow1InsidePlane(0x08, TRUE);
    *(vu16 *)0x04000040 = 0xe8;
    *(vu16 *)0x04000044 = 0x1898;
    *(vu16 *)0x04000042 = 0x4000;
    *(vu16 *)0x04000046 = 0xa8c0;
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0xe000) | 0x6000;
    *(vu16 *)0x0400000a = (u16)((*(vu16 *)0x0400000a & 0x43) | 0x90);
    *(vu16 *)0x0400000c = (u16)((*(vu16 *)0x0400000c & 0x43) | 0x81a0);
    *(vu16 *)0x0400000e = (u16)((*(vu16 *)0x0400000e & 0x43) | 0x3b0);
    MIi_CpuClearFast_01ff8740(0, G2_GetBG1ScrPtr_02006e34(), 0x600);

    archive = func_0202c478((((menu->archiveId + 0x8000) & 0xfffffc) << 7) | 0x80000001, 0xf);
    GetBgDataFromArchive_0202b554(&panelBg, archive, 0, 0, 0);
    GX_LoadBG2Char_02007a90(panelBg.character->rawData, 0, 0x4000);
    for (i = 0; i < 8; i++) {
        GX_LoadBG2Scr_02007710(panelBg.screen->rawData, i << 9, 0x200);
    }
    func_01ff878c(panelBg.character->rawData + 0xa00, menu->panelBackground[0], 0x3c0);
    func_01ff878c(panelBg.character->rawData + 0x1200, menu->panelBackground[1], 0x3c0);
    func_0200344c(menu->panelBackground, 0x780);
    func_01ff878c(panelBg.character->rawData + 0x2a80, menu->widePanelBackground[0], 0x3c0);
    func_01ff878c(panelBg.character->rawData + 0x3280, menu->widePanelBackground[1], 0x3c0);
    func_0200344c(menu->widePanelBackground, 0x780);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);

    archive = func_0202c478((((menu->archiveId + 0x8000) & 0xfffffc) << 7) | 0x80000000, 0xf);
    GetBgDataFromArchive_0202b554(&backBg, archive, 0, 0, 0);
    func_02007250(backBg.palette->rawData, 0, 0x200);
    GX_LoadBG3Char_02007b70(backBg.character->rawData, 0, 0xc000);
    GX_LoadBG3Scr_020077f0(backBg.screen->rawData, 0, 0x600);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
}
