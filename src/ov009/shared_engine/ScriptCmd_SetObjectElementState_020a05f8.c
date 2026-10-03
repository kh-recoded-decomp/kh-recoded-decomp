#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *cmd);
extern int func_ov001_0207f038(int slot, int elementIndex);
extern void PXI_Init_020a0c1c(int element, BOOL enable);

int ScriptCmd_SetObjectElementState_020a05f8(void *vm, void *cmd)
{
    int slot;
    int elementIndex;
    BOOL enable;

    slot = ScriptVm_ReadOperandInt_02025de4(vm, cmd);
    elementIndex = ScriptVm_ReadOperandInt_02025de4(vm, (u8 *)cmd + 8);
    enable = ScriptVm_ReadOperandInt_02025de4(vm, (u8 *)cmd + 0x10) != 0;
    PXI_Init_020a0c1c(func_ov001_0207f038(slot, elementIndex), enable);
    return 1;
}
