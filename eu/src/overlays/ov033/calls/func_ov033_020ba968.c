#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[8];
    u32 result;
} State_020baac0;

extern State_020baac0 *data_ov033_020baae0;

void func_ov033_020ba968(u32 value)
{
    data_ov033_020baae0->result = value;
    data_ov033_020baae0->flags |= 0x4000;
}
