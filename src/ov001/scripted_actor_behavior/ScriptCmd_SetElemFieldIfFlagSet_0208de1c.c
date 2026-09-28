#include "nitro/types.h"

extern void func_ov001_0208dd24(void *scriptContext, void *obj);
extern void ScriptCmd_SetElemField_02025e18(void *scriptContext, u32 value);

u32 ScriptCmd_SetElemFieldIfFlagSet_0208de1c(void *scriptContext, u8 *obj)
{
    func_ov001_0208dd24(scriptContext, obj);
    if (*(s32 *)(obj + 0x24) == 0) {
        return 1;
    }
    ScriptCmd_SetElemField_02025e18(scriptContext, (u32)obj);
    return 0;
}
