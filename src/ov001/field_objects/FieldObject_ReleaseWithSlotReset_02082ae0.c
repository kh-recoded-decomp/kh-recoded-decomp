#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x67];
    u8 activeBit : 1;
    u8 otherFlags : 7;
} FieldObject;

typedef struct Session {
    u8 pad_000[0x214];
    u32 lowFlags : 19;
    u32 flag19 : 1;
    u32 highFlags : 12;
} Session;

extern Session *data_ov001_020a0460;
extern void func_ov001_02063d4c(int parameterId, int value);
extern BOOL SetSlotLayoutHighlight_0207d45c(int enable);
extern void ReleaseOwnerResource_0207f20c(FieldObject *object, int arg);

void FieldObject_ReleaseWithSlotReset_02082ae0(FieldObject *object, int arg)
{
    func_ov001_02063d4c(6, 0x1000);
    object->activeBit = 0;
    SetSlotLayoutHighlight_0207d45c(0);
    data_ov001_020a0460->flag19 = 0;
    ReleaseOwnerResource_0207f20c(object, arg);
}
