#include "nitro/types.h"

extern void func_ov001_02086384(void *node);
extern u32 data_ov001_020a04dc;

void func_ov001_02087010(void) {
    void **node = *(void ***)(data_ov001_020a04dc + 8);
    while (node != 0) {
        func_ov001_02086384(node);
        node = *node;
    }
}
