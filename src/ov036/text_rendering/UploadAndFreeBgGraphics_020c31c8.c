#include "nitro/types.h"

typedef struct BgGraphics {
    u8 pad_00[0xc];
    s32 windowMask;
    void *bg2Screen;
    void *bg3Screen;
    void *charData;
    void *palette;
} BgGraphics;

#define REG_DISPCNT (*(vu32 *)0x04000000)

extern BgGraphics *data_ov036_020ca1e4;
extern void func_020033e0(void);
extern void func_ov036_020c2e84(void);
extern void GX_LoadBG2Scr_02007710(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Scr_020077f0(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Char_02007a90(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern void func_02007250(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void ApplyTextWindowBgOffsets_020c29f8(void);

void UploadAndFreeBgGraphics_020c31c8(void)
{
    BgGraphics *graphics = data_ov036_020ca1e4;

    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x300;
    func_020033e0();
    func_ov036_020c2e84();
    GX_LoadBG2Scr_02007710(graphics->bg2Screen, 0, 0x800);
    GX_LoadBG3Scr_020077f0(graphics->bg3Screen, 0, 0x800);
    GX_LoadBG2Char_02007a90(graphics->charData, 0, 0x10000);
    GX_LoadBG3Char_02007b70(graphics->charData, 0, 0x10000);
    func_02007250(graphics->palette, 0, 0x200);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(graphics->palette);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(graphics->charData);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(graphics->bg2Screen);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(graphics->bg3Screen);
    graphics->palette = NULL;
    graphics->charData = NULL;
    graphics->bg2Screen = NULL;
    graphics->bg3Screen = NULL;
    REG_DISPCNT = (REG_DISPCNT & ~0xe000) | (graphics->windowMask << 13);
    ApplyTextWindowBgOffsets_020c29f8();
}
