#include "nitro/types.h"

typedef void (*Callback)(void *node);

extern u32 data_ov001_020a04d8;
extern void func_ov001_02087190(void);

void InvokeListNodeCallbacks_0207eff0(void)
{
    u8 *node;
    Callback callback;

    for (node = *(u8 **)(data_ov001_020a04d8 + 8); node != 0; node = *(u8 **)(node + 4)) {
        callback = *(Callback *)(*(u8 **)(node + 8) + 0x40);
        if (callback != 0) {
            (*callback)(node);
        }
    }
    func_ov001_02087190();
}
