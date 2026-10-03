#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00[0x18];
    void *bufferA;
    void *bufferB;
    u8 pad_20[4];
    u8 panel[1];
} SlotMenu;

extern u32 data_ov076_020cd3e0;

extern void MenuPanel_Destroy_020cc088(void *panel);
extern int ZeroHalfThenFree_0202cd78(void *block);
extern void SlotMenu_ReleaseSlotObjects_020c68dc(SlotMenu *menu);
extern void SlotMenu_ReleaseSprites_020c6c7c(SlotMenu *menu);
extern void func_ov045_020be6a0(void);
extern void NNS_GfdResetFrmTexVramState_0201391c(void);
extern void func_02013d74(void);
extern void SetStateFlagBits_020bc688(u8 clearMask, u8 setBits);
extern void RefreshSlotRecordCache_02028f44(void);
extern void BuildSelectionEntryList_0204f98c(void);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern void ReleaseRecordManager_02051cdc(void);

void SlotMenu_Shutdown_020c5ee0(SlotMenu *menu)
{
    MenuPanel_Destroy_020cc088(menu->panel);
    ZeroHalfThenFree_0202cd78(menu->bufferA);
    ZeroHalfThenFree_0202cd78(menu->bufferB);
    SlotMenu_ReleaseSlotObjects_020c68dc(menu);
    SlotMenu_ReleaseSprites_020c6c7c(menu);
    func_ov045_020be6a0();
    *(vu32 *)0x04000014 = 0;
    *(vu32 *)0x04000018 = 0;
    *(vu32 *)0x0400001c = 0;
    *(vu32 *)0x04000000 &= ~0xe000;
    NNS_GfdResetFrmTexVramState_0201391c();
    func_02013d74();
    SetStateFlagBits_020bc688(1, 1);
    RefreshSlotRecordCache_02028f44();
    BuildSelectionEntryList_0204f98c();
    ReleaseRecordSlot_02051dfc(0);
    ReleaseRecordSlot_02051dfc(1);
    ReleaseRecordSlot_02051dfc(5);
    ReleaseRecordManager_02051cdc();
    data_ov076_020cd3e0 = 0;
}
