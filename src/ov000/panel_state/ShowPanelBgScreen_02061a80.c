#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct BgGraphicsData {
    NNSG2dScreenData *screen;
    NNSG2dCharacterData *character;
    NNSG2dPaletteData *palette;
} BgGraphicsData;

typedef struct BgScreenPair {
    BgGraphicsData main;
    BgGraphicsData sub;
} BgScreenPair;

typedef struct Panel {
    u8 pad_00[0x1a4];
    BgScreenPair screens[5];
} Panel;

extern void func_02007250(const void *src, u32 offset, u32 size);
extern void GX_LoadBG1Char_020079b0(const void *src, u32 offset, u32 size);
extern void GX_LoadBG1Scr_02007630(const void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt_020072b4(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG1Char_02007a20(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG1Scr_020076a0(const void *src, u32 offset, u32 size);

void ShowPanelBgScreen_02061a80(Panel *panel, int screenIndex)
{
    BgGraphicsData *main = &panel->screens[screenIndex].main;
    BgGraphicsData *sub;

    func_02007250(main->palette->pRawData, 0, main->palette->szByte);
    GX_LoadBG1Char_020079b0(main->character->pRawData, 0, main->character->szByte);
    GX_LoadBG1Scr_02007630(main->screen->rawData, 0, main->screen->szByte);

    sub = &panel->screens[screenIndex].sub;
    GXS_LoadBGPltt_020072b4(sub->palette->pRawData, 0, sub->palette->szByte);
    if (sub->character != NULL && sub->screen != NULL) {
        GXS_LoadBG1Char_02007a20(sub->character->pRawData, 0, sub->character->szByte);
        GXS_LoadBG1Scr_020076a0(sub->screen->rawData, 0, sub->screen->szByte);
    }
}
