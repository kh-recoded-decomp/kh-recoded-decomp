#include "nitro/types.h"

#define OBJECT_KIND_OV018 6

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *cmd);
extern void *func_ov001_02086e90(int kind, int slot, int id, int arg);
extern void func_ov001_02086f90(int slot, void *object);

int ScriptCmd_CreateSlotObject_020a1de0(void *vm, void *cmd)
{
    int slot = ScriptVm_ReadOperandInt_02025de4(vm, cmd);
    int id = ScriptVm_ReadOperandInt_02025de4(vm, (u8 *)cmd + 8);
    void *object = func_ov001_02086e90(OBJECT_KIND_OV018, slot, id, 0);

    func_ov001_02086f90(slot, object);
    return 1;
}
