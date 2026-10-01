#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *operand);
extern void func_ov001_02069274(int eventId, BOOL enable, int mode, int *params);

BOOL ScriptCmd_ConfigureEventSlot_02065ac4(void *vm, u8 *operands)
{
    int enable = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int eventId = ScriptVm_ReadOperandInt_02025de4(vm, operands + 8);
    int params[5];

    params[0] = ScriptVm_ReadOperandInt_02025de4(vm, operands + 0x10);
    params[1] = ScriptVm_ReadOperandInt_02025de4(vm, operands + 0x18);
    params[2] = ScriptVm_ReadOperandInt_02025de4(vm, operands + 0x20);
    params[3] = ScriptVm_ReadOperandInt_02025de4(vm, operands + 0x28);
    params[4] = ScriptVm_ReadOperandInt_02025de4(vm, operands + 0x30);
    func_ov001_02069274(eventId, enable != 0, 7, params);
    return TRUE;
}
