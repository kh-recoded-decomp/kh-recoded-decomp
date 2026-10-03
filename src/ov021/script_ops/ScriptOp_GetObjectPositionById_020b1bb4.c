#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x34];
    VecFx32 vector;
} ScriptContext;

typedef struct {
    u8 pad_00[8];
    TaggedValue operand;
} ScriptCommand;

typedef struct {
    u8 pad_000[0x2c0];
    VecFx32 position;
} ScriptObject;

extern TaggedValue *ResolveTaggedValueRef_020b0374(ScriptContext *context, TaggedValue *value);
extern s32 TaggedValueToInt_020b0398(TaggedValue *tagged);
extern ScriptObject *func_ov021_020b02b8(ScriptContext *context, s32 id);

int ScriptOp_GetObjectPositionById_020b1bb4(ScriptContext *context, ScriptCommand *command)
{
    ScriptObject *object = func_ov021_020b02b8(context, TaggedValueToInt_020b0398(ResolveTaggedValueRef_020b0374(context, &command->operand)));
    if (object != NULL) {
        context->vector = object->position;
    }
    return 0;
}
