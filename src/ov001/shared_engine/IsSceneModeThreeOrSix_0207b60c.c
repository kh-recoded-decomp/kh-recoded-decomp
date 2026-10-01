#include "nitro/types.h"

typedef struct SceneState {
    u8 pad_00[0x30];
    int mode;
} SceneState;

extern SceneState *data_ov001_020a04c8;

BOOL IsSceneModeThreeOrSix_0207b60c(void)
{
    BOOL match = TRUE;
    int mode = data_ov001_020a04c8->mode;

    if (mode != 6 && mode != 3) {
        match = FALSE;
    }
    return match != FALSE;
}
