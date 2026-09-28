#include "nitro/types.h"

void SetTableAEntry_02003828(int index, u32 value) {
    *(u32 *)(index * 4 + 0x2fffdc4) = value;
}
