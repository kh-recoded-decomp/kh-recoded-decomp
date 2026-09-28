#include "nitro/types.h"

typedef struct SceneCtl {
    void *obj;
    void *entry;
    s32   curId;
    s32   pendId;
    s32   pendArg;
} SceneCtl;

extern SceneCtl g_sceneCtl_0205fdec;
extern void func_01ff8830(void *dest, u32 value, u32 size);

s32 ResetSceneCtl_02025550(void)
{
    func_01ff8830(&g_sceneCtl_0205fdec, 0, 0x14);
    return 1;
}
