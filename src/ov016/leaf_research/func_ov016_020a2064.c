#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x50];
    u32 value1;
    u32 value2;
    u32 value3;
} ObjectState;

extern u32 func_ov016_020a1df4(u32 source, u32 *cursor);

void func_ov016_020a2064(ObjectState *obj, u32 source, u32 *cursor)
{
    obj->value1 = func_ov016_020a1df4(source, cursor);
    obj->value2 = func_ov016_020a1df4(source, cursor);
    obj->value3 = func_ov016_020a1df4(source, cursor);
}
