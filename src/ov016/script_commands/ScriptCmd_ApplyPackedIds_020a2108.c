#include "nitro/types.h"

typedef struct ScriptOperand {
    u32 type;
    u32 value;
} ScriptOperand;

typedef struct {
    u32 kind : 6;
    u32 first : 10;
    u32 second : 10;
} PackedIds;

extern s32 ScriptVm_ConsumeOperandInt_020a1de0(void *vm, ScriptOperand **cursor);
extern unsigned int func_ov001_02087214(int index);
extern void func_ov016_020a68d8(unsigned int entry, PackedIds *ids);

BOOL ScriptCmd_ApplyPackedIds_020a2108(void *vm, ScriptOperand *operands)
{
    ScriptOperand *cursor = operands;
    PackedIds ids;
    int index;

    index = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    ids.kind = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    ids.first = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    ids.second = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    func_ov016_020a68d8(func_ov001_02087214(index), &ids);
    return TRUE;
}
