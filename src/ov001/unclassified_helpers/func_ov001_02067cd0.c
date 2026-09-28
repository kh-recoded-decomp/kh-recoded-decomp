#include "nitro/types.h"

extern u32 data_ov001_020a046c;

void func_ov001_02067cd0(s32 index, s32 enable)
{
    u8 *entry;

    entry = (u8 *)(data_ov001_020a046c + 0x18 + index * 0x108);
    if (enable != 0) {
        entry[0x104] = entry[0x104] | 1;
        return;
    }
    entry[0x104] = entry[0x104] & 0xfe;
}
