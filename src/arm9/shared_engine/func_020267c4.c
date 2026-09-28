#include "nitro/types.h"

typedef struct ScriptObj {
    u8 pad_00[0x628];
    s32 flag;
} ScriptObj;

extern int ScriptVm_ReadOperandInt_02025de4(void *obj, void *cmd);
extern BOOL IsSoundStreamActive_0204ded4(int handleIndex);
extern void func_0204dd4c(int param1, int param2);

int func_020267c4(ScriptObj *obj, void *cmd)
{
    int a = ScriptVm_ReadOperandInt_02025de4(obj, cmd);
    if (obj->flag != 0) {
        return 1;
    }
    if (IsSoundStreamActive_0204ded4(0) != 0) {
        return 0;
    }
    func_0204dd4c(0, a);
    return 1;
}
