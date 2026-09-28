#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xc0];
    u32 flags;
} ObjectState;

extern u32 func_ov016_020a1de0(u32 source, u32 *cursor);
extern u32 func_ov001_02087214(u32 value);
extern ObjectState *func_ov001_0208635c(u32 key1, u32 key2);

u32 func_ov016_020a2224(u32 source, u32 arg1, u32 unused, u32 arg2)
{
    u32 val1;
    u32 val2;
    ObjectState *obj;
    u32 cursor1;
    u32 cursor2;

    cursor1 = arg1;
    cursor2 = arg2;
    val1 = func_ov016_020a1de0(source, &cursor1);
    val2 = func_ov016_020a1de0(source, &cursor1);
    val1 = func_ov001_02087214(val1);
    obj = func_ov001_0208635c(val1, val2);
    obj->flags |= 0x400000;
    return 1;
}
