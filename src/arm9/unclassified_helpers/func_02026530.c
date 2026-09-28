#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x628];
    s32 field_628;
} ScriptObj_02026530;

extern void ScriptCmd_SetElemField_02025e18(ScriptObj_02026530 *obj, u32 value);

u32 func_02026530(ScriptObj_02026530 *obj, u32 mode)
{
    u32 next;

    if (obj->field_628 != 0) {
        return 1;
    }
    next = mode - 1;
    if (next == 0) {
        return 1;
    }
    ScriptCmd_SetElemField_02025e18(obj, next);
    return 0;
}
