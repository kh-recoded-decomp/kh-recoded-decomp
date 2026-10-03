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

BOOL IsSceneFlag10Clear_020bc5c0(void) {
    return (data_ov036_020c3920.work->flags & 0x10) == 0;
}
