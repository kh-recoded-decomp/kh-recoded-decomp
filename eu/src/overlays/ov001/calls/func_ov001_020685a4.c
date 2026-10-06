#include "nitro/types.h"

extern u32 data_ov001_020a0490;
extern void func_ov001_020685d4(void);
extern void ReleaseRecordSlot(s32 mode);
extern void ReleaseServiceInstance_020876a0(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void func_ov001_020685a4(void)
{
    u32 *ctx;

    ctx = (u32 *)data_ov001_020a0490;
    func_ov001_020685d4();
    ReleaseRecordSlot(4);
    ReleaseServiceInstance_020876a0();
    if (*ctx != 0) {
        NNSi_FndFreeFromDefaultHeap((void *)*ctx);
    }
    NNSi_FndFreeFromDefaultHeap((void *)data_ov001_020a0490);
    data_ov001_020a0490 = 0;
}
