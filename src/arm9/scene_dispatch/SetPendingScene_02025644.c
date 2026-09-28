#include "nitro/types.h"

typedef struct SceneCtl {
    void *obj;
    void *entry;
    s32   curId;
    s32   pendId;
    s32   pendArg;
} SceneCtl;

extern SceneCtl g_sceneCtl_0205fdec;

void SetPendingScene_02025644(s32 pendId, s32 pendArg) {
    g_sceneCtl_0205fdec.pendId = pendId;
    g_sceneCtl_0205fdec.pendArg = pendArg;
}
