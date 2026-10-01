#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorTable {
    u8 pad_00[0x4C];
    void **actors;
} ActorTable;

typedef struct ScriptContext {
    u8 pad_000[0x1C8];
    ActorTable *actorTable;
    u8 pad_1CC[0x45C];
    s32 skip;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue_02025960(ScriptContext *context, int value);
extern int func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern void func_ov001_0208a36c(void *actor, int value);
extern void func_ov001_0208a3bc(void *actor, int state, int value);

BOOL ScriptCmd_ActorTimerOrAnim_0208e048(ScriptContext *context, ScriptOperand *operands)
{
    int handle = ScriptVm_ReadOperandInt_02025de4(context, operands);
    int index;
    int state;

    if (context->skip != 0) {
        return TRUE;
    }
    index = ScriptCmd_ReturnValue_02025960(context, handle);
    switch (operands[1].type) {
    case 1:
        func_ov001_0208a36c(context->actorTable->actors[index], ScriptVm_ReadOperandInt_02025de4(context, &operands[1]));
        break;
    case 2:
        state = func_02025dac(context, &operands[1]);
        func_ov001_0208a3bc(context->actorTable->actors[index], state, ScriptVm_ReadOperandInt_02025de4(context, &operands[2]));
        break;
    }
    return TRUE;
}
