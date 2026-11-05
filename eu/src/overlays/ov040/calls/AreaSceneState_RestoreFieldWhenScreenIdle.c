#include "nitro/types.h"

extern int IsScreenModeIdle();
extern void SetFieldStateValue();
extern void MarkFieldValueNegative();

u32 AreaSceneState_RestoreFieldWhenScreenIdle(void)
{
    int ready;

    ready = IsScreenModeIdle();
    if (ready != 0) {
        SetFieldStateValue(0xfffffffd, 3);
        MarkFieldValueNegative();
        return 5;
    }
    return 0xffffffff;
}
