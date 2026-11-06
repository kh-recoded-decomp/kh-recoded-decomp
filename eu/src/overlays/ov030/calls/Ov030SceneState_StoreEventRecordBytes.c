#include "nitro/types.h"

extern u32 gOv030SceneWork;
extern u32 GetPendingWorldEntryData(void);
extern s8 GetSignedByteAt1(void);
extern s8 GetSignedByteAt3(u32 arg);
extern void StoreFieldSessionEntryPayloadPair(u32 a, u32 b);

u32 Ov030SceneState_StoreEventRecordBytes(void)
{
    u32 ctx;
    u32 valueA;
    u32 valueB;

    ctx = gOv030SceneWork;
    valueA = GetPendingWorldEntryData();
    valueB = GetSignedByteAt1();
    valueA = GetSignedByteAt3(valueA);
    StoreFieldSessionEntryPayloadPair(valueB, valueA);
    *(u16 *)(ctx + 6) = *(u16 *)(ctx + 6) | 2;
    return 7;
}
