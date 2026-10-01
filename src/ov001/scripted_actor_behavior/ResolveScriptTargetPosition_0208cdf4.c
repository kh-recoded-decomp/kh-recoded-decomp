#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorNode {
    u8 pad_00[0xa8];
    VecFx32 position;
} ActorNode;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(ScriptContext *context, ScriptOperand *operand);
extern ScriptOperand *ScriptVm_ResolveOperand_02025d08(ScriptContext *context, ScriptOperand *operand);
extern int func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern int func_02023dbc(int dividend, int divisor);
extern ActorNode *func_02036240(u16 actorId);
extern int func_02036564(int location, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern const s16 data_0205356c[];

void ResolveScriptTargetPosition_0208cdf4(ScriptContext *context, ScriptOperand *operands, int actorId, VecFx32 *out)
{
    VecFx32 offset;
    VecFx32 direction;
    fx32 distance;
    ScriptOperand *location;
    int angleIndex;

    distance = ScriptVm_ReadOperandFx32_02025df8(context, operands + 6);
    location = ScriptVm_ResolveOperand_02025d08(context, operands + 1);
    offset.x = ScriptVm_ReadOperandFx32_02025df8(context, operands + 2);
    offset.y = ScriptVm_ReadOperandFx32_02025df8(context, operands + 3);
    offset.z = ScriptVm_ReadOperandFx32_02025df8(context, operands + 4);
    switch (location->type) {
    case 2:
        func_02036564(func_02025dac(context, location), out);
        VEC_Add_01ff9e0c(out, &offset, out);
        break;
    case 1:
        angleIndex = (u16)func_02023dbc(ScriptVm_ReadOperandInt_02025de4(context, location) << 16, 360) >> 4;
        direction.x = data_0205356c[angleIndex];
        direction.y = 0;
        direction.z = data_0205356c[(0x400 - angleIndex) & 0xfff];
        VEC_MultAdd_01ffa09c(distance, &direction, &func_02036240(actorId)->position, out);
        break;
    case 0:
        *out = offset;
        break;
    }
}
