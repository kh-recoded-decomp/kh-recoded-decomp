#include "nitro/types.h"

typedef struct EventGroup {
    u16 unk_00;
    u16 state;
    u8 pad_04[0x4];
    s8 progress;
    u8 pad_09[0x7];
    u16 groupId;
    u8 pad_12[0x2];
    int pending;
} EventGroup;

extern s16 func_ov001_02098da8(EventGroup *group, int flaggedOnly);
extern s16 func_ov001_02098e24(EventGroup *group, int flaggedOnly);

int GetEventGroupState_02098ea8(EventGroup *group, u32 groupId, u32 flags)
{
    if (group == NULL) {
        return 0;
    }
    if (groupId != 0xffff && group->groupId != groupId) {
        return 0;
    }
    if (group->state == 7) {
        return 1;
    }
    if (flags & 1) {
        if (func_ov001_02098da8(group, 1) != 0) {
            if (func_ov001_02098e24(group, 1) == 0) {
                if (group->progress < 0) {
                    return -1;
                } else if (group->progress > 0) {
                    return -1;
                } else if (group->progress == 0) {
                    if (group->pending != 0) {
                        return -1;
                    }
                }
                return 1;
            }
            return -1;
        }
        return 0;
    }
    return -1;
}
