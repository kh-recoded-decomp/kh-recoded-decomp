#include "nitro/types.h"

extern void func_02025438(u32 value);
extern void ScriptCmd_SetElemField_02025e18(void *scriptContext, u32 value);
extern void func_ov036_020bdc98(void *scriptContext, u32 value);

void ScriptCmd_ResetAndDispatch_020bdcc8(void *scriptContext, u32 value)
{
    func_02025438(0);
    ScriptCmd_SetElemField_02025e18(scriptContext, value);
    func_ov036_020bdc98(scriptContext, value);
}
