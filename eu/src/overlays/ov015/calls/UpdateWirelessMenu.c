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

extern s8 *gWirelessMenuWork;
extern PanelStateCallbacks gLinkPanelExitHandler[];
extern void RTC_GetDate(void *ptr);
extern void PrepareOpponentProfile(void);
extern u8 TickConnectState(void);
extern void UpdateDriftingElementsByMode(void);
extern void BlinkPanelCursor(void);
extern void UpdateDisplayObjectListQueued(void *list);
extern void BobPanelWidgets(void);

int UpdateWirelessMenu(void) {
    s8 state;

    RTC_GetDate(gWirelessMenuWork + 0xf0);
    if (((PanelFlagsE2d *)(gWirelessMenuWork + 0xe2))->flag4 != 0) {
        u8 result;
        PrepareOpponentProfile();
        result = TickConnectState();
        gWirelessMenuWork[0xbf] = result;
    }
    gLinkPanelExitHandler[(s16)gWirelessMenuWork[0]].onUpdate();
    if (((PanelFlagsE1b *)(gWirelessMenuWork + 0xe1))->flag4 != 0) {
        UpdateDriftingElementsByMode();
    }
    if (((PanelFlagsE1b *)(gWirelessMenuWork + 0xe1))->twobit5_6 != 0) {
        BlinkPanelCursor();
    }
    if (((PanelFlagsE0c *)(gWirelessMenuWork + 0xe0))->flag3 == 0) {
        UpdateDisplayObjectListQueued(gWirelessMenuWork + 0x644);
        state = gWirelessMenuWork[0];
        if (state != 5) {
            if (!(state == 1 || state == 0 || state == 7)) {
                BobPanelWidgets();
            }
            UpdateDisplayObjectListQueued(gWirelessMenuWork + 0x6ac0);
        }
    }
    return gWirelessMenuWork[1];
}
