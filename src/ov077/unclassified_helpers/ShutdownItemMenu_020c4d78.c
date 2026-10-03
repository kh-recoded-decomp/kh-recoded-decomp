#include "nitro/types.h"

typedef struct ItemMenu {
    void *bufferA;
    void *bufferB;
    u8 pad_08[0xc];
    u8 screen[1];
} ItemMenu;

extern u32 data_ov077_020ca380;

extern void ReleaseScreenResources_020c90bc(void *screen);
extern int ZeroHalfThenFree_0202cd78(void *block);
extern void ReleaseScreenSprites_020c5270(ItemMenu *menu);
extern void func_ov045_020be6a0(void);
extern void NNS_GfdResetFrmTexVramState_0201391c(void);
extern void func_02013d74(void);
extern void FillSelectionRecordFromGroup_0204f8dc(void);
extern void SyncSelectionRecordFromSlotEntry_0204fabc(void);
extern void func_0204fba0(void);

void ShutdownItemMenu_020c4d78(ItemMenu *menu)
{
    ReleaseScreenResources_020c90bc(menu->screen);
    ZeroHalfThenFree_0202cd78(menu->bufferA);
    ZeroHalfThenFree_0202cd78(menu->bufferB);
    ReleaseScreenSprites_020c5270(menu);
    func_ov045_020be6a0();
    *(vu32 *)0x04000014 = 0;
    *(vu32 *)0x04000018 = 0;
    *(vu32 *)0x0400001c = 0;
    *(vu32 *)0x04000000 &= ~0xe000;
    NNS_GfdResetFrmTexVramState_0201391c();
    func_02013d74();
    FillSelectionRecordFromGroup_0204f8dc();
    SyncSelectionRecordFromSlotEntry_0204fabc();
    func_0204fba0();
    data_ov077_020ca380 = 0;
}
