#include "nitro/types.h"

extern s32 IsScreenModeIdle(void);
extern void SetFieldStateValue(s32 param1, s32 param2);
extern void MarkFieldValueNegative(void);

u32 FieldSceneState_ResetFieldValueWhenScreenIdle(void)
{
    s32 ready = IsScreenModeIdle();

    if (ready != 0) {
        SetFieldStateValue(0xfffffffd, 3);
        MarkFieldValueNegative();
        return 7;
    }
    return 0xffffffff;
}
