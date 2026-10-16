#include "nitro/types.h"

typedef struct PanelDisplayState {
    u8 unknown00[0x9c];
    s32 savedMainBrightness;
    s32 savedSubBrightness;
    u32 savedVisiblePlanes;
    u32 savedVisibleWindows;
    u32 savedBg3Priority;
    u8 unknownb0[0xc0 - 0xb0];
    s32 fadeEngine;
    s32 fadePending;
} PanelDisplayState;

typedef char MainBrightnessOffset[(u32)&((PanelDisplayState *)0)->savedMainBrightness == 0x9c ? 1 : -1];
typedef char VisiblePlanesOffset[(u32)&((PanelDisplayState *)0)->savedVisiblePlanes == 0xa4 ? 1 : -1];
typedef char VisibleWindowsOffset[(u32)&((PanelDisplayState *)0)->savedVisibleWindows == 0xa8 ? 1 : -1];
typedef char Bg3PriorityOffset[(u32)&((PanelDisplayState *)0)->savedBg3Priority == 0xac ? 1 : -1];
typedef char FadeEngineOffset[(u32)&((PanelDisplayState *)0)->fadeEngine == 0xc0 ? 1 : -1];
typedef char FadePendingOffset[(u32)&((PanelDisplayState *)0)->fadePending == 0xc4 ? 1 : -1];
typedef char PanelDisplayStateIs200Bytes[sizeof(PanelDisplayState) == 0xc8 ? 1 : -1];

extern PanelDisplayState *gPanelState;
extern char sMain_PoffRefresh_02055f54[];
extern void G2x_SetBlendBrightness_(u32 registerAddress, int planes, int brightness);
extern void G2x_SetBlendAlpha_(u32 *registerAddress, u32 firstPlanes,
                             u32 secondPlanes, u32 firstWeight, u32 secondWeight);
extern void GXx_SetMasterBrightness_(u16 *registerAddress, int brightness);
extern int func_ov001_02063a38(void);
extern void NotifyBothOrOne(u32 mask, const char *name, int index);

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_SUB_DISPCNT (*(vu32 *)0x04001000)
#define REG_BG3CNT (*(vu16 *)0x0400000e)

static inline u32 GetMainVisiblePlanes(void)
{
    return (REG_DISPCNT & 0x1f00) >> 8;
}

static inline u32 GetSubVisiblePlanes(void)
{
    return (REG_SUB_DISPCNT & 0x1f00) >> 8;
}

static inline void SetBg3Priority(int priority)
{
    REG_BG3CNT = (u16)((REG_BG3CNT & ~3) | priority);
}

/* Restore main display settings from pause-panel state shared with VBlank. */
void RestorePanelDisplayState(void)
{
    volatile PanelDisplayState *panel = gPanelState;

    switch (panel->fadeEngine) {
    case 1:
        G2x_SetBlendBrightness_(0x04000050, GetMainVisiblePlanes(), 0);
        break;
    case 2:
        G2x_SetBlendBrightness_(0x04001050, GetSubVisiblePlanes(), 0);
        break;
    case 3:
        G2x_SetBlendBrightness_(0x04000050, GetMainVisiblePlanes(), 0);
        G2x_SetBlendBrightness_(0x04001050, GetSubVisiblePlanes(), 0);
        break;
    }

    panel->fadeEngine = 3;
    if (func_ov001_02063a38() == 8) {
        G2x_SetBlendAlpha_((u32 *)0x04000050, 1, 0x22, 0, 16);
    }
    if (func_ov001_02063a38() == 8) {
        SetBg3Priority(panel->savedBg3Priority);
    }
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (panel->savedVisiblePlanes << 8);
    REG_DISPCNT = (REG_DISPCNT & ~0xe000) | (panel->savedVisibleWindows << 13);
    GXx_SetMasterBrightness_((u16 *)0x0400006c, panel->savedMainBrightness);
    NotifyBothOrOne(1, sMain_PoffRefresh_02055f54, -1);
    panel->fadePending = 0;
}
