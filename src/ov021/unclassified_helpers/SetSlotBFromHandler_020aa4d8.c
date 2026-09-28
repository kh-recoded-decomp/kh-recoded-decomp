#include "nitro/types.h"

extern u32 func_ov021_020aa6e4(void);

typedef struct {
    u8 pad_000[0x64];
    u32 slotB;
} ObjHandle;

void SetSlotBFromHandler_020aa4d8(ObjHandle *obj)
{
    obj->slotB = func_ov021_020aa6e4();
}
