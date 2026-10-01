#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(ScriptContext *context, ScriptOperand *operand);
extern int func_02023dbc(int dividend, int divisor);
extern void StoreSessionSpawnPoint_02063524(int index, const VecFx32 *position, u16 angle);

BOOL ScriptCmd_SetSpawnPoint_020652c0(ScriptContext *context, ScriptOperand *operands)
{
    VecFx32 position;
    int degrees;
    int index;

    position.x = ScriptVm_ReadOperandFx32_02025df8(context, &operands[0]);
    position.y = ScriptVm_ReadOperandFx32_02025df8(context, &operands[1]);
    position.z = ScriptVm_ReadOperandFx32_02025df8(context, &operands[2]);
    degrees = ScriptVm_ReadOperandInt_02025de4(context, &operands[3]);
    index = ScriptVm_ReadOperandInt_02025de4(context, &operands[4]);
    StoreSessionSpawnPoint_02063524(index, &position, func_02023dbc(degrees << 16, 360));
    return TRUE;
}
