#include "nitro/types.h"

typedef struct EventRecord {
    u8 pad0[0x10];
    u16 actorId;
} EventRecord;

typedef struct EventSource {
    u8 pad0[0xa];
    u16 eventId;
} EventSource;

typedef struct ActiveContext {
    void *stage;
    EventSource *source;
    void *object;
} ActiveContext;

typedef struct ScriptContext {
    u8 pad0[0x2c];
    u16 resultValid;
    u8 pad2e[2];
    u32 result;
} ScriptContext;

extern ActiveContext data_ov021_020b56a4;
extern void *ResolveTaggedValueRef_020b0374(ScriptContext *context, void *value);
extern EventRecord *GetStageEventRecord_0209c0ec(u32 id);
extern u8 *GetStageActor_0209c040(int id);

int ScriptOp_GetEventActorValue_020b0b6c(ScriptContext *context, u8 *operands)
{
    EventSource *source;
    EventRecord *record;
    u8 *actor;

    ResolveTaggedValueRef_020b0374(context, operands + 8);
    source = data_ov021_020b56a4.source;
    if (source == NULL) {
        return 0;
    }
    context->result = 0;
    context->resultValid = 1;
    if (source->eventId == 0) {
        return 0;
    }
    record = GetStageEventRecord_0209c0ec(source->eventId);
    if (record == NULL) {
        return 0;
    }
    if (record->actorId == 0) {
        return 0;
    }
    actor = GetStageActor_0209c040((s16)record->actorId);
    if (actor == NULL) {
        return 0;
    }
    context->result = *(u16 *)(actor + 0x280);
    return 0;
}
