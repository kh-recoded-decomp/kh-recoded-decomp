#include "nitro/types.h"

typedef struct Position {
    int x;
    int y;
} Position;

typedef struct SlotGroups {
    Position origin;
    Position offset;
    u8 pad_010[0x1d4 - 0x10];
    u8 recordSlots[22][16];
    u8 pad_334[0x494 - 0x334];
    u8 counts[22];
} SlotGroups;

extern void func_0204f13c(void *manager, int recordIndex, Position *position);

void ResetGroupSlotsPosition_020680a4(void *manager, SlotGroups *groups)
{
    Position position;
    int group;
    int i;

    for (group = 0; group < 22; group++) {
        position.x = groups->origin.x + groups->offset.x;
        position.y = groups->origin.y + groups->offset.y;
        for (i = 0; i < groups->counts[group]; i++) {
            func_0204f13c(manager, groups->recordSlots[group][i], &position);
        }
    }
}
