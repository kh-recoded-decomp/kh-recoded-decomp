#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 payload;
} ScriptOperand;

extern s32 ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void func_ov001_020689b0(s32 count, s32 *entryIds);

BOOL ScriptCmd_ShuffleEntryPositions_020a0520(void *vm, ScriptOperand *operands)
{
    s32 entryIds[128];
    s32 count;
    s32 i;
    ScriptOperand *first = operands;

    operands++;
    count = ScriptVm_ReadOperandInt_02025de4(vm, first);
    for (i = 0; i < count; i++) {
        s32 entryId = ScriptVm_ReadOperandInt_02025de4(vm, operands);
        operands++;
        entryIds[i] = entryId;
    }
    func_ov001_020689b0(count, entryIds);
    return TRUE;
}
