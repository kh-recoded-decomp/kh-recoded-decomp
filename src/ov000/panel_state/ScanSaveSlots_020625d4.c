#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x48];
    s32 slotIndex;
    s32 usedSlotCount;
    u8 pad_50[0x6688 - 0x50];
    BOOL progressFlag;
    u8 pad_668c[0x66c4 - 0x668c];
    u32 unlockFlagA;
    u32 unlockFlagB;
    u8 pad_66cc[0x66e8 - 0x66cc];
    BOOL loadFailed;
} Panel;

extern int PollCardThreadResult_02027060(void);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void ClearGlobalPackedBit_02027334(int bitIndex);
extern void StartCardWriteFromSlot_02027034(int slot);
extern void SetPanelState_02061db0(Panel *panel, s32 state, u32 param1, u32 param2);

s32 ScanSaveSlots_020625d4(Panel *panel)
{
    s32 result = -1;

    switch (PollCardThreadResult_02027060()) {
    case 3:
        panel->loadFailed = TRUE;
        SetPanelState_02061db0(panel, 1, 0, 0);
        result = 0xe;
        break;
    case 0:
        if (IsGlobalPackedBitSet_02027304(0xbea)) {
            panel->progressFlag = TRUE;
        }
        panel->unlockFlagA |= (u8)(IsGlobalPackedBitSet_02027304(0xf4c) != 0);
        panel->unlockFlagB |= (u8)(IsGlobalPackedBitSet_02027304(0xf4d) != 0);
    case 4:
        panel->usedSlotCount++;
    case 2:
        if (++panel->slotIndex < 2) {
            StartCardWriteFromSlot_02027034(panel->slotIndex);
            break;
        }
        SetPanelState_02061db0(panel, 0, 0, 30);
        result = 6;
        if (panel->unlockFlagA) {
            SetGlobalPackedBit_02027320(0x1150);
        } else {
            ClearGlobalPackedBit_02027334(0x1150);
            ClearGlobalPackedBit_02027334(0xf4c);
        }
        if (panel->unlockFlagB) {
            SetGlobalPackedBit_02027320(0x1151);
        } else {
            ClearGlobalPackedBit_02027334(0x1151);
            ClearGlobalPackedBit_02027334(0xf4d);
        }
        if (panel->progressFlag) {
            SetGlobalPackedBit_02027320(0xbea);
        } else {
            ClearGlobalPackedBit_02027334(0xbea);
        }
        break;
    }
    return result;
}
