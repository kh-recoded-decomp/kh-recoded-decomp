#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext {
    u8 pad_000[0x628];
    s32 isSkipping;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern void func_ov036_020bd2c8(int entityId, int startX, int startY, int targetX, int targetY, int duration);

int ScriptCmd_PlaceEntityAndMove_020be564(ScriptContext *context, ScriptOperand *operands)
{
    int entityId = ScriptVm_ReadOperandInt_02025de4(context, &operands[0]);
    int startX = ScriptVm_ReadOperandInt_02025de4(context, &operands[1]);
    int startY = ScriptVm_ReadOperandInt_02025de4(context, &operands[2]);
    int targetX = ScriptVm_ReadOperandInt_02025de4(context, &operands[3]);
    int targetY = ScriptVm_ReadOperandInt_02025de4(context, &operands[4]);
    int duration = ScriptVm_ReadOperandInt_02025de4(context, &operands[5]);

    if (context->isSkipping != 0) {
        return 1;
    }
    func_ov036_020bd2c8(entityId, startX, startY, targetX, targetY, duration);
    return 1;
}
