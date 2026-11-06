#include "nitro/types.h"

extern u32 gFieldSessionWork;

void SetFieldCameraModeRequest(u8 value) {
    *(u8 *)(gFieldSessionWork + 0x27b4) = value;
}
