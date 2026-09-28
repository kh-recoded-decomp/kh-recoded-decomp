#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov001_02087214(int tableIndex);
extern void *func_ov001_0208635c(void *table, int entryIndex);
extern void func_ov017_020a405c(void *entry);

int ScriptCmd_ResetEntry_020a2218(void *vm, ScriptOperand *operands)
{
    int tableIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int entryIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);
    void *entry = func_ov001_0208635c(func_ov001_02087214(tableIndex), entryIndex);

    func_ov017_020a405c(entry);
    return 1;
}
