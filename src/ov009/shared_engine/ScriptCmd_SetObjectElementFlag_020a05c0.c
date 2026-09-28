#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *cmd);
extern u32 func_ov001_0207f038(u32 slot, u32 elementIndex);
extern void SetFlagBit0x10At0x4e_020a0bf4(int element, BOOL enable);

int ScriptCmd_SetObjectElementFlag_020a05c0(void *vm, void *cmd)
{
    u32 slot;
    u32 elementIndex;
    BOOL enable;

    slot = ScriptVm_ReadOperandInt_02025de4(vm, cmd);
    elementIndex = ScriptVm_ReadOperandInt_02025de4(vm, (u8 *)cmd + 8);
    enable = ScriptVm_ReadOperandInt_02025de4(vm, (u8 *)cmd + 0x10);
    SetFlagBit0x10At0x4e_020a0bf4(func_ov001_0207f038(slot, elementIndex), enable);
    return 1;
}
