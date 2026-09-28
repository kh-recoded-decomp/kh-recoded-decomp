#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *cmd);
extern void *func_ov009_020a0ad0(u16 elementCount);
extern void func_ov001_0207ee04(int slot, void *object);

int ScriptCmd_CreateObjectInSlot_020a0520(void *vm, void *cmd)
{
    int slot;
    u32 elementCount;

    slot = ScriptVm_ReadOperandInt_02025de4(vm, cmd);
    elementCount = ScriptVm_ReadOperandInt_02025de4(vm, (u8 *)cmd + 8);
    func_ov001_0207ee04(slot, func_ov009_020a0ad0(elementCount));
    return 1;
}
