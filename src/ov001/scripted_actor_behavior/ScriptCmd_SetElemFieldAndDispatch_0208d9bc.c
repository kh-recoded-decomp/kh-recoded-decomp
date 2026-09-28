#include "nitro/types.h"

extern void ScriptCmd_SetElemField_02025e18(void *scriptContext, u32 value);
extern int func_ov001_02071860(void);
extern int func_ov001_0208c6a4(void *scriptContext, u32 arg);
extern u32 func_ov001_0208d738(void *scriptContext, u32 value);

u32 ScriptCmd_SetElemFieldAndDispatch_0208d9bc(u8 *scriptContext, u32 value)
{
    int flag;
    u8 *sub;

    ScriptCmd_SetElemField_02025e18(scriptContext, value);
    flag = func_ov001_02071860();
    if (flag == 0) {
        return 0;
    }
    sub = *(u8 **)(scriptContext + 0x1c8);
    if (*(s32 *)(sub + 0x1cc) != 0) {
        flag = func_ov001_0208c6a4(scriptContext, *(u32 *)(sub + 0x50));
        if (flag == 1) {
            return func_ov001_0208d738(scriptContext, value);
        }
        return 0;
    }
    return func_ov001_0208d738(scriptContext, value);
}
