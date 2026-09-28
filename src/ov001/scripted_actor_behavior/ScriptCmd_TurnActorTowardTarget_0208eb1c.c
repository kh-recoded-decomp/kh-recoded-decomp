#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
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
extern ScriptOperand *ScriptVm_ResolveOperand_02025d08(ScriptContext *context, ScriptOperand *operand);
extern char *func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern int func_ov001_0208cf44(ScriptContext *context, ScriptOperand *target, int actorId);
extern void func_ov001_0208a73c(void *actorObject, int heading, char *turnAnimation, char *followAnimation);

int ScriptCmd_TurnActorTowardTarget_0208eb1c(ScriptContext *context, ScriptOperand *operands)
{
    int actorId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    ScriptOperand *target = ScriptVm_ResolveOperand_02025d08(context, operands + 1);
    char *turnAnimation = func_02025dac(context, operands + 2);
    char *followAnimation = func_02025dac(context, operands + 3);
    int heading;

    actorId = ScriptCmd_ReturnValue_02025960(context, actorId);
    heading = func_ov001_0208cf44(context, target, actorId);
    func_ov001_0208a73c(context->scene->actorObjects[actorId], heading, turnAnimation, followAnimation);
    return 1;
}
