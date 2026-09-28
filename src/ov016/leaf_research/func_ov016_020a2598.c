#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x10];
    u8 srcBuffer[0x28];
    u8 dstBuffer[8];
} ObjectState;

extern void func_ov001_02080834(u8 *src, u8 *dst, u32 count, u32 width, u32 height,
                                 u32 depth, u32 flags, u32 param, u32 stride);

void func_ov016_020a2598(ObjectState *obj, u32 param)
{
    func_ov001_02080834(obj->srcBuffer, obj->dstBuffer, 3, 0x1800, 0x1800, 0x1800, 0, param, 4);
}
