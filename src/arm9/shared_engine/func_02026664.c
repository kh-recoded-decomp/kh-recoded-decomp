#include "nitro/types.h"

typedef struct ScriptObj {
    u8 pad_00[0x628];
    s32 flag;
} ScriptObj;

extern int ScriptVm_ReadOperandInt_02025de4(void *obj, void *cmd);
extern s32 func_ov001_02063a38(void);
extern void func_ov036_020bd980(s32 a, s32 b);
extern int func_020262a4(void);
extern int func_0204d8b8(int arg0, int arg1);
extern s8 data_02055e00;

int func_02026664(ScriptObj *obj, void *cmd)
{
    int a = ScriptVm_ReadOperandInt_02025de4(obj, cmd);
    int b = ScriptVm_ReadOperandInt_02025de4(obj, (u8 *)cmd + 8);
    if (func_ov001_02063a38() == 8) {
        func_ov036_020bd980(a, b);
        if (obj->flag != 0) {
            return 1;
        }
    }
    if (func_020262a4() != 0) {
        func_0204d8b8((u8)a, b);
        data_02055e00 = a;
    }
    return 1;
}
