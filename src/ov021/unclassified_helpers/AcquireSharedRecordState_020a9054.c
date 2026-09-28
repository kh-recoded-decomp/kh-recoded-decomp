#include "nitro/types.h"

extern void *RetainOrInitializeSharedRecord_0202c80c(s32 key, s32 context);
extern void func_0202ea78(void *state, u32 initArg, s32 recordArg, u32 context);

typedef struct {
    u32 initialized;
    void *record;
    u8 state[1];
} SharedRecordState;

void AcquireSharedRecordState_020a9054(SharedRecordState *obj, s32 key, u32 initArg, u32 context)
{
    if (obj->initialized == 0) {
        void *record = RetainOrInitializeSharedRecord_0202c80c(key, context);
        obj->record = record;
        func_0202ea78(obj->state, initArg, *(s32 *)((u8 *)record + 0xc), context);
        obj->initialized = 1;
    }
}
