#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct BgGraphicsData {
    NNSG2dScreenData *screen;
    NNSG2dCharacterData *character;
    NNSG2dPaletteData *palette;
} BgGraphicsData;

typedef struct PanelSlotSrc {
    s32 srcY;
    s32 pad;
} PanelSlotSrc;

typedef struct PanelState {
    u8 pad_00[0xc];
    u8 pages[0x5c];
    BgGraphicsData graphics;
    u8 pad_74[0x4];
    PanelSlotSrc slots[2];
    u8 pad_88[0x10];
    s32 step;
    u8 pad_9c[0x4];
    s32 subBrightness;
    u8 pad_a4[0x8];
    u32 savedBg3Priority;
    u32 visible;
    u8 pad_b4[0x10];
    u32 active;
} PanelState;

extern PanelState *data_0205fe24;
extern u32 data_0205fde4;
extern u8 data_0205fdc4;
extern char data_02055f44[];

extern void NotifyBothOrOne_02001154(u32 mask, const char *name, int index);
extern int func_ov001_02063a38(void);
extern void *G2_GetBG1ScrPtr_02006e34(void);
extern void *G2_GetBG2ScrPtr_02006e88(void);
extern void *G2_GetBG3ScrPtr_02006f80(void);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dst, u32 size);
extern void ResetPanelPageLayout_02028310(void);
extern void func_0202849c(void *pages, int index, s32 srcY);
extern void func_02007250(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char_02007b70(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Scr_020077f0(const void *src, u32 offset, u32 size);
extern void SetupBackgroundFromResources_02016754(int bg, NNSG2dScreenData *screen, NNSG2dCharacterData *character, NNSG2dPaletteData *palette, int a, int b, int c, int d);
extern void ToggleSceneBlendAndClearColor_020bd8c8(void);
extern void G2x_SetBlendBrightness_0200686c(u32 regAddr, int plane, int brightness);
extern void func_02006748(u32 reg, int value);
extern u32 func_02027edc(void);

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_DISPCNT_SUB (*(vu32 *)0x04001000)
#define REG_BG3CNT (*(vu16 *)0x0400000e)
#define REG_BG3OFS (*(vu32 *)0x0400001c)

static inline void SetVisiblePlane(u32 plane)
{
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (plane << 8);
}

static inline u32 GetVisiblePlane(void)
{
    return (REG_DISPCNT & 0x1f00) >> 8;
}

static inline u32 GetSubVisiblePlane(void)
{
    return (REG_DISPCNT_SUB & 0x1f00) >> 8;
}

static inline void SetBG3ControlText(int screenSize, int colorMode, int screenBase, int charBase)
{
    REG_BG3CNT = (u16)((REG_BG3CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2));
}

static inline void SetBG3Priority(int priority)
{
    REG_BG3CNT = (u16)((REG_BG3CNT & ~3) | priority);
}

static inline void SetBlendBrightness(int plane, int brightness)
{
    G2x_SetBlendBrightness_0200686c(0x04000050, plane, brightness);
}

static inline void SetSubBlendBrightness(int plane, int brightness)
{
    G2x_SetBlendBrightness_0200686c(0x04001050, plane, brightness);
}
void UpdatePanelScreenSetup_02027eec(void)
{
    PanelState *panel = data_0205fe24;
    BgGraphicsData *graphics = &panel->graphics;
    int i;

    if (data_0205fde4 == 0) {
        NotifyBothOrOne_02001154(1, data_02055f44, -1);
        panel->active = 0;
        return;
    }
    switch (panel->step) {
    case 0:
        if (data_0205fdc4 == 0) {
            return;
        }
        if (func_ov001_02063a38() != 8) {
            REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x100;
        } else {
            REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x300;
            REG_BG3OFS = 0;
        }
        REG_DISPCNT &= ~0xe000;
        SetBG3ControlText(0, 0, func_ov001_02063a38() == 8 ? 0x16 : 0x1f, 0);
        if (func_ov001_02063a38() != 8) {
            MIi_CpuClearFast_01ff8740(0, G2_GetBG1ScrPtr_02006e34(), 0x800);
        }
        MIi_CpuClearFast_01ff8740(0, G2_GetBG2ScrPtr_02006e88(), 0x800);
        MIi_CpuClearFast_01ff8740(0, G2_GetBG3ScrPtr_02006f80(), 0x800);
        ResetPanelPageLayout_02028310();
        for (i = 0; i < 2; i++) {
            func_0202849c(panel->pages, i, panel->slots[i].srcY);
        }
        if (func_ov001_02063a38() == 8) {
            u32 size = graphics->palette->szByte;
            func_02007250((u8 *)graphics->palette->pRawData + 0x1c0, size - (size >> 3), size >> 3);
            GX_LoadBG3Char_02007b70(graphics->character->pRawData, 0, graphics->character->szByte);
            GX_LoadBG3Scr_020077f0(graphics->screen->rawData, 0, graphics->screen->szByte);
        } else {
            SetupBackgroundFromResources_02016754(3, panel->graphics.screen, panel->graphics.character, panel->graphics.palette, 0, 0, 0x1f, 0);
        }
        if (func_ov001_02063a38() == 8) {
            ToggleSceneBlendAndClearColor_020bd8c8();
        } else {
            SetBlendBrightness(GetVisiblePlane(), -8);
        }
        func_02006748(0x0400006c, 0);
        SetSubBlendBrightness(GetSubVisiblePlane(), panel->subBrightness);
        panel->subBrightness = -8;
        panel->visible = 1;
        break;
    case 2:
        if (func_ov001_02063a38() == 8) {
            panel->savedBg3Priority = func_02027edc();
            SetBG3Priority(0);
        }
        SetVisiblePlane(GetVisiblePlane() | 8);
        NotifyBothOrOne_02001154(1, data_02055f44, -1);
        panel->active = 0;
        break;
    }
    panel->step++;
}






