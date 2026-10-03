#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    u32 type;
    u32 value;
} ScriptOperand;

typedef struct {
    u32 id : 10;
    fx32 values[5];
} EntryParams;

extern s32 ScriptVm_ConsumeOperandInt_020a1de0(void *vm, ScriptOperand **cursor);
extern fx32 ScriptVm_ConsumeOperandFx32_020a1df4(void *vm, ScriptOperand **cursor);
extern unsigned int func_ov001_02087214(int index);
extern void func_ov016_020a6910(unsigned int entry, EntryParams *params);

BOOL ScriptCmd_ApplyEntryValues_020a2178(void *vm, ScriptOperand *operands)
{
    EntryParams params;
    ScriptOperand *cursor = operands;
    int index;

    index = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    params.id = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    params.values[0] = ScriptVm_ConsumeOperandFx32_020a1df4(vm, &cursor);
    params.values[1] = ScriptVm_ConsumeOperandFx32_020a1df4(vm, &cursor);
    params.values[2] = ScriptVm_ConsumeOperandFx32_020a1df4(vm, &cursor);
    params.values[3] = ScriptVm_ConsumeOperandFx32_020a1df4(vm, &cursor);
    params.values[4] = ScriptVm_ConsumeOperandFx32_020a1df4(vm, &cursor);
    func_ov016_020a6910(func_ov001_02087214(index), &params);
    return TRUE;
}
