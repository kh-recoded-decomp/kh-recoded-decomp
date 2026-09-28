#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    u8 **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern BOOL func_ov001_0208a424(u8 *actor, int mode);

int ScriptCmd_WaitActorReady_0208dce4(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int mode;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    mode = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    actorId = ScriptCmd_ReturnValue_02025960(context, actorId);
    if (func_ov001_0208a424(context->scene->actorObjects[actorId], mode) != 0) {
        return 1;
    }
    return 0;
}
