#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *operand);
extern u32 func_ov001_0207b320(int mode);
extern u32 func_ov001_0207b3cc(void);
extern void ScriptCmd_SetElemField_02025e18(void *vm, void *cmd);

BOOL ScriptCmd_WaitMenuState_0208ef64(void *vm, void *cmd)
{
    switch (ScriptVm_ReadOperandInt_02025de4(vm, cmd)) {
    case 0:
        if (func_ov001_0207b320(0)) {
            return TRUE;
        }
        break;
    case 1:
        if (func_ov001_0207b3cc() == 2 || func_ov001_0207b320(2)) {
            return TRUE;
        }
        break;
    default:
        return TRUE;
    }
    ScriptCmd_SetElemField_02025e18(vm, cmd);
    return FALSE;
}
