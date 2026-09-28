#include "nitro/types.h"

typedef struct ScriptObj {
    u8 pad_00[0x628];
    s32 flag;
} ScriptObj;

extern int ScriptVm_ReadOperandInt_02025de4(void *obj, void *cmd);
extern s32 func_ov001_02063a38(void);
extern void func_ov036_020bd980(s32 a, s32 b);
extern void func_0204d7f4(int new_value);
extern s8 data_02055e00;

int func_02026620(ScriptObj *obj, void *cmd)
{
    int a = ScriptVm_ReadOperandInt_02025de4(obj, cmd);
    if (func_ov001_02063a38() == 8) {
        func_ov036_020bd980(-1, a);
        if (obj->flag != 0) {
            return 1;
        }
    }
    data_02055e00 = -1;
    func_0204d7f4(a);
    return 1;
}
