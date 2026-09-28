#include "nitro/types.h"

extern void InitObjManager_0204efa8(int manager, u32 *config);

void InitObjManagerAndMark_020b9060(void *obj, void *config) {
    InitObjManager_0204efa8((int)obj, (u32 *)config);
    *(u32 *)((u8 *)obj + 0x6478) |= 4;
}
