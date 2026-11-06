#include "nitro/types.h"

extern u32 gFieldSessionWork;

void StoreFieldSessionEntryPayloadPair(u8 param1, u8 param2) {
    u32 base = gFieldSessionWork;
    *(u8 *)(gFieldSessionWork + 0x2744) = param1;
    *(u8 *)(base + 0x2745) = param2;
}
