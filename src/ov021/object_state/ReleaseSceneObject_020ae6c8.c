#include "nitro/types.h"

typedef struct {
    u8 data[0x2c];
} SharedRecordState;

typedef struct {
    u8 pad_000[0x15];
    u8 partCount;
    u8 pad_016[0x2e];
    u8 resource[0x104];
    SharedRecordState mainState;
    SharedRecordState *partStates;
} SceneObject;

extern void ReleaseResourceAndDetach_0202eee8(u8 *object);
extern void ReleaseSharedRecordState_020a9084(SharedRecordState *state);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void ReleaseCallbackOwnedBuffer_020aafac(SceneObject *object);

void ReleaseSceneObject_020ae6c8(SceneObject *object)
{
    int i;

    ReleaseResourceAndDetach_0202eee8(object->resource);
    ReleaseSharedRecordState_020a9084(&object->mainState);
    if (object->partStates != NULL) {
        for (i = 0; i < object->partCount; i++) {
            ReleaseSharedRecordState_020a9084(&object->partStates[i]);
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(object->partStates);
    }
    ReleaseCallbackOwnedBuffer_020aafac(object);
}
