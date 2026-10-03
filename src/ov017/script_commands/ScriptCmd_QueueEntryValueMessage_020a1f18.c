#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, ScriptOperand *operand);
extern void *func_ov017_020a4204(void);
extern void *func_ov001_0208635c(void *table, int entryIndex);
extern void *AppendPool0Value_020a3ec4(void *manager, int value);
extern void FormatAndQueueMessage_020a4008(void *obj, const char *format, u32 flags, void *args);

int ScriptCmd_QueueEntryValueMessage_020a1f18(void *vm, ScriptOperand *operands)
{
    int entryIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    BOOL enable = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1) != 0;
    fx32 value = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 2);
    void *manager = func_ov017_020a4204();
    void *entry = func_ov001_0208635c(manager, entryIndex);

    FormatAndQueueMessage_020a4008(entry, NULL, enable, AppendPool0Value_020a3ec4(manager, value));
    return 1;
}
