#include "nitro/types.h"

u8 *func_ov032_020bbc80(void *param0) {
    void *field4 = *(void **)((u8 *)param0 + 4);
    u8 *array = *(u8 **)((u8 *)field4 + 0xcc);
    u8 *record = *(u8 **)((u8 *)param0 + 0xec);
    s8 index = *(s8 *)(record + 2);
    return array + index * 0x1e0;
}
