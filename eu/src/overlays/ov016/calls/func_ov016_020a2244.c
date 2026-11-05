#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xc0];
    u32 flags;
} ObjectState;

extern u32 ScriptVm_ConsumeOperandInt(u32 source, u32 *cursor);
extern u32 GetFieldEntryPoolAtIndex(u32 value);
extern ObjectState *GetEntryPoolObjectAtIndex(u32 key1, u32 key2);

u32 func_ov016_020a2244(u32 source, u32 arg1, u32 unused, u32 arg2)
{
    u32 val1;
    u32 val2;
    ObjectState *obj;
    u32 cursor1;
    u32 cursor2;

    cursor1 = arg1;
    cursor2 = arg2;
    val1 = ScriptVm_ConsumeOperandInt(source, &cursor1);
    val2 = ScriptVm_ConsumeOperandInt(source, &cursor1);
    val1 = GetFieldEntryPoolAtIndex(val1);
    obj = GetEntryPoolObjectAtIndex(val1, val2);
    obj->flags |= 0x400000;
    return 1;
}
