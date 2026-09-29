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

extern char data_ov001_020a0230[];
extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern char *func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern int func_02023dbc(int dividend, int divisor);
extern void func_ov001_0208a73c(void *actorObject, int heading, char *turnAnimation, char *followAnimation);

int ScriptCmd_TurnActorToHeading_0208ea94(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int heading;
    char *turnAnimation;
    char *followAnimation;

    actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    heading = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    actorId = ScriptCmd_ReturnValue_02025960(context, actorId);
    heading = (u16)func_02023dbc(heading << 16, 360);
    if (operands[2].type == 2 || operands[2].type == 0x40) {
        turnAnimation = func_02025dac(context, operands + 2);
    } else {
        turnAnimation = data_ov001_020a0230;
    }
    if (operands[3].type == 2 || operands[3].type == 0x40) {
        followAnimation = func_02025dac(context, operands + 3);
    } else {
        followAnimation = data_ov001_020a0230;
    }
    func_ov001_0208a73c(context->scene->actorObjects[actorId], heading, turnAnimation, followAnimation);
    return 1;
}
