#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad;
    s32 value;
} ScriptOperand;

extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *scriptContext, ScriptOperand *operand);
extern int ScriptVm_ReadOperandInt_02025de4(void *scriptContext, ScriptOperand *operand);
extern ScriptOperand *ScriptVm_ResolveOperand_02025d08(void *scriptContext, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(void *scriptContext, int actorId);
extern void *func_02025dac(void *scriptContext, ScriptOperand *operand);
extern u8 *FindWorldCollisionEntry_02036548(void *name);
extern void VEC_Add_01ff9e0c(const VecFx32 *left, const VecFx32 *right, VecFx32 *result);
extern void SetCameraTargetParams_0208ba8c(int mode, int distance, const VecFx32 *focus, const VecFx32 *offset);
extern const VecFx32 data_02053438;

int ScriptCmd_SetCameraTarget_0208d408(void *scriptContext, ScriptOperand *operands) {
    VecFx32 zero = data_02053438;
    VecFx32 focus = zero;
    VecFx32 angles = zero;
    fx32 distance;
    int mode;
    ScriptOperand *operand;
    int degrees;
    u8 *entry;

    distance = ScriptVm_ReadOperandFx32_02025df8(scriptContext, operands + 4);
    mode = 0;
    focus.x = ScriptVm_ReadOperandFx32_02025df8(scriptContext, operands + 1);
    focus.y = ScriptVm_ReadOperandFx32_02025df8(scriptContext, operands + 2);
    focus.z = ScriptVm_ReadOperandFx32_02025df8(scriptContext, operands + 3);
    operand = ScriptVm_ResolveOperand_02025d08(scriptContext, operands + 5);
    if (operand->type == 1) {
        angles.x = ScriptVm_ReadOperandInt_02025de4(scriptContext, operand) * 0xb6;
    }
    operand = ScriptVm_ResolveOperand_02025d08(scriptContext, operands + 6);
    if (operand->type == 1) {
        degrees = ScriptVm_ReadOperandInt_02025de4(scriptContext, operand);
        if (degrees > 360) {
            degrees = -(degrees - 360);
        }
        angles.y = degrees * 0xb6;
    }
    operand = ScriptVm_ResolveOperand_02025d08(scriptContext, operands);
    switch (operand->type) {
    case 1:
        if (operand->value != -1) {
            mode = ScriptCmd_ReturnValue_02025960(scriptContext, operand->value);
        } else {
            mode = -1;
        }
        break;
    case 2:
        entry = FindWorldCollisionEntry_02036548(func_02025dac(scriptContext, operand));
        mode = -1;
        VEC_Add_01ff9e0c(&focus, (VecFx32 *)(entry + 8), &focus);
        break;
    }
    SetCameraTargetParams_0208ba8c(mode, distance, &focus, &angles);
    return 1;
}
