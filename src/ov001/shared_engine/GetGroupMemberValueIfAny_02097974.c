#include "nitro/types.h"

extern void *func_ov001_0209c040(s16 groupId);
extern u32 func_ov001_02097950(void *node);

u32 GetGroupMemberValueIfAny_02097974(s32 groupId)
{
    void *node;

    if (groupId == 0) {
        return 0;
    }
    node = func_ov001_0209c040((s16)groupId);
    if (node != 0) {
        return func_ov001_02097950(node);
    }
    return 0;
}
