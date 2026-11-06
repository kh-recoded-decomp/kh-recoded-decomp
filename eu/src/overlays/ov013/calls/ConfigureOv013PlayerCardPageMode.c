#include "nitro/types.h"

typedef struct {
    u8 blockA : 1;
    u8 blockB : 1;
    u8 pad_2to7 : 6;
} StatusFlagsD259;

extern s8 gSceneHandoffSharedHeader[];
extern int IsPanelBusy(void);
extern void InitMenuScreenGraphics(void);
extern void ResetOv013PlayerCardPageDisplay(void);
extern void SetOv013MainLayerMask1e(void);
extern void SetPanelPhase(int mode);
extern int gOv013PanelGlobals;

/* Selects the player-card page path from the current position and every-tenth-entry rule. */
void ConfigureOv013PlayerCardPageMode(void) {
    int position = *(s8 *)(gOv013PanelGlobals + 0x2f0);
    if (IsPanelBusy() == 0) {
        position = gSceneHandoffSharedHeader[0x11] + gSceneHandoffSharedHeader[0x10];
    }
    if ((position + 1) % 10 != 0) {
        u8 status99 = *(u8 *)(gOv013PanelGlobals + 0x99);
        if ((((u32)status99 << 0x1d) >> 0x1f) == 0) {
            int flags = status99;
            flags = flags & ~8;
            *(u8 *)(gOv013PanelGlobals + 0x99) = (u8)flags;
            *(int *)(gOv013PanelGlobals + 0x2e8) = position;
            InitMenuScreenGraphics();
            SetOv013MainLayerMask1e();
            return;
        }
        if (((StatusFlagsD259 *)(gOv013PanelGlobals + 0xd259))->blockA) {
            return;
        }
        if (((StatusFlagsD259 *)(gOv013PanelGlobals + 0xd259))->blockB) {
            return;
        }
        {
            int flags = status99;
            flags = flags & ~8;
            *(u8 *)(gOv013PanelGlobals + 0x99) = (u8)flags;
        }
        SetPanelPhase(1);
        return;
    }
    *(int *)(gOv013PanelGlobals + 0x2e8) = position;
    InitMenuScreenGraphics();
    ResetOv013PlayerCardPageDisplay();
}
