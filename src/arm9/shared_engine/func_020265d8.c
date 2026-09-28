#include "nitro/types.h"

typedef struct ScriptObj {
    u8 pad_00[0x628];
    s32 flag;
} ScriptObj;

extern int ScriptVm_ReadOperandInt_02025de4(void *obj, void *cmd);
extern s32 func_ov001_02063a38(void);
extern void func_ov036_020bd980(s32 a, s32 b);
extern int func_020262a4(void);
extern int SetSelectionIfChanged_0204d73c(int selection);
extern s8 data_02055e00;

int func_020265d8(ScriptObj *obj, void *cmd)
{
    int a = ScriptVm_ReadOperandInt_02025de4(obj, cmd);
    if (func_ov001_02063a38() == 8) {
        func_ov036_020bd980(a, 0);
        if (obj->flag != 0) {
            return 1;
        }
    }
    if (func_020262a4() != 0) {
        data_02055e00 = a;
        SetSelectionIfChanged_0204d73c((u8)a);
    }
    return 1;
}
