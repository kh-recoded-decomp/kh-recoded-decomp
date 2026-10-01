#include "nitro/types.h"

typedef struct Panel {
    u8 pad_00[0x4c];
    s32 usedSlotCount;
    s32 cursorIndex;
    u8 pad_54[0x6688 - 0x54];
    BOOL progressFlag;
    u8 pad_668c[0x66c4 - 0x668c];
    u32 unlockFlagA;
    u32 unlockFlagB;
} Panel;

extern u32 g_hasSaveData_0205fe20;

extern void SetPanelFlag_02061bc4(Panel *panel, int bit, BOOL enable);
extern void SetGlobalPackedBit_02027320(int bitIndex);

void ApplyPanelMenuFlags_02061bf4(Panel *panel, BOOL selectContinue)
{
    int i;

    for (i = 0; i < 4; i++) {
        SetPanelFlag_02061bc4(panel, i, TRUE);
    }

    if (panel->usedSlotCount == 0) {
        panel->cursorIndex = 0;
        g_hasSaveData_0205fe20 = 0;
        SetPanelFlag_02061bc4(panel, 1, FALSE);
        SetPanelFlag_02061bc4(panel, 2, FALSE);
        SetPanelFlag_02061bc4(panel, 3, FALSE);
        return;
    }

    if (selectContinue) {
        panel->cursorIndex = 1;
    }
    g_hasSaveData_0205fe20 = 1;
    if (!panel->progressFlag) {
        SetPanelFlag_02061bc4(panel, 3, FALSE);
    }
    if (panel->unlockFlagA) {
        SetGlobalPackedBit_02027320(0x1150);
    }
    if (panel->unlockFlagB) {
        SetGlobalPackedBit_02027320(0x1151);
    }
    if (panel->progressFlag) {
        SetGlobalPackedBit_02027320(0xbea);
    }
}
