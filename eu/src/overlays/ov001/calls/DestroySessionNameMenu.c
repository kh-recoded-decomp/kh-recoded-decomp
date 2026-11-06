#include "nitro/types.h"

extern u32 gFieldSessionWork;
extern u32 DestroyTaskObjectWrapper();

void DestroySessionNameMenu(void) {
    u32 base = gFieldSessionWork;
    if (*(s32 *)(gFieldSessionWork + 0x27e8) != -1) {
        DestroyTaskObjectWrapper();
        *(u32 *)(base + 0x27e8) = 0xffffffff;
    }
}
