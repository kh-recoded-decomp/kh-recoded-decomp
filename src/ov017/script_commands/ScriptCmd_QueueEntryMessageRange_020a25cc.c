#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov017_020a4204(void);
extern void *func_ov001_0208635c(void *table, int entryIndex);
extern void func_ov017_020a4030(void *target, void *source, int firstIndex, int lastIndex);

int ScriptCmd_QueueEntryMessageRange_020a25cc(void *vm, ScriptOperand *operands)
{
    int targetIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int sourceIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);
    int firstIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands + 2);
    int lastIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands + 3);
    void *manager = func_ov017_020a4204();
    void *target = func_ov001_0208635c(manager, targetIndex);
    void *source = func_ov001_0208635c(manager, sourceIndex);

    func_ov017_020a4030(target, source, (u16)firstIndex, (u16)lastIndex);
    return 1;
}
