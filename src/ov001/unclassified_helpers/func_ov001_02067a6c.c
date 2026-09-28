#include "nitro/types.h"

extern u32 data_ov001_020a046c;
extern void func_0202eee8(void *entry);

void func_ov001_02067a6c(void)
{
    s32 i;
    u8 *base;
    u8 *entry;

    i = 0;
    base = (u8 *)(data_ov001_020a046c + 0x18);
    do {
        entry = base + i * 0x108;
        if ((entry[0x104] & 0x80) != 0) {
            func_0202eee8(entry);
            entry[0x104] = 0;
        }
        i = i + 1;
    } while (i < 0x10);
}
