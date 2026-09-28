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
extern void func_ov036_020bd500(int screen, BOOL useWhiteClearColor);

int ScriptCmd_ResetScreenLayer_020be0c4(ScriptContext *context, ScriptOperand *operands)
{
    int screen = ScriptVm_ReadOperandInt_02025de4(context, &operands[0]);
    int useWhiteClearColor = ScriptVm_ReadOperandInt_02025de4(context, &operands[1]);

    if (context->isSkipping != 0) {
        return 1;
    }
    func_ov036_020bd500(screen, useWhiteClearColor);
    return 1;
}
