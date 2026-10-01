#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x30];
    s32 phase;
    u8 pad_34[0x38 - 0x34];
    s32 ready;
    u8 pad_3c[0x4c - 0x3c];
    s32 altDisplay;
    u8 pad_50[0x58 - 0x50];
    s32 fadeSpeed;
    u8 pad_5c[0xd8 - 0x5c];
    s32 mode;
    u8 pad_dc[0xe4 - 0xdc];
    void *graphics[4];
    u8 pad_f4[0x108 - 0xf4];
    u32 sessionFlags;
} PanelScene;

typedef struct {
    u32 unk_00 : 12;
    u32 panelStyle : 2;
} SessionStateFlags;

extern PanelScene *data_ov001_020a04c8;
extern u8 *data_0205fe0c;

extern BOOL func_ov001_02064490(void);
extern u32 func_ov001_0207b3cc(void);
extern void *func_ov025_020b6270(int index);
extern void SetDisplaySetting_02029f28(int value);
extern void func_ov001_0207b20c(PanelScene *panel, int mode);

BOOL RequestPanelModeChange_0207b27c(int mode) {
    PanelScene *panel = data_ov001_020a04c8;
    int i;

    if (panel->phase != 0 && panel->phase != 6) {
        return FALSE;
    }
    if (panel->mode != 4 && func_ov001_02064490()) {
        return FALSE;
    }
    if (panel->ready == 0) {
        return FALSE;
    }
    if (panel->mode == mode) {
        return FALSE;
    }
    if (mode != 2) {
        panel->sessionFlags = ((SessionStateFlags *)(data_0205fe0c + 0x2878))->panelStyle;
    }
    if (func_ov001_0207b3cc() == 2) {
        for (i = 0; i < 4; i++) {
            panel->graphics[i] = func_ov025_020b6270(i);
        }
    }
    SetDisplaySetting_02029f28(panel->altDisplay != 0 ? 2 : 1);
    func_ov001_0207b20c(panel, mode);
    panel->fadeSpeed = 6;
    return TRUE;
}
