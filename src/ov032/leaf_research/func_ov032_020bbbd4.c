#include "nitro/types.h"

u8 *func_ov032_020bbbd4(void *param0, s32 param1) {
    u8 *array1 = *(u8 **)((u8 *)param0 + 0xcc);
    u32 word0 = *(u32 *)(array1 + param1 * 0x1e0);
    u32 kind = word0 >> 0x1c;
    u8 *array2 = *(u8 **)((u8 *)param0 + 0xd0);
    return array2 + kind * 0x28;
}
