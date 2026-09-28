#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *context, ScriptOperand *operand);
extern u32 SubScene9_Request_02066e50(u8 value);

BOOL ScriptCmd_RequestSubScene9_020655a8(void *context, ScriptOperand *operands)
{
    int waitForScene;

    waitForScene = ScriptVm_ReadOperandInt_02025de4(context, operands);
    SubScene9_Request_02066e50(0);
    return waitForScene == 0;
}
