#include "nitro/types.h"

typedef struct ScriptObj {
    u8 pad_00[0x628];
    s32 flag;
} ScriptObj;

extern int ScriptVm_ReadOperandInt_02025de4(void *obj, void *cmd);
extern void func_0204d8d0(u32 param1, u32 param2);

int func_02026740(ScriptObj *obj, void *cmd)
{
    int a = ScriptVm_ReadOperandInt_02025de4(obj, cmd);
    int b = ScriptVm_ReadOperandInt_02025de4(obj, (u8 *)cmd + 8);
    if (obj->flag != 0) {
        return 1;
    }
    func_0204d8d0(a, b);
    return 1;
}
