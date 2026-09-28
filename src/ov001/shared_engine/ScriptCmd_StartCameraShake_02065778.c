#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *context, ScriptOperand *operand);
extern void func_ov042_020bd74c(fx32 magnitude, fx32 duration);
extern void func_0204d8d0(u32 bank, u32 soundId);

int ScriptCmd_StartCameraShake_02065778(void *context, ScriptOperand *operands)
{
    fx32 magnitude;
    fx32 duration;

    magnitude = ScriptVm_ReadOperandFx32_02025df8(context, operands);
    duration = ScriptVm_ReadOperandFx32_02025df8(context, operands + 1);
    func_ov042_020bd74c(magnitude, duration);
    func_0204d8d0(0, 0x31);
    return 1;
}
