#include "nitro/types.h"

extern u32 data_ov030_020bd020;
extern u32 GetPendingWorldEntryData(void);
extern s8 GetSignedByteAt1(void);
extern s8 GetSignedByteAt3(u32 arg);
extern void func_ov001_02063848(u32 a, u32 b);

u32 Ov030SceneState_StoreEventRecordBytes(void)
{
    u32 ctx;
    u32 valueA;
    u32 valueB;

    ctx = data_ov030_020bd020;
    valueA = GetPendingWorldEntryData();
    valueB = GetSignedByteAt1();
    valueA = GetSignedByteAt3(valueA);
    func_ov001_02063848(valueB, valueA);
    *(u16 *)(ctx + 6) = *(u16 *)(ctx + 6) | 2;
    return 7;
}
