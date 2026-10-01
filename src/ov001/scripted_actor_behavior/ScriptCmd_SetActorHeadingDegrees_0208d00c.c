#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    void **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern int func_02023dbc(int dividend, int divisor);
extern void func_ov001_0208a328(void *actor, u32 targetHeading);

int ScriptCmd_SetActorHeadingDegrees_0208d00c(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int degrees;
    u16 heading;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    degrees = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    actorId = ScriptCmd_ReturnValue_02025960(context, actorId);
    heading = func_02023dbc(degrees << 16, 360);
    func_ov001_0208a328(context->scene->actorObjects[actorId], heading);
    return 1;
}
