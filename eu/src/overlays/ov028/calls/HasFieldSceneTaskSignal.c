#include "nitro/types.h"

extern u32 gOv028FieldSceneTaskHandle;
extern s32 Obj_GetWord28(u32 handle);

BOOL HasFieldSceneTaskSignal(void)
{
    s32 result = Obj_GetWord28(gOv028FieldSceneTaskHandle);
    return result != 0;
}
