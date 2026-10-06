#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
} State_020baac0;

extern State_020baac0 *data_ov033_020baae0;
extern void func_ov039_020bbb8c(u32 argument0);

u32 func_ov033_020ba71c(void)
{
    State_020baac0 *state = data_ov033_020baae0;
    u32 result = 0xffffffff;

    func_ov039_020bbb8c(0);
    if ((state->flags & 0x4000) != 0) {
        result = 2;
    }
    return result;
}
