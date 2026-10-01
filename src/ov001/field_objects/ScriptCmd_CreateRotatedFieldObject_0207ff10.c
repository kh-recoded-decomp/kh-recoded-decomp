#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    u32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(ScriptContext *context, ScriptOperand *operand);
extern void *func_ov001_0207f028(int index);
extern void *func_ov001_020819b4(void *objectClass, u16 slotIndex, u16 saveBitOffset, u8 saveBitCount,
                                 const VecFx32 *position, u16 angle, s16 param);

BOOL ScriptCmd_CreateRotatedFieldObject_0207ff10(ScriptContext *context, ScriptOperand *operands)
{
    VecFx32 position;
    int classIndex = ScriptVm_ReadOperandInt_02025de4(context, &operands[0]);
    int slotIndex = ScriptVm_ReadOperandInt_02025de4(context, &operands[1]);
    u32 saveBits = operands[2].value;
    int degrees;
    fx32 param;

    position.x = ScriptVm_ReadOperandFx32_02025df8(context, &operands[3]);
    position.y = ScriptVm_ReadOperandFx32_02025df8(context, &operands[4]);
    position.z = ScriptVm_ReadOperandFx32_02025df8(context, &operands[5]);
    degrees = ScriptVm_ReadOperandInt_02025de4(context, &operands[6]);
    param = ScriptVm_ReadOperandFx32_02025df8(context, &operands[7]);
    func_ov001_020819b4(func_ov001_0207f028(classIndex), slotIndex, saveBits & 0xFFFF, (u16)(saveBits >> 16),
                        &position, (degrees << 16) / 360, param);
    return TRUE;
}
