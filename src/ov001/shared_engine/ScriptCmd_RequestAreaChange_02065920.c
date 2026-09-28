#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext {
    u8 pad_000[0x1cc];
    s32 waitArmed;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern void func_ov001_0206317c(int areaId, int roomId, int entranceId, int transitionFlags);

int ScriptCmd_RequestAreaChange_02065920(ScriptContext *context, ScriptOperand *operands)
{
    int areaId;
    int entranceId;

    areaId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    entranceId = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    func_ov001_0206317c(areaId, 0, entranceId, -1);
    context->waitArmed = 0;
    return 3;
}
