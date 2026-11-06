#include "nitro/types.h"

extern u32 gOv028FieldSceneWorkStorage;
extern u32 GetPendingWorldEntryData(void);
extern u32 GetSignedByteAt1(void);
extern u32 GetSignedByteAt3(u32 value);
extern void StoreFieldSessionEntryPayloadPair(u32 param1, u32 param2);

u32 Ov028SceneState_StoreEventRecordBytes(void)
{
    u32 context = gOv028FieldSceneWorkStorage;
    u32 arg1;
    u32 arg2;

    arg1 = GetPendingWorldEntryData();
    arg2 = GetSignedByteAt1();
    arg1 = GetSignedByteAt3(arg1);
    StoreFieldSessionEntryPayloadPair(arg2, arg1);
    *(u16 *)(context + 6) = *(u16 *)(context + 6) | 2;
    return 7;
}
