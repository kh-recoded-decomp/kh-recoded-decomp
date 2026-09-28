#include "nitro/types.h"

extern s32 *func_ov021_020a8810(void);
extern void func_ov021_020a867c(s32 addr, u32 value);

void InvokeHandlerOnIndexedRecord_020a8e88(u32 unused0, s32 index, u32 value)
{
    s32 *table = func_ov021_020a8810();
    if (table != 0) {
        func_ov021_020a867c(*table + index * 0x138, value);
    }
}
