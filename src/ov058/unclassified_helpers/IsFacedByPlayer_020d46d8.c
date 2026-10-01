#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_0000[0x4e5];
    u8 alwaysAlert;
    u8 pad_04e6[0x9c0 - 0x4e6];
    s32 actionState;
    u8 pad_09c4[0xa0c - 0x9c4];
    fx32 reachBelow;
} Enemy;

extern Enemy *g_player_020d8a20;
extern const s16 data_0205356c[];
extern VecFx32 *func_ov052_020ceb54(Enemy *enemy);
extern u16 func_ov052_020ceb7c(Enemy *enemy);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

BOOL IsFacedByPlayer_020d46d8(Enemy *enemy, VecFx32 *outDirection)
{
    VecFx32 *enemyPos = func_ov052_020ceb54(enemy);
    VecFx32 *playerPos = func_ov052_020ceb54(g_player_020d8a20);
    fx32 height;
    BOOL inRange;
    fx32 length;
    int angleIndex;
    VecFx32 toEnemy;
    VecFx32 facing;

    func_01ffa0f4(playerPos, enemyPos);
    inRange = FALSE;
    VEC_Subtract_01ff9e3c(enemyPos, playerPos, &toEnemy);
    height = toEnemy.y;
    toEnemy.y = 0;
    length = func_01ffaff4(&toEnemy, &toEnemy);
    switch (g_player_020d8a20->actionState) {
    case 1:
    case 8:
        if (length < 0x1e00) {
            inRange = TRUE;
        }
        break;
    case 3:
    case 0x13:
        if (length < 0x1e00 && height < 0 && enemy->reachBelow >= -height) {
            inRange = TRUE;
        }
        break;
    }
    if (inRange) {
        angleIndex = func_ov052_020ceb7c(g_player_020d8a20) >> 4;
        facing.x = -data_0205356c[angleIndex];
        facing.y = 0;
        facing.z = -data_0205356c[(0x400 - angleIndex) & 0xfff];
        facing.y = 0;
        func_01ff9f88(&facing, &facing);
        if (VEC_DotProduct_01ff9e6c(&facing, &toEnemy) > 0x800) {
            *outDirection = toEnemy;
            return TRUE;
        }
    }
    return enemy->alwaysAlert != 0;
}
