#include "nitro/types.h"

extern void func_0202a1c4(void *ptr);
extern u32 data_ov001_020a04dc;

void func_ov001_02087414(void) {
    void *ptr = *(void **)(data_ov001_020a04dc + 0x1bc);
    if (ptr != 0) {
        func_0202a1c4(ptr);
        *(u32 *)(data_ov001_020a04dc + 0x1bc) = 0;
    }
    ptr = *(void **)(data_ov001_020a04dc + 0x1c4);
    if (ptr != 0) {
        func_0202a1c4(ptr);
        *(u32 *)(data_ov001_020a04dc + 0x1c4) = 0;
    }
}
