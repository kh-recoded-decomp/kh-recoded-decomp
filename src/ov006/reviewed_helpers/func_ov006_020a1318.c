#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x0E];
    s16 stride;
} GridInfo;

int func_ov006_020a1318(GridInfo *info, int index, int base)
{
    return base + index * info->stride;
}
