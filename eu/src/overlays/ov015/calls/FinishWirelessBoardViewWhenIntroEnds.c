#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xe1];
    u8 bits0_2 : 3;
    u8 flagE1_3 : 1;
    u8 flagE1_4 : 1;
    u8 bits5_6 : 2;
    u8 flagE1_7 : 1;
    u8 bitE2_0 : 1;
    u8 flagE2_1 : 1;
    u8 bitsE2_2_7 : 6;
} PanelState;

extern u32 UpdateWirelessBoardIntro(void);
extern void ReleaseWorkBuffer(void);
extern void InitOv002SubPanelGraphics(void);
extern void ResetOv002SubPanelText(int selector);
extern void SetWirelessMenuState(int mode);
extern PanelState *gWirelessMenuWork;

void FinishWirelessBoardViewWhenIntroEnds(void) {
    if (UpdateWirelessBoardIntro() != 0) {
        return;
    }
    ReleaseWorkBuffer();
    gWirelessMenuWork->flagE1_3 = 0;
    gWirelessMenuWork->flagE2_1 = 0;
    gWirelessMenuWork->flagE1_4 = 0;
    gWirelessMenuWork->flagE1_7 = 0;
    InitOv002SubPanelGraphics();
    ResetOv002SubPanelText(0);
    SetWirelessMenuState(2);
}
