#include "nitro/types.h"

typedef struct {
    u16 field0;
    u16 field1;
    u32 handle;
} ResourceSlot;

extern ResourceSlot *func_ov001_0209c1fc();
extern u32 func_0204dbe4();
extern u32 func_0204dc3c();

void ReleaseSlotResource_0209d15c(void)
{
    ResourceSlot *slot;
    u32 flag;

    slot = func_ov001_0209c1fc();
    if ((slot != 0) && (slot->handle != 0)) {
        flag = func_0204dc3c();
        if (flag != 0) {
            func_0204dbe4(slot->handle);
        }
        slot->handle = 0;
        slot->field0 = 0;
        slot->field1 = 0;
    }
}
