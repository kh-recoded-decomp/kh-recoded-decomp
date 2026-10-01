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
extern void func_ov042_020bd474(VecFx32 *direction, fx32 angle);
extern u32 func_ov030_020bb354(void);
extern void *func_ov017_020a3f1c(void *manager, fx32 x, fx32 y, VecFx32 *direction, u32 context, fx32 rotation, int duration);
extern s64 LongMul_02023d9c(s64 a, s64 b);
extern s64 LongDiv_02023ba4(s64 numerator, s64 denominator);
extern void FormatAndQueueMessage_020a4008(void *obj, const char *format, u32 flags, void *args);

int ScriptCmd_QueueEntryRotationMessage_020a1ff8(void *vm, ScriptOperand *operands)
{
    int entryIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    BOOL enable = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1) != 0;
    fx32 x = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 2);
    fx32 y = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 3);
    fx32 angle = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 4);
    fx32 rotation = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 5);
    int duration = ScriptVm_ReadOperandInt_02025de4(vm, operands + 6);
    void *manager = func_ov017_020a4204();
    void *entry = func_ov001_0208635c(manager, entryIndex);
    VecFx32 direction;

    func_ov042_020bd474(&direction, angle);
    FormatAndQueueMessage_020a4008(entry, (const char *)2, enable,
        func_ov017_020a3f1c(manager, x, y, &direction, func_ov030_020bb354(),
            (fx32)LongDiv_02023ba4(LongMul_02023d9c(rotation, 0x3244), 0xb4000), duration));
    return 1;
}
