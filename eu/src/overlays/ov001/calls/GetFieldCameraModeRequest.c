#include "nitro/types.h"

extern u32 gFieldSessionWork;

s32 GetFieldCameraModeRequest(void) {
    return (s32)*(s8 *)(gFieldSessionWork + 0x27b4);
}
