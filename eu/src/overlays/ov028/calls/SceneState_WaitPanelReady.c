#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
} SceneState;

extern SceneState *data_ov028_020bb3a0;

extern BOOL func_ov001_0207b6b0(void);
extern void StoreToGlobalPtr4Field28(int value);

int SceneState_WaitPanelReady(void) {
    if (!func_ov001_0207b6b0()) {
        return -1;
    }
    if (data_ov028_020bb3a0->flags & 1) {
        data_ov028_020bb3a0->flags &= ~1;
    }
    StoreToGlobalPtr4Field28(0);
    return 7;
}
