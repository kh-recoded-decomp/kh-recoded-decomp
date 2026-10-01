#include "nitro/types.h"

typedef struct PanelScene PanelScene;
typedef void (*PanelStateFn)(PanelScene *panel);

typedef struct PanelStateTable {
    PanelStateFn handlers[7];
} PanelStateTable;

struct PanelScene {
    u8 pad_000[0x30];
    int state;
    u8 pad_034[0xc];
    int touchActive;
    u8 pad_044[0x102 - 0x44];
    u8 channel;
    u8 pad_103[5];
    int timerMode;
};

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchSample;

extern PanelScene *data_ov001_020a04c8;
extern PanelStateTable data_ov001_0209ef4c;
extern u8 GetPrimarySelectionByte1E_02050514(void);
extern BOOL func_ov001_020645c8(u32 value);
extern int func_ov001_02064784(void);
extern void PulsePaletteFlash_0207a9f4(PanelScene *panel);
extern void UpdateIdleTimerToggle_0207aec8(PanelScene *panel);
extern void UpdatePanelConfirmTimer_0207af6c(PanelScene *panel);
extern u32 func_ov001_0207b3cc(void);
extern BOOL func_ov001_0207b5e8(void);
extern void func_ov001_0207b6c4(void);
extern int LookupChannelEntry_020b628c(int channel);
extern int CopySourceBlock_020b9f7c(TouchSample *sample);
extern void func_ov027_020b9f9c(void);

int UpdatePanelScene_0207aff0(void)
{
    PanelScene *panel = data_ov001_020a04c8;
    TouchSample sample;
    PanelStateTable table = data_ov001_0209ef4c;
    u8 channel = GetPrimarySelectionByte1E_02050514();

    if (table.handlers[panel->state] != NULL) {
        table.handlers[panel->state](panel);
    }
    if (panel->channel != channel && func_ov001_0207b3cc() == 2 && func_ov001_0207b5e8()) {
        LookupChannelEntry_020b628c(channel);
        panel->channel = channel;
    }
    if (!func_ov001_02064784() && func_ov001_020645c8(0x370b)) {
        UpdatePanelConfirmTimer_0207af6c(panel);
    } else {
        switch (panel->timerMode) {
        case 0:
            UpdateIdleTimerToggle_0207aec8(panel);
            break;
        case 1:
            UpdatePanelConfirmTimer_0207af6c(panel);
            break;
        case 2:
            break;
        }
    }
    if (func_ov001_0207b3cc() == 0 && func_ov001_0207b5e8()) {
        PulsePaletteFlash_0207a9f4(panel);
    }
    if (panel->touchActive != 0) {
        CopySourceBlock_020b9f7c(&sample);
        if (sample.touch == 0) {
            func_ov001_0207b6c4();
        } else {
            func_ov027_020b9f9c();
        }
    }
    return 0;
}
