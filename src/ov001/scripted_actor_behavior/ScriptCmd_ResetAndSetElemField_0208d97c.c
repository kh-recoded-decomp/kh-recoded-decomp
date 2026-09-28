#include "nitro/types.h"

extern void func_01ff86fc(u32 data, void *dst, u32 size);
extern void ScriptCmd_SetElemField_02025e18(void *scriptContext, u32 value);
extern int func_ov001_02071860(void);
extern u32 func_ov001_0208d738(void *scriptContext, u32 value);

u32 ScriptCmd_ResetAndSetElemField_0208d97c(u8 *scriptContext, u32 value)
{
    u32 result;
    int flag;

    *(u32 *)(*(u8 **)(scriptContext + 0x1c8) + 0x54) = 0xffffffff;
    result = 0;
    func_01ff86fc(0, *(u8 **)(scriptContext + 0x1c8) + 200, 0x100);
    ScriptCmd_SetElemField_02025e18(scriptContext, value);
    flag = func_ov001_02071860();
    if (flag != 0) {
        result = func_ov001_0208d738(scriptContext, value);
    }
    return result;
}
