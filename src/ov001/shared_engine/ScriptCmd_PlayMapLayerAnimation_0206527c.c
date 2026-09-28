#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *context, ScriptOperand *operand);
extern void func_ov001_02067c48(int layerIndex, int animIndex, fx32 speed, BOOL loop);

int ScriptCmd_PlayMapLayerAnimation_0206527c(void *context, ScriptOperand *operands)
{
    int layerIndex;
    int animIndex;
    fx32 speed;
    int loop;

    layerIndex = ScriptVm_ReadOperandInt_02025de4(context, operands);
    animIndex = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    speed = ScriptVm_ReadOperandFx32_02025df8(context, operands + 2);
    loop = ScriptVm_ReadOperandInt_02025de4(context, operands + 3);
    func_ov001_02067c48(layerIndex, animIndex, speed, loop != 0);
    return 1;
}
