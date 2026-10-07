#include "nitro/types.h"

typedef struct StageGroup {
    u8 pad_00[0x9];
    u8 isEnabled : 1;
    u8 unk_9_1 : 1;
    u8 state : 2;
} StageGroup;

extern s32 g_stageEventsState;
extern StageGroup *GetStageObjectHandle(u16 groupId);

BOOL func_ov001_02087df8(s16 groupIndex)
{
    if (g_stageEventsState != -1) {
        return GetStageObjectHandle(groupIndex + 1)->state & 1;
    }
    return FALSE;
}
