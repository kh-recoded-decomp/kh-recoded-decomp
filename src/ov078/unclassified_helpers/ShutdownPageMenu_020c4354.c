#include "nitro/types.h"

typedef struct PageMenu {
    void *bufferA;
    void *bufferB;
    void *bufferC;
    void *imageA;
    u8 pad_10[8];
    void *imageB;
} PageMenu;

extern u32 data_ov078_020c51c0;

extern void OS_RescheduleThread_020c4708(void);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern void ReleaseRecordManager_02051cdc(void);
extern void FreePointerIfSet_020ba294(void **ptr);
extern int ZeroHalfThenFree_0202cd78(void *block);
extern void func_ov045_020be6a0(void);
extern void NNS_GfdResetFrmTexVramState_0201391c(void);
extern void func_02013d74(void);

void ShutdownPageMenu_020c4354(PageMenu *menu)
{
    OS_RescheduleThread_020c4708();
    ReleaseRecordSlot_02051dfc(2);
    ReleaseRecordSlot_02051dfc(0);
    ReleaseRecordManager_02051cdc();
    FreePointerIfSet_020ba294(&menu->imageA);
    FreePointerIfSet_020ba294(&menu->imageB);
    ZeroHalfThenFree_0202cd78(menu->bufferA);
    ZeroHalfThenFree_0202cd78(menu->bufferB);
    ZeroHalfThenFree_0202cd78(menu->bufferC);
    func_ov045_020be6a0();
    *(vu32 *)0x04000014 = 0;
    *(vu32 *)0x04000018 = 0;
    *(vu32 *)0x0400001c = 0;
    *(vu32 *)0x04000000 &= ~0xe000;
    NNS_GfdResetFrmTexVramState_0201391c();
    func_02013d74();
    data_ov078_020c51c0 = 0;
}
