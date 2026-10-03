#include "nitro/types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x2c];
    u16 resultTag;
    u16 pad_2e;
    s32 resultValue;
} ScriptContext;

typedef struct {
    u8 pad_00[8];
    TaggedValue operand;
} ScriptCommand;

typedef struct StageObject {
    u8 pad_000[0x280];
    u16 typeId;
} StageObject;

typedef struct ScriptGlobals {
    u8 pad_00[8];
    StageObject *activeObject;
} ScriptGlobals;

extern ScriptGlobals data_ov021_020b56a4;
extern TaggedValue *ResolveTaggedValueRef_020b0374(ScriptContext *context, TaggedValue *value);
extern StageObject *FindStageObjectById_0209c290(u16 id);

int ScriptOp_GetObjectTypeId_020b0e20(ScriptContext *context, ScriptCommand *command)
{
    TaggedValue *idValue = ResolveTaggedValueRef_020b0374(context, &command->operand);
    StageObject *object = data_ov021_020b56a4.activeObject;
    StageObject *found;

    if (object == NULL) {
        return 0;
    }
    if (idValue->value != 0) {
        found = FindStageObjectById_0209c290(idValue->value);
        if (found != NULL) {
            object = found;
        }
    }
    context->resultTag = 1;
    context->resultValue = object->typeId;
    return 0;
}
