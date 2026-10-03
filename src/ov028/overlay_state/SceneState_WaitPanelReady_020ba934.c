#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
} SceneState;

extern SceneState *data_ov028_020bb380;

extern BOOL func_ov001_0207b688(void);
extern void StoreToGlobalPtr4Field28_0202a778(int value);

int SceneState_WaitPanelReady_020ba934(void) {
    if (!func_ov001_0207b688()) {
        return -1;
    }
    if (data_ov028_020bb380->flags & 1) {
        data_ov028_020bb380->flags &= ~1;
    }
    StoreToGlobalPtr4Field28_0202a778(0);
    return 7;
}
