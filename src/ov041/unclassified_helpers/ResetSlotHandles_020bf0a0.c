#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;

void ResetSlotHandles_020bf0a0(void) {
    int offset;
    int i;
    int manager;

    i = 0;
    manager = *(int *)(data_ov035_020bc4e0 + 0xb8);
    *(u32 *)(manager + 0x2318) = 0;
    do {
        offset = i * 4;
        i = i + 1;
        *(u32 *)(manager + offset + 0x231c) = 0xffffffff;
    } while (i < 3);
}
