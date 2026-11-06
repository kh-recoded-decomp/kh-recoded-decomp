#include "nitro/types.h"

extern u32 gFieldSessionWork;

void StoreFieldSessionContainerSlot(s32 index, u32 value) {
    *(u32 *)(gFieldSessionWork + index * 4 + 0x25b0) = value;
}
