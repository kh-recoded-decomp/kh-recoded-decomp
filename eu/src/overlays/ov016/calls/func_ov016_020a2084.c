#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x50];
    u32 value1;
    u32 value2;
    u32 value3;
} ObjectState;

extern u32 ScriptVm_ConsumeOperandFx32(u32 source, u32 *cursor);

void func_ov016_020a2084(ObjectState *obj, u32 source, u32 *cursor)
{
    obj->value1 = ScriptVm_ConsumeOperandFx32(source, cursor);
    obj->value2 = ScriptVm_ConsumeOperandFx32(source, cursor);
    obj->value3 = ScriptVm_ConsumeOperandFx32(source, cursor);
}
