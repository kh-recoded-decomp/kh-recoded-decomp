#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *operand);
extern void SaveSessionCheckpoint_02064364(u8 flags);

BOOL ScriptCmd_SaveCheckpoint_02065a38(void *vm, void *operand)
{
    u8 slot = ScriptVm_ReadOperandInt_02025de4(vm, operand);

    SaveSessionCheckpoint_02064364(slot | 0x80);
    return TRUE;
}
