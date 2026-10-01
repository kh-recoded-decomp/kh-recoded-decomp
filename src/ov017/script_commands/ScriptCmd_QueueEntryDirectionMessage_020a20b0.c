#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, ScriptOperand *operand);
extern VecFx32 func_ov042_020bd474(fx32 angle);
extern void func_0204a5e4(VecFx32 *vec, fx32 scale);
extern void *func_ov017_020a4204(void);
extern void *func_ov001_0208635c(void *table, int entryIndex);
extern void *func_ov017_020a3f58(void *manager, VecFx32 *vec);
extern void FormatAndQueueMessage_020a4008(void *obj, const char *format, u32 flags, void *args);

static inline VecFx32 ScaleVec(VecFx32 vec, fx32 scale)
{
    func_0204a5e4(&vec, scale);
    return vec;
}

int ScriptCmd_QueueEntryDirectionMessage_020a20b0(void *vm, ScriptOperand *operands)
{
    int entryIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    BOOL enable = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1) != 0;
    fx32 angle = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 2);
    fx32 length = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 3);
    VecFx32 direction = ScaleVec(func_ov042_020bd474(angle), length);
    void *manager = func_ov017_020a4204();
    void *entry = func_ov001_0208635c(manager, entryIndex);

    FormatAndQueueMessage_020a4008(entry, (const char *)3, enable, func_ov017_020a3f58(manager, &direction));
    return 1;
}
