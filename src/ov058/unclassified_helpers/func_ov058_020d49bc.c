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

extern BOOL func_ov001_0206c328(TargetInfo *target);
extern BOOL FindNearestTarget_0206c348(TargetInfo *target, u8 team, u32 kinds);

BOOL func_ov058_020d49bc(Enemy *enemy)
{
    TargetInfo target;
    BOOL found = FALSE;

    if (func_ov001_0206c328(&target) && target.kind != 4) {
        enemy->target = target;
        found = TRUE;
    }
    if (!found && FindNearestTarget_0206c348(&enemy->target, enemy->team, 3)) {
        found = TRUE;
    }
    return found;
}
