#include "nitro/types.h"

typedef struct SceneWork {
    u8 unknown_00[6];
    u16 flags;
} SceneWork;

typedef struct SceneGlobals {
    void *unknown_00;
    SceneWork *work;
} SceneGlobals;

extern SceneGlobals data_ov036_020c3920;

void SetSceneFlag4000_020bc3f8(void) {
    data_ov036_020c3920.work->flags |= 0x4000;
}
