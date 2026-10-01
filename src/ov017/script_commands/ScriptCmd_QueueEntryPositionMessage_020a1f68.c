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
extern u32 func_ov017_020a4234(void *manager);
extern void *func_ov001_0208635c(void *table, int entryIndex);
extern void *func_ov017_020a3eec(void *manager, VecFx32 *position, u32 managerValue, fx32 speed, int duration);
extern void FormatAndQueueMessage_020a4008(void *obj, const char *format, u32 flags, void *args);

int ScriptCmd_QueueEntryPositionMessage_020a1f68(void *vm, ScriptOperand *operands)
{
    void *manager = func_ov017_020a4204();
    int entryIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    BOOL enable = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1) != 0;
    VecFx32 position;
    u32 managerValue;
    fx32 speed;
    int duration;
    void *entry;

    position.x = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 2);
    position.y = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 3);
    position.z = 0;
    managerValue = func_ov017_020a4234(manager);
    speed = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 4);
    duration = ScriptVm_ReadOperandInt_02025de4(vm, operands + 5);
    entry = func_ov001_0208635c(manager, entryIndex);

    FormatAndQueueMessage_020a4008(entry, (const char *)1, enable, func_ov017_020a3eec(manager, &position, managerValue, speed, duration));
    return 1;
}
