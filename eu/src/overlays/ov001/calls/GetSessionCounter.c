#include "nitro/types.h"

extern u32 gFieldSessionWork;

u32 GetSessionCounter(s32 index) {
    return *(u32 *)(gFieldSessionWork + index * 4 + 0x2938);
}
