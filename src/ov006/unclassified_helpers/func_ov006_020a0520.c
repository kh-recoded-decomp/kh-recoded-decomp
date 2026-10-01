#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

typedef struct {
    fx32 unk_00;
    fx32 unk_04;
    fx32 unk_08;
    fx32 unk_0c;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 unk_1a;
    u8 unk_1b;
    u8 unk_1c;
} ObjectGroupParams;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, ScriptOperand *operand);
extern void *func_ov006_020a0e3c(u16 kind, ObjectGroupParams *params);
extern void func_ov001_0207ee04(int groupIndex, void *group);

int func_ov006_020a0520(void *vm, ScriptOperand *operands)
{
    ObjectGroupParams params;
    int groupIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int kind = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);

    params.unk_12 = ScriptVm_ReadOperandInt_02025de4(vm, operands + 2);
    params.unk_14 = ScriptVm_ReadOperandInt_02025de4(vm, operands + 3);
    params.unk_16 = ScriptVm_ReadOperandInt_02025de4(vm, operands + 4);
    params.unk_1a = ScriptVm_ReadOperandInt_02025de4(vm, operands + 5);
    params.unk_00 = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 6);
    params.unk_04 = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 7);
    params.unk_08 = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 8);
    params.unk_0c = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 9);
    params.unk_1b = ScriptVm_ReadOperandInt_02025de4(vm, operands + 10);
    params.unk_1c = ScriptVm_ReadOperandInt_02025de4(vm, operands + 11);
    params.unk_10 = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 12);
    params.unk_18 = ScriptVm_ReadOperandInt_02025de4(vm, operands + 13);
    func_ov001_0207ee04(groupIndex, func_ov006_020a0e3c(kind, &params));
    return 1;
}
