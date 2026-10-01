#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov017_020a4204(void);
extern void *func_ov001_0208635c(void *table, int entryIndex);
extern void *func_ov017_020a3f84(void *manager);
extern void FormatAndQueueMessage_020a4008(void *obj, const char *format, u32 flags, void *args);

int ScriptCmd_QueueEntryMessage_020a2244(void *vm, ScriptOperand *operands)
{
    int entryIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    BOOL enable = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1) != 0;
    void *manager = func_ov017_020a4204();
    void *entry = func_ov001_0208635c(manager, entryIndex);

    FormatAndQueueMessage_020a4008(entry, (const char *)4, enable, func_ov017_020a3f84(manager));
    return 1;
}
