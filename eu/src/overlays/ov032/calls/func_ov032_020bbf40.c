#include "nitro/types.h"

extern u8 *GetRowDefinition(void *param0, s32 param1);
extern void PickWeightedIndex(void *dst, s32 count);

void func_ov032_020bbf40(void *param0, s32 param1) {
    u8 *entry = GetRowDefinition(param0, param1);
    PickWeightedIndex(entry + 0x1b, 4);
}
