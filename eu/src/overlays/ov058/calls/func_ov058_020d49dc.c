#include "nitro/types.h"

typedef struct TargetInfo {
    u8 kind;
    u8 pad_01[0x03];
    void *object;
    u8 pad_08[0x0c];
} TargetInfo;

typedef struct {
    u8 pad_0000[0x9b4];
    u8 team;
    u8 pad_09b5[0x1048 - 0x9b5];
    TargetInfo target;
} Enemy;

extern BOOL ReadActiveMenuState(TargetInfo *target);
extern BOOL FindNearestTarget(TargetInfo *target, u8 team, u32 kinds);

BOOL func_ov058_020d49dc(Enemy *enemy)
{
    TargetInfo target;
    BOOL found = FALSE;

    if (ReadActiveMenuState(&target) && target.kind != 4) {
        enemy->target = target;
        found = TRUE;
    }
    if (!found && FindNearestTarget(&enemy->target, enemy->team, 3)) {
        found = TRUE;
    }
    return found;
}
