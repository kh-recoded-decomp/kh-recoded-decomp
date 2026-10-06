#include "nitro/types.h"

typedef struct {
    void (*onUpdate)(void);
    void (*onDraw)(void);
    void (*onExit)(void);
} PanelStateCallbacks;

typedef struct {
    u8 pad0_3 : 4;
    u8 flag4 : 1;
    u8 twobit5_6 : 2;
    u8 pad7 : 1;
} PanelFlagsE1b;

typedef struct {
    u8 pad0_2 : 3;
    u8 flag3 : 1;
    u8 pad4_7 : 4;
} PanelFlagsE0c;

typedef struct {
    u8 pad0_3 : 4;
    u8 flag4 : 1;
    u8 pad5_7 : 3;
} PanelFlagsE2d;

extern s8 *data_ov015_0207e960;
extern PanelStateCallbacks gLinkPanelExitHandler[];
extern void RTC_GetDate(void *ptr);
extern void PrepareOpponentProfile(void);
extern u8 TickConnectState(void);
extern void UpdateDriftingElementsByMode(void);
extern void BlinkPanelCursor(void);
extern void NNS_FndInitListWithOffset0_0204f130(void *list);
extern void BobPanelWidgets(void);

int func_ov015_0206c4f0(void) {
    s8 state;

    RTC_GetDate(data_ov015_0207e960 + 0xf0);
    if (((PanelFlagsE2d *)(data_ov015_0207e960 + 0xe2))->flag4 != 0) {
        u8 result;
        PrepareOpponentProfile();
        result = TickConnectState();
        data_ov015_0207e960[0xbf] = result;
    }
    gLinkPanelExitHandler[(s16)data_ov015_0207e960[0]].onUpdate();
    if (((PanelFlagsE1b *)(data_ov015_0207e960 + 0xe1))->flag4 != 0) {
        UpdateDriftingElementsByMode();
    }
    if (((PanelFlagsE1b *)(data_ov015_0207e960 + 0xe1))->twobit5_6 != 0) {
        BlinkPanelCursor();
    }
    if (((PanelFlagsE0c *)(data_ov015_0207e960 + 0xe0))->flag3 == 0) {
        NNS_FndInitListWithOffset0_0204f130(data_ov015_0207e960 + 0x644);
        state = data_ov015_0207e960[0];
        if (state != 5) {
            if (!(state == 1 || state == 0 || state == 7)) {
                BobPanelWidgets();
            }
            NNS_FndInitListWithOffset0_0204f130(data_ov015_0207e960 + 0x6ac0);
        }
    }
    return data_ov015_0207e960[1];
}
