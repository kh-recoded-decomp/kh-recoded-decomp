#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x100];
    u32 field100;
} UnkStruct_ov056_020d3b1c;

void func_ov056_020d3b1c(u32 unused, UnkStruct_ov056_020d3b1c *target, u32 value)
{
    target->field100 = value;
}
