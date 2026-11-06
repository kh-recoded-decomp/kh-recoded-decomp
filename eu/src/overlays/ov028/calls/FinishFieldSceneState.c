#include "nitro/types.h"

typedef struct FieldSceneState {
    u8 pad_00[6];
    u16 flags;
} FieldSceneState;

extern FieldSceneState *gOv028FieldSceneWorkStorage;

int FinishFieldSceneState(void)
{
    gOv028FieldSceneWorkStorage->flags = gOv028FieldSceneWorkStorage->flags & 0xfff3;
    return -1;
}
