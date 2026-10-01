#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    u32 type;
    int raw;
} ScriptOperand;

typedef struct MotionParams {
    int startMode;
    VecFx32 start;
    int endMode;
    VecFx32 end;
    int duration;
} MotionParams;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, ScriptOperand *operand);
extern void func_ov001_02069274(int id, BOOL repeat, int unused, MotionParams *params);

int ScriptOp_StartFieldMotion_02064f08(void *vm, ScriptOperand *operands)
{
    int repeat = ScriptVm_ReadOperandInt_02025de4(vm, &operands[0]);
    int id = ScriptVm_ReadOperandInt_02025de4(vm, &operands[1]);
    MotionParams params;

    params.startMode = ScriptVm_ReadOperandInt_02025de4(vm, &operands[2]);
    params.start.x = ScriptVm_ReadOperandFx32_02025df8(vm, &operands[3]);
    params.start.y = ScriptVm_ReadOperandFx32_02025df8(vm, &operands[4]);
    params.start.z = ScriptVm_ReadOperandFx32_02025df8(vm, &operands[5]);
    params.endMode = ScriptVm_ReadOperandInt_02025de4(vm, &operands[6]);
    params.end.x = ScriptVm_ReadOperandFx32_02025df8(vm, &operands[7]);
    params.end.y = ScriptVm_ReadOperandFx32_02025df8(vm, &operands[8]);
    params.end.z = ScriptVm_ReadOperandFx32_02025df8(vm, &operands[9]);
    params.duration = ScriptVm_ReadOperandInt_02025de4(vm, &operands[10]);
    func_ov001_02069274(id, repeat != 0, 0, &params);
    return 1;
}
