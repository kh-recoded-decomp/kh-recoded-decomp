#include "nitro/types.h"

extern void func_0202eaf4(void *state);
extern void func_0202c8a8(void *record);

typedef struct {
    u32 initialized;
    void *record;
    u8 state[1];
} SharedRecordState;

void ReleaseSharedRecordState_020a9084(SharedRecordState *obj)
{
    if (obj->initialized != 0) {
        func_0202eaf4(obj->state);
        func_0202c8a8(obj->record);
        obj->initialized = 0;
    }
}
