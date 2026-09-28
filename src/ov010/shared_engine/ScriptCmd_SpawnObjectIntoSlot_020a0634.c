#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *cmd);
extern void *func_ov010_020a0bd4(u16 param);
extern void func_ov001_0207ee04(int slotIndex, void *object);

int ScriptCmd_SpawnObjectIntoSlot_020a0634(void *vm, void *cmd)
{
    int slotIndex = ScriptVm_ReadOperandInt_02025de4(vm, cmd);
    int param = ScriptVm_ReadOperandInt_02025de4(vm, (u8 *)cmd + 8);
    void *object = func_ov010_020a0bd4((u16)param);
    func_ov001_0207ee04(slotIndex, object);
    return 1;
}
