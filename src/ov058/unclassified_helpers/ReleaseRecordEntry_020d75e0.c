#include "nitro/types.h"

typedef struct {
    u32 initialized;
    void *record;
    u8 state[1];
} SharedRecordState;

extern void ReleaseResourceAndDetach_0202eee8(u8 *object);
extern void ReleaseSharedRecordState_020a9084(SharedRecordState *obj);

// Releases an object and its embedded record state
void ReleaseRecordEntry_020d75e0(u8 *object)
{
    ReleaseResourceAndDetach_0202eee8(object);
    ReleaseSharedRecordState_020a9084((SharedRecordState *)(object + 0x104));
}
