#include "nitro/types.h"

extern u32 data_ov001_020a04f8;
extern void FieldObject_Refresh(void *node);
extern void func_ov001_02087038(void);

void func_ov001_0207ef44(void)
{
    u8 *node;

    for (node = *(u8 **)(data_ov001_020a04f8 + 8); node != 0; node = *(u8 **)(node + 4)) {
        FieldObject_Refresh(node);
    }
    func_ov001_02087038();
}
