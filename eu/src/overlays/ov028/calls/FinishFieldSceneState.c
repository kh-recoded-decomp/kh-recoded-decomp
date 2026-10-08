#include "nitro/types.h"

typedef struct FieldSceneState {
    u8 pad_00[6];
    u16 flags;
} FieldSceneState;

extern FieldSceneState *data_ov028_020bb3a0;

int FinishFieldSceneState(void)
{
    data_ov028_020bb3a0->flags = data_ov028_020bb3a0->flags & 0xfff3;
    return -1;
}
