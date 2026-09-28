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
extern void ScriptCmd_SetElemField_02025e18(ScriptContext *context, ScriptOperand *operands);
extern void ScriptCmd_StartScreenBrightnessFade_0208d084(ScriptContext *context, ScriptOperand *operands, int screen);

int ScriptCmd_BeginBrightnessFade_0208d184(ScriptContext *context, ScriptOperand *operands)
{
    int screen;

    if (operands[2].type == 0) {
        screen = 2;
    } else {
        screen = ScriptVm_ReadOperandInt_02025de4(context, &operands[2]);
    }
    if (screen == 2) {
        ScriptCmd_StartScreenBrightnessFade_0208d084(context, operands, 0);
        ScriptCmd_StartScreenBrightnessFade_0208d084(context, operands, 1);
    } else {
        ScriptCmd_StartScreenBrightnessFade_0208d084(context, operands, screen);
    }
    if (ScriptVm_ReadOperandInt_02025de4(context, &operands[1]) == 0 || context->isSkipping != 0) {
        return 1;
    }
    ScriptCmd_SetElemField_02025e18(context, operands);
    return 0;
}
