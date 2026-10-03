#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
} SceneState;

extern SceneState *data_ov030_020bd000;

BOOL IsSceneUnpaused_020bacb4(void) {
    BOOL result = TRUE;

    if (data_ov030_020bd000->flags & 0x10) {
        result = FALSE;
    }
    return result;
}
