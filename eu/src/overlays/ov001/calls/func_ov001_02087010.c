#include "nitro/types.h"

extern void func_ov001_02086390(void *node);
extern u32 data_ov001_020a04fc;

void func_ov001_02087010(void) {
    u32 base = data_ov001_020a04fc;
    void **node = *(void ***)(base + 8);
    while (node != 0) {
        func_ov001_02086390(node);
        node = *node;
    }
    *(u32 *)(base + 8) = 0;
    *(u32 *)(base + 0xc) = 0;
    *(u16 *)(base + 6) = 0;
}
