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
extern void AppendPool1Batch_020a3fac(void *manager, int count, VecFx32 *points, int mode, fx32 speed, u16 *outIndices);
extern void FormatAndQueueMessage_020a4008(void *obj, const char *format, u32 flags, void *args);

int ScriptCmd_QueueEntryPathMessages_020a213c(void *vm, ScriptOperand *operands)
{
    VecFx32 points[256];
    u16 indices[256];
    int mode;
    int entryIndex;
    fx32 speed;
    BOOL enable;
    int count;
    int i;
    void *manager;
    void *entry;

    entryIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    enable = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1) ? TRUE : FALSE;
    mode = ScriptVm_ReadOperandInt_02025de4(vm, operands + 2);
    speed = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 3);
    operands += 4;
    count = ScriptVm_ReadOperandInt_02025de4(vm, operands++);
    for (i = 0; i < count; i++) {
        points[i].x = ScriptVm_ReadOperandFx32_02025df8(vm, operands++);
        points[i].y = ScriptVm_ReadOperandFx32_02025df8(vm, operands++);
        points[i].z = 0;
    }
    manager = func_ov017_020a4204();
    entry = func_ov001_0208635c(manager, entryIndex);
    AppendPool1Batch_020a3fac(manager, count, points, mode, speed, indices);
    for (i = 0; i < count; i++) {
        FormatAndQueueMessage_020a4008(entry, (const char *)1, enable, (void *)indices[i]);
    }
    return 1;
}
