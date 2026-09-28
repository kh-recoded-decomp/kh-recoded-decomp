#include "nitro/types.h"

typedef struct StageGroup {
    u8 pad_00[0x9];
    u8 isEnabled : 1;
    u8 unk_9_1 : 1;
    u8 state : 2;
} StageGroup;

extern s32 g_activeService_0209f2c8;
extern StageGroup *func_ov001_0209c0c4(u16 groupId);

BOOL func_ov001_02087dd0(s16 groupIndex)
{
    if (g_activeService_0209f2c8 != -1) {
        return func_ov001_0209c0c4(groupIndex + 1)->state & 1;
    }
    return FALSE;
}
