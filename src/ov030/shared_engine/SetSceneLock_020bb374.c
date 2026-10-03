#include "nitro/types.h"

typedef struct {
    u8 pad_00[9];
    u8 locked;
} SceneState;

extern SceneState *data_ov030_020bd000;

extern void func_ov042_020bd5d4(BOOL enabled);

void SetSceneLock_020bb374(u8 locked) {
    data_ov030_020bd000->locked = locked;
    func_ov042_020bd5d4(locked == 0 ? TRUE : FALSE);
}
