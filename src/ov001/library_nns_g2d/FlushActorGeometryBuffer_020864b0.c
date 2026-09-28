#include "nitro/types.h"

extern void FlushGeometryCommandBuffer_01ffa204(const void *src, u32 size);
extern u8 data_ov001_0209f174[0x154];

void FlushActorGeometryBuffer_020864b0(void) {
    FlushGeometryCommandBuffer_01ffa204(data_ov001_0209f174, 0x154);
}
